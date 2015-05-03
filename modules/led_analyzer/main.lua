---- importing ----
require("color_conversions") -- Convert between color spaces 
require("color_validation")	 -- Validate your colors, contains helper to print your colors and store your colors in adequate arrays
require("led_analyzer")		 -- libusb/ftdi driver library + sensor specific functions 
require("testboard")		 -- board to be tested, containing dom. wavelengths and/or x/y pairs

local clock = os.clock
function sleep(n)  -- seconds
  local t0 = clock()
  while clock() - t0 <= n do end
end

TEST_RESULT_OK = 0 
TEST_RESULT_LED_FAILED = 1 
TEST_RESULT_SENSORS_FAILED = 2
TEST_RESULT_NO_DEVICES = 3
TEST_RESULT_DEVICE_FAILED = 4

MAXDEVICES = 50
MAXHANDLES = MAXDEVICES * 2
MAXSENSORS = 16 

MAXSERIALS = MAXDEVICES

INIT_MAXERROR  = 10
READ_MAXERROR  = 10 
VALID_MAXERROR = 10 

TCS3471_GAIN_1X  = 0x00
TCS3471_GAIN_4X  = 0x01
TCS3471_GAIN_16X = 0x02
TCS3471_GAIN_60X = 0x03

TCS3471_INTEGRATION_2_4ms 		= 0xFF
TCS3471_INTEGRATION_24ms 		= 0xF6
TCS3471_INTEGRATION_100ms 		= 0xD6
TCS3471_INTEGRATION_200ms	    = 0xAD
TCS3471_INTEGRATION_154ms 		= 0xC0
TCS3471_INTEGRATION_700ms       = 0x00

-- Colors from the TCS3472 will be stored in following arrays -- 
ausClear  = led_analyzer.new_ushort(MAXSENSORS)
ausRed    = led_analyzer.new_ushort(MAXSENSORS)
ausGreen  = led_analyzer.new_ushort(MAXSENSORS)
ausBlue   = led_analyzer.new_ushort(MAXSENSORS)


aucGains  = led_analyzer.new_puchar(MAXSENSORS)
aucIntTimes = led_analyzer.new_puchar(MAXSENSORS)


asSerials = led_analyzer.new_astring(MAXSERIALS)
apHandles = led_analyzer.new_apvoid(MAXHANDLES)


numberOfDevices = led_analyzer.scan_devices(asSerials, MAXSERIALS);


numberOfDevices = led_analyzer.connect_to_devices(apHandles, MAXHANDLES, asSerials)
tSerials = astring_to_table(asSerials, MAXSERIALS)

local devIndex = 0 
local error_counter = 0 

if numberOfDevices == 0 then 
	return TEST_RESULT_NO_DEVICES
end 	
if numberOfDevices < 0 then
	return TEST_RESULT_DEVICE_FAILED
end 


	

-- iterate over all devices and perform initialization -- 
devIndex = 0
while(devIndex < numberOfDevices) do 


	led_analyzer.set_gain(apHandles, devIndex, TCS3471_GAIN_1X)
	led_analyzer.set_intTime(apHandles, devIndex, TCS3471_INTEGRATION_100ms)
	
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
		return TEST_RESULT_SENSORS_FAILED
	else 
		error_counter = 0 
	end 
			
	devIndex = devIndex + 1 
end 


led_analyzer.wait4Conversion(500)



-- perform the color related functions which contains reading out color, do the color conversion
-- put the colors into the color tables and perform a final validty check 


-- table containing sensor's colors in diferent color spaces 
-- Index 1: Wavelength 
-- Index 2: RGB 
-- Index 3: XYZ
-- Index 4: tYxy 
-- Index 5: tHSV 

devIndex = 0 
local tColorTable = {}

while(devIndex < numberOfDevices) do 

	print(string.format("\n------------------ Device %d -------------------- ", devIndex))
		
	while(error_counter < READ_MAXERROR) do		
		ret = led_analyzer.read_colors(apHandles, devIndex, ausClear, ausRed, ausGreen, ausBlue)
		if ret ~= 0 then
			error_counter = error_counter + 1
		else
			break 
		end 
	end 
	if error_counter == READ_MAXERROR then
		print(string.format("%d color reading errors in a row, test aborting ...", error_counter))
		return TEST_RESULT_SENSORS_FAILED  
	else 
		error_counter = 0
	end 
	
	tColorTable[devIndex] = aus2colorTable(ausClear, ausRed, ausGreen, ausBlue, 16)
	print_color(devIndex, tColorTable, 16, "wavelength")
	print_color(devIndex, tColorTable, 16, "RGB")
	
	
	
	devIndex = devIndex + 1 
	print("\n")
end 

-- now follows the validation of the LEDs given in testboard.lua --
devIndex = 0 
tTestSummary = {}
while(devIndex < numberOfDevices) do 

	print(string.format("\n-------------------------------- Device %d -------------------------------------- ", devIndex))	
	tTestSummary[devIndex] = validate_device_colors(tTest[devIndex], tColorTable[devIndex][1], 0)
	print_deviceSummary(tTestSummary[devIndex], 1 )

devIndex = devIndex + 1 

	
end 


ret = led_analyzer.free_devices(apHandles)	

led_analyzer.delete_ushort(ausClear)
led_analyzer.delete_ushort(ausRed)
led_analyzer.delete_ushort(ausGreen)
led_analyzer.delete_ushort(ausBlue)
	
led_analyzer.delete_puchar(aucGains)
led_analyzer.delete_puchar(aucIntTimes)

led_analyzer.delete_apvoid(apHandles)
led_analyzer.delete_astring(asSerials)