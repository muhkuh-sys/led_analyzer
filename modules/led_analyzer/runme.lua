---- importing ----
require("color_conversions") -- Convert between color spaces 
require("color_validation")	 -- Validate your colors, contains helper to print your colors and store your colors in adequate arrays
require("led_analyzer")		 -- should be renamed soon, contains the libusb, libftdi, tcs ... files 
require("testBoard")		 -- board to be tested, containing dom. wavelengths and/or x/y pairs

TEST_RESULT_OK = 0 
TEST_RESULT_LED_FAILED = 1 
TEST_RESULT_SENSORS_FAILED = 2


MAXHANDLES = 16 
MAXSENSORS = 16 

MAXSERIALS = 16

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


local clock = os.clock
function sleep(n)  -- seconds
  local t0 = clock()
  while clock() - t0 <= n do end
end


function astring_to_table(astring, numbOfSerials)
	
	
	local tSerialnumbers = {}
	
	for i = 0, numbOfSerials - 1 do
			
			if led_analyzer.astring_getitem(astring, i) ~= NULL then 
				tSerialnumbers[i+1] = led_analyzer.astring_getitem(astring, i)
			end 
	end
			
	return tSerialnumbers
end


asSerials = led_analyzer.new_astring(MAXSERIALS)
apHandles = led_analyzer.new_apvoid(MAXHANDLES)

numberofserials = led_analyzer.scan_devices(asSerials, MAXSERIALS);
stringtable = astring_to_table(asSerials, MAXSERIALS)
numberOfDevices = led_analyzer.connect_to_devices(apHandles, MAXHANDLES, asSerials)


local error_counter = 0 


if numberOfDevices == -1 then
		
		
	
else 
	
	-- must be 0 first, the functions increment it to 1 
	-- 0 because deviceNr -> handleNr algorithm needs this (detect_devices)	
	devIndex = 0


	 
	 -- integration time gain, waittime mit defines aus .c files ersetzen 
	 
	 
	while(devIndex < numberOfDevices) do 
	
		print(				"------------------------------------------------ ")
		print(string.format("------------------ Device %d -------------------- ", devIndex))
		print(				"------------------------------------------------ ")
		
		
		
		
		
		while(error_counter < INIT_MAXERROR) do
			ret = led_analyzer.init_sensors(apHandles, devIndex, TCS3471_INTEGRATION_200ms, TCS3471_GAIN_1X)
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
		
		
		while(error_counter < READ_MAXERROR) do		
			ret = led_analyzer.read_colors(apHandles, devIndex, ausClear, ausRed, ausGreen, ausBlue, aucIntTimes)
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
		
		while(error_counter < VALID_MAXERROR) do 
			ret = led_analyzer.check_validity(apHandles, devIndex, ausClear, aucIntTimes)
			if ret ~= 0 then 
				error_counter = error_counter + 1 
			else 
				break 
			end 
		end 
		if error_counter == VALID_MAXERROR then 
			print(string.format("%d invalid datasets in a row, test aborting ...", error_counter))
			return TEST_RESULT_SENSORS_FAILED 
		else 
			error_counter = 0 
		end 
		
		
		
		--led_analyzer.set_gain_x(apHandles, devIndex, TCS3471_GAIN_4X, 0);
		--led_analyzer.set_intTime_x(apHandles, devIndex, TCS3471_INTEGRATION_154ms, 0);
		

			led_analyzer.set_gain(apHandles, devIndex, TCS3471_GAIN_4X)
			led_analyzer.set_intTime(apHandles, devIndex, TCS3471_INTEGRATION_200ms)

			led_analyzer.get_gain(apHandles, devIndex, aucGains)
			led_analyzer.get_intTime(apHandles, devIndex, aucIntTimes)
			
--			for i = 0, 15 do
--				print(led_analyzer.puchar_getitem(aucGains, i))
--				print(led_analyzer.puchar_getitem(aucIntTimes, i))
--			end
			
		
		
		tColor, tXYZ, tYxy, tnm, tHSV = aus_to_table(devIndex, ausClear, ausRed, ausGreen, ausBlue, 16)

		print_color(devIndex, tColor, 16, "RGB")
		--print_color(devIndex, tXYZ, 16, "XYZ")
		--print_color(devIndex, tColor, 16, "RGB_n")
		--print_color(devIndex, tHSV, 16, "HSV")
		--print_color(devIndex, tYxy, 16, "Yxy")
		print_color(devIndex, tnm, 16, "wavelength")
		
		-- Validate color receives a device table, meaning a table with 16 entries for sensors
		-- as devIndex start = 0, and tableIndex start = 1, we have to pass devIndex +16
		
		-- other functions like print_color, austotable, ... get devIndex = 0 and use devIndex +1 intern
		validate_color(tTest[devIndex+1], tnm[devIndex+1], tYxy[devIndex+1])
		--print_LEDs(tTest[devIndex+1])
		
		devIndex = devIndex + 1
		
		
	end 


	-- Now comes a final check if all LED were found --
	
	-- devIndex = 0 
	-- local flag = 0 
	
	-- while(devIndex < numberOfDevices) do 
		-- for k,v in ipairs(tTest[devIndex+1]) do 
			-- if(tTest[devIndex+1][k].LED_State ~= 1) then 
				-- print(string.format("%20s not found ... ", tTest[devIndex+1][k].name ))
				-- flag = 1  
			-- else 
				-- print(string.format("%20s OK! ", tTest[devIndex+1][k].name ))
			-- end 		
		-- end 
		-- devIndex = devIndex + 1 
	-- end 
	

	ret = led_analyzer.free_devices(apHandles)
	

	led_analyzer.delete_ushort(ausClear)
	led_analyzer.delete_ushort(ausRed)
	led_analyzer.delete_ushort(ausGreen)
	led_analyzer.delete_ushort(ausBlue)
	
	led_analyzer.delete_puchar(aucGains)
	led_analyzer.delete_puchar(aucIntTimes)

	led_analyzer.delete_apvoid(apHandles)
	led_analyzer.delete_astring(asSerials)

	if flag == 0 then 
		print("All LEDs found") 
		return TEST_RESULT_OK 
	end 
	
	return TEST_RESULT_FAILED
end 
