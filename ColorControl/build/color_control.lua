---- importing ----

require("led_analyzer")		 -- libusb/ftdi driver library + sensor specific functions 
require("color_conversions") -- handles conversion between color spaces and array to table (or vice versa) handling
require("color_validation")	 -- Validate your colors, contains helper to print your colors and store your colors in adequate arrays


TEST_RESULT_OK 			  = 0 
TEST_RESULT_FAIL 		  = 1 
TEST_RESULT_LEDS_ON 	  = 2 
TEST_RESULT_LEDS_OFF 	  = 3 
TEST_RESULT_NO_DEVICES 	  = 4
TEST_RESULT_DEVICE_FAILED = 5 

MAXDEVICES = 50
MAXHANDLES = MAXDEVICES * 2
MAXSENSORS = 16 

MAXSERIALS = MAXDEVICES

INIT_MAXERROR  = 10
READ_MAXERROR  = 10 
VALID_MAXERROR = 10 


-- tcs3472 specific settings for gain 
TCS3472_GAIN_1X  = 0x00
TCS3472_GAIN_4X  = 0x01
TCS3472_GAIN_16X = 0x02
TCS3472_GAIN_60X = 0x03

-- tcs3472 specific settings for integration time 
TCS3472_INTEGRATION_2_4ms 		= 0xFF
TCS3472_INTEGRATION_24ms 		= 0xF6
TCS3472_INTEGRATION_100ms 		= 0xD6
TCS3472_INTEGRATION_200ms	    = 0xAD
TCS3472_INTEGRATION_154ms 		= 0xC0
TCS3472_INTEGRATION_700ms       = 0x00

-- Color and light related data from the TCS3472 will be stored in following arrays -- 
local ausClear  		= led_analyzer.new_ushort(MAXSENSORS)
local ausRed    		= led_analyzer.new_ushort(MAXSENSORS)
local ausGreen  		= led_analyzer.new_ushort(MAXSENSORS)
local ausBlue   		= led_analyzer.new_ushort(MAXSENSORS)
local ausCCT    		= led_analyzer.new_ushort(MAXSENSORS)
local afLUX     		= led_analyzer.new_afloat(MAXSENSORS)
-- system settings from tcs3472 will be stored in following arrays --
local aucGains  		= led_analyzer.new_puchar(MAXSENSORS)
local aucIntTimes 		= led_analyzer.new_puchar(MAXSENSORS)
-- serial numbers of connected color controller(s) will be stored in asSerials --
local asSerials 		= led_analyzer.new_astring(MAXSERIALS)
local tStrSerials		= {}
-- handle to all connected color controller(s) will be stored in apHandles (note 2 handles per device)
local apHandles 		= led_analyzer.new_apvoid(MAXHANDLES)
local numberOfDevices	= 0
-- global table contains all color and light related data / global for easy access by C 
tColorTable = {}
-- table that contains a test summary for each device --
local tTestSummary

local ret 				 = 0



function scanDevices()
	numberOfDevices = led_analyzer.scan_devices(asSerials, MAXSERIALS)
	tStrSerials = astring2table(asSerials, numberOfDevices)
	return tStrSerials, numberOfDevices
end 

-- connects to color controller devices with serial numbers given in table tStrSerials
-- if tOptionalSerials doesn't exist, function will connect to all color controller devices 
-- taking the order of their serial numbers into account (serial number 20000 will have a smaller index than 20004)
function connectDevices(tOptionalSerials)
	
	if(tOptionalSerials == nil) then 
		numberOfDevices = led_analyzer.connect_to_devices(apHandles, MAXHANDLES, table2astring(tStrSerials, asSerials))
	else 
		numberOfDevices = led_analyzer.connect_to_devices(apHandles, MAXHANDLES, table2astring(tOptionalSerials, asSerials))
	end 
	
	return numberOfDevices;
end 



-- initializes all connected devices with gain and integration time settings given in the parameters
-- if any of the sensor specific settings like gain or integration time is not given the value will 
-- be set to a default value (gain 1x and integration time 100 ms)
function initDevices(numberOfDevices, gain, integrationtime)
-- iterate over all devices and perform initialization -- 
	local devIndex = 0
	local error_counter = 0 
	local ret = 0
	
	local lGain = 0 
	local lIntegrationtime = 0 
	
	if gain == nil then 
		lGain = TCS3472_GAIN_1X 
	else 
		lGain = gain 
	end 
	
	if integrationtime == nil then 
		lIntegrationtime = TCS3472_INTEGRATION_100ms
	else 
		lIntegrationtime = integrationtime
	end 
	
	while(devIndex < numberOfDevices) do 


		led_analyzer.set_gain(apHandles, devIndex, lGain)
		led_analyzer.set_intTime(apHandles, devIndex, lIntegrationtime)
		
		while(error_counter < INIT_MAXERROR) do
			ret = led_analyzer.init_sensors(apHandles, devIndex)
			if ret ~= 0 then
				error_counter = error_counter + 1 
			else
				break
			end  
		end 
		if error_counter == INIT_MAXERROR then
			print(string.format("%d initialization errors in a row, test aborting ...", error_counter))
			return TEST_RESULT_DEVICE_FAILED
		else 
			error_counter = 0 
		end 
				
		devIndex = devIndex + 1 
	end 
	
	return 0 
