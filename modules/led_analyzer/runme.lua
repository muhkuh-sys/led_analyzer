---- importing ----
require("color_conversions") -- Convert between color spaces 
require("color_validation")	 -- Validate your colors, contains helper to print your colors and store your colors in adequate arrays
require("bit")				 -- should be renamed soon, contains the libusb, libftdi, tcs ... files 
require("testBoard")		 -- board to be tested, containing dom. wavelengths and/or x/y pairs

TEST_RESULT_OK = 0 
TEST_RESULT_LED_FAILED = 1 
TEST_RESULT_SENSORS_FAILED = 2

MAXHANDLES = 16 
MAXSENSORS = 16 

INIT_MAXERROR  = 10
READ_MAXERROR  = 10 
VALID_MAXERROR = 10 

TCS3471_GAIN_1X = 0x00
TCS3471_GAIN_4X = 0x01
TCS3471_GAIN_16X = 0x02
TCS3471_GAIN_60X = 0x03

TCS3471_INTEGRATION_2_4ms 		= 0xFF
TCS3471_INTEGRATION_24ms 		= 0xF6
TCS3471_INTEGRATION_100ms 		= 0xD6
TCS3471_INTEGRATION_200ms	    = 0xAD
TCS3471_INTEGRATION_154ms 		= 0xC0
TCS3471_INTEGRATION_700ms       = 0x00

-- Colors from the TCS3472 will be stored in following arrays -- 
ausClear  = bit.new_ushort(MAXSENSORS)
ausRed    = bit.new_ushort(MAXSENSORS)
ausGreen  = bit.new_ushort(MAXSENSORS)
ausBlue   = bit.new_ushort(MAXSENSORS)

-- array of void pointers which will contain struct_ftdi_context* elements -- 
apHandles = bit.new_apvoid(MAXSENSORS)

-- Detects the ftdi devices and returns the number of devices found 
-- #1 => 1 ftdi device found => two handles saved in apHandles, second param: number of max handles
numberOfDevices = bit.detect_devices(apHandles, MAXHANDLES)


local error_counter = 0 



if numberOfDevices == -1 then
		
		
	
else 
	
	-- must be 0 first, the functions increment it to 1 
	-- 0 because deviceNr -> handleNr algorithm needs this (detect_devices)	
	devIndex = 0


	 
	 -- integration time gain, waittime mit defines aus .c files ersetzen 
	 
	 
	while(devIndex < numberOfDevices) do 
		-- Init: apHandles, devIndex, integrationtime, gain, -waittime 
		
		while(error_counter < INIT_MAXERROR) do
			ret = bit.init_sensors(apHandles, devIndex, TCS3471_INTEGRATION_200ms, TCS3471_GAIN_4X, 20)
			if ret ~= 0 then
				error_counter = error_counter + 1 
			else
				break
			end  
		end 
		if error_counter == INIT_MAXERROR then
			print(string.format("%d initialization errors in a row, test aborting ..."))
			return TEST_RESULT_SENSORS_FAILED
		else 
			error_counter = 0 
		end 
		
		
		while(error_counter < READ_MAXERROR) do		
			ret = bit.read_colors(apHandles, devIndex, ausClear, ausRed, ausGreen, ausBlue)
			if ret ~= 0 then
				error_counter = error_counter + 1
			else
				break 
			end 
		end 
		if error_counter == READ_MAXERROR then
			print(string.format("%d color reading errors in a row, test aborting ..."))
			return TEST_RESULT_SENSORS_FAILED  
		else 
			error_counter = 0
		end 
		
		while(error_counter < VALID_MAXERROR) do 
			ret = bit.check_validity(apHandles, devIndex, ausClear, TCS3471_INTEGRATION_100ms)
			if ret ~= 0 then 
				error_counter = error_counter + 1 
			else 
				break 
			end 
		end 
		if error_counter == VALID_MAXERROR then 
			print(string.format("%d invalid datasets in a row, test aborting ..."))
			return TEST_RESULT_SENSORS_FAILED 
		else 
			error_counter = 0 
		end 
		
		
		tColor, tXYZ, tYxy, tnm, tHSV = aus_to_table(devIndex, ausClear, ausRed, ausGreen, ausBlue, 16)

		--print_color(devIndex, tColor, 16, "RGB")
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
	

	ret = bit.free_devices(apHandles)
	

	bit.delete_ushort(ausClear)
	bit.delete_ushort(ausRed)
	bit.delete_ushort(ausGreen)
	bit.delete_ushort(ausBlue)

	bit.delete_apvoid(apHandles)

	if flag == 0 then 
		print("All LEDs found") 
		return TEST_RESULT_OK 
	end 
	
	return TEST_RESULT_FAILED
end 
