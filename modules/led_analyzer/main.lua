---- importing ----
require("color_conversions") -- Convert between color spaces 
require("color_validation")	 -- Validate your colors, contains helper to print your colors and store your colors in adequate arrays
require("led_analyzer")		 -- libusb/ftdi driver library + sensor specific functions 
require("testboard")		 -- board to be tested, containing dom. wavelengths and/or x/y pairs

TEST_RESULT_OK = 0 
TEST_RESULT_LED_FAILED = 1
TEST_RESULT_NO_DEVICES = 2
TEST_RESULT_DEVICE_FAILED = 3

MAXDEVICES = 50
MAXHANDLES = MAXDEVICES * 2
MAXSENSORS = 16 

MAXSERIALS = MAXDEVICES

INIT_MAXERROR  = 10
READ_MAXERROR  = 10 
VALID_MAXERROR = 10 

TCS3472_GAIN_1X  = 0x00
TCS3472_GAIN_4X  = 0x01
TCS3472_GAIN_16X = 0x02
TCS3472_GAIN_60X = 0x03

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
-- handle to all connected color controller(s) will be stored in apHandles 
local apHandles 		= led_analyzer.new_apvoid(MAXHANDLES)
local numberOfDevices   = 0
-- table contains all color and light related data
local tColorTable 		= {}
-- the test summary --
local tTestSummary 		= {}

local ret 				= 0



function initDevices(numberOfDevices, gain, integrationtime)
-- iterate over all devices and perform initialization -- 
	local devIndex = 0
	local error_counter = 0 
	local ret = 0
	
	while(devIndex < numberOfDevices) do 


		led_analyzer.set_gain(apHandles, devIndex, gain)
		led_analyzer.set_intTime(apHandles, devIndex, integrationtime)
		
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

function startMeasurements(numberOfDevices)
	
	local devIndex = 0
	local error_counter = 0 
	local ret = 0

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
		print_color(devIndex, tColorTable, 16, "wavelength")
		--print_color(devIndex, tColorTable, 16, "RGB")
		
		devIndex = devIndex + 1 
		print("\n")
	end 
	
	return 0 
end 

function validateLEDs(numberOfDevices, tDUT, lux_check_enable)
	
	local devIndex = 0
	local ret = 0 
	
	while(devIndex < numberOfDevices) do 
		tTestSummary[devIndex] = getDeviceSummary(tDUT[devIndex], tColorTable[devIndex][1], lux_check_enable)
		--printDeviceSummary(tTestSummary[devIndex], 1 )
		devIndex = devIndex + 1 
	end 
	
	ret = validateTestSummary(numberOfDevices, tTestSummary)
	return ret 
end

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










--------------------------------- DEVICE CONNECTION ------------------------------
numberOfDevices = led_analyzer.scan_devices(asSerials, MAXSERIALS);
numberOfDevices = led_analyzer.connect_to_devices(apHandles, MAXHANDLES, asSerials)

if numberOfDevices == 0 then 
	return TEST_RESULT_NO_DEVICES
end 	
if numberOfDevices < 0 then
	return TEST_RESULT_DEVICE_FAILED
end 
---------------------------------- ACTUAL TEST -----------------------------------

ret = initDevices(numberOfDevices, TCS3472_GAIN_1X, TCS3472_INTEGRATION_100ms)
led_analyzer.wait4Conversion(500)
if(ret ~= 0) then 
	free()
	return TEST_RESULT_DEVICE_FAILED
end 


led_analyzer.wait4Conversion(100)
ret = startMeasurements(numberOfDevices)
if (ret ~= 0) then 
	free()
	return TEST_RESULT_DEVICE_FAILED
end 

ret = validateLEDs(numberOfDevices, tTest, 1)


free()
return ret 



------------------------------------ TEST END ------------------------------------