end 


-- starts the measurements on each opened color controller device
-- having read and checked all raw color data, these will be converted into the needed color spaces and stored in a color table  
function startMeasurements(numberOfDevices)
	
	local devIndex = 0
	local error_counter = 0 
	local ret = 0
	
	tColorTable = {}

	while(devIndex < numberOfDevices) do 
		print(string.format("\n------------------ Device %d -------------------- ", devIndex))
			
		while(error_counter < READ_MAXERROR) do		
			ret = led_analyzer.read_colors(apHandles, devIndex, ausClear, ausRed, ausGreen, ausBlue, ausCCT, afLUX)
			if ret ~= 0 then
				error_counter = error_counter + 1
			else
				break 
			end 
		end 
		if error_counter == READ_MAXERROR then
			print(string.format("%d color reading errors in a row, test aborting ...", error_counter))
			return TEST_RESULT_DEVICE_FAILED  
		else 
			error_counter = 0
		end 
		
		tColorTable[devIndex] = aus2colorTable(ausClear, ausRed, ausGreen, ausBlue, ausCCT, afLUX, 16)
		print_color(devIndex, tColorTable, 16)
		--print_color(devIndex, tColorTable, 16, "HSV")
		
		devIndex = devIndex + 1 
		print("\n")
	end 
	
	return 0 
end 

-- function compares the color sets read from the devices to the testtable given in tDUT
-- the LEDs under test must be on, this means we test if the right LEDs (correct wavelength, sat, ...) are mounted on the baord
-- a table tTestSummary will be filled according to the test results (led on, led off, wrong led detected and so on)
function ON_validateLEDs(numberOfDevices, tDUT, lux_check_enable)
	
	local devIndex = 0
	local ret = 0 
	
	tTestSummary = {}
	print("Testing LEDs ON\n")
	
	while(devIndex < numberOfDevices) do 
		tTestSummary[devIndex] = getDeviceSummary(tDUT[devIndex], tColorTable[devIndex][1], lux_check_enable)
		--printDeviceSummary(tTestSummary[devIndex], 1 )
		devIndex = devIndex + 1 
	end 
	
	ret = ON_validateTestSummary(numberOfDevices, tTestSummary)
	return ret 
end

-- function compares the color sets read from the devices to the testtable given in tDUT
-- the LEDs under test must be off, this means we test if the LEDs can be powered off 
-- a table tTestSummary will be filled according to the test results (led on, led off, wrong led detected and so on)
function OFF_validateLEDs(numberOfDevices, tDUT, lux_check_enable)
	
	local devIndex = 0
	local ret = 0 
	
	tTestSummary = {}
	print("Testing LEDs OFF\n")
	
	while(devIndex < numberOfDevices) do 
		tTestSummary[devIndex] = getDeviceSummary(tDUT[devIndex], tColorTable[devIndex][1], lux_check_enable)
		devIndex = devIndex + 1 
	end 
	
	ret = OFF_validateTestSummary(numberOfDevices, tTestSummary)
	return ret 
end


function swapUp(sCurSerial)
	led_analyzer.swap_up(asSerials, sCurSerial)
	tStrSerials = astring2table(asSerials, numberOfDevices)
	return tStrSerials
end 

function swapDown(sCurSerial)
	led_analyzer.swap_down(asSerials, sCurSerial)
	tStrSerials = astring2table(asSerials, numberOfDevices)
	return tStrSerials
end 


-- don't forget to clean up after every test -- 
function free()
	-- CLEAN UP --
	led_analyzer.free_devices(apHandles)
	led_analyzer.delete_ushort(ausClear)
	led_analyzer.delete_ushort(ausRed)
	led_analyzer.delete_ushort(ausGreen)
	led_analyzer.delete_ushort(ausBlue)
	led_analyzer.delete_ushort(ausCCT)
	led_analyzer.delete_afloat(afLUX)
	led_analyzer.delete_puchar(aucGains)
	led_analyzer.delete_puchar(aucIntTimes)
	led_analyzer.delete_apvoid(apHandles)
	led_analyzer.delete_astring(asSerials)
	
end 

