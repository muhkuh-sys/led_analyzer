-- DEBU OUTPUT LEVELS
-- 0 : no warnings if test entries are missing for a device or test entries are missing for sensors
-- 1 : prints out information about the failed sensors and info text 
-- 2 : prints out warnings if test entries are missing for devices or sensors 
-- 3 : if test entries for devices miss we throw an error 

DEBUG_OUTPUT = 1

-- tDUTrow is a row in testboard.lua which contains LED, sat, lux and nm values and tolerances
-- tnm is a row with a .nm value 

function compareRows(tDUTrow, tCurColorSensor, lux_check_enable)
	
	-- The row in testboard exists, thus a test for this LED is desired 
	if tDUTrow ~= nil then 
		-- d prefix describes a delta value 
		local dnm = tCurColorSensor.nm - tDUTrow.nm 
		local dsat = tCurColorSensor.sat - tDUTrow.sat
		local dlux 
		
		if lux_check_enable ~= nil then 
			dlux = tCurColorSensor.lux - tDUTrow.lux 
		else 
			dlux = 0 
		end 
		
		-- Saturation and wavelength fit 
		if  (tCurColorSensor.nm  		  >= (tDUTrow.nm  - tDUTrow.tol_nm)
		and  tCurColorSensor.nm  		  <= (tDUTrow.nm  + tDUTrow.tol_nm)
		and  tCurColorSensor.sat 		  >= (tDUTrow.sat - tDUTrow.tol_sat)
		and  tCurColorSensor.sat		  <= (tDUTrow.sat + tDUTrow.tol_sat)) then 
		
			-- Brightness check is enabled
			if lux_check_enable ~= nil then 
				if (tDUTrow.lux ~= nil) and (tDUTrow.tol_lux ~= nil) then 
					-- Brightness is OK --
					if tCurColorSensor.lux > (tDUTrow.lux - tDUTrow.tol_lux)
					and tCurColorSensor.lux < (tDUTrow.lux + tDUTrow.tol_lux) then 
						return 0, string.format("%s LED with %3d nm OK - PASS!", tReferenceLEDcolors[tDUTrow.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
					 
					-- Brightness falls below min_brightness
					elseif tCurColorSensor.lux < (tDUTrow.lux - tDUTrow.tol_lux) then
						return 4, "LED too dark!\n			Check if right series resisor is used.", dnm, dsat, dlux
					 
					-- Brightness exceeds max_brightness
					elseif tCurColorSensor.lux > (tDUTrow.lux + tDUTrow.tol_lux) then  
						return 5, "LED too bright!\n			Check if right series resistor is used.\n			Check if shortcuts exists on the board", dnm, dsat, dlux
					end   
				elseif tDUTrow.lux == nil and tDUTrow.tol_lux ~= nil then 
						return 6, "value for lux or tol_lux is missing, please check.\n"
				
				elseif tDUTrow.lux ~= nil and tDUTrow.tol_lux == nil then 
						return 6, "value for lux or tol_lux is missing, please check.\n"
				end 
				
			--Brightness check is disabled 
			else 
				-- As wavelength and saturations are OK and there's no need for a lux check we can return OK here
				return 0, string.format("%s LED with %3d nm OK - PASS!", tReferenceLEDcolors[tDUTrow.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
			end 
		
		-- Saturation fits but wavelength doesn't 
		elseif ((tCurColorSensor.nm  <= (tDUTrow.nm  - tDUTrow.tol_nm) 
		or 	     tCurColorSensor.nm  >= (tDUTrow.nm  + tDUTrow.tol_nm))
		and      tCurColorSensor.sat >= (tDUTrow.sat - tDUTrow.tol_sat)
		and      tCurColorSensor.sat <= (tDUTrow.sat + tDUTrow.tol_sat)) then 
			return 2, string.format("Wrong LED Color!\n			Want: %s with %3d nm\n 			Detected: %s with %3d nm", 
					tReferenceLEDcolors[tDUTrow.nm].colorname, tReferenceLEDcolors[tDUTrow.nm].nm, 
					tReferenceLEDcolors[tCurColorSensor.nm].colorname, tReferenceLEDcolors[tCurColorSensor.nm].nm), dnm, dsat, dlux
			
		-- Neither saturation nor wavelength fit -- NO LED 
		else 
			return 1, string.format("NO LED DETECTED!\n			Want: %s with %3d nm", tReferenceLEDcolors[tDUTrow.nm].colorname,
					tReferenceLEDcolors[tDUTrow.nm].nm), dnm, dsat, dlux
		end 
	
	-- the wavelength field in the row for testboard does not exist, thus we do not need to test this LED "
	else 
		return 3, "NO TEST ENTRY", 0, 0, 0
	end 
	
end 
	
	 
-- Checks if the LEDs measured by a device are correct 
function inRange(tDUT, tCurColors, lux_check_enable)
	local tTestSummary_device = {}
	
	local status, infotext, dnm, dsat, dlux
	
	for sensor = 1, 16 do 
			tTestSummary_device[sensor] = {}
			status, infotext, dnm, dsat, dlux = compareRows(tDUT[sensor], tCurColors[sensor], lux_check_enable)
			tTestSummary_device[sensor].status 	 = status
			tTestSummary_device[sensor].infotext = infotext
			tTestSummary_device[sensor].dnm  	 = dnm 
			tTestSummary_device[sensor].dsat 	 = dsat  
			tTestSummary_device[sensor].dlux 	 = dlux  
	end 
	
	return tTestSummary_device 
end 


function getDeviceSummary(tDUT, tCurColors, lux_check_enable)
	
	local tTestSummary_device 
	
	if(tDUT ~= nil) then 
		tTestSummary_device = {}
		tTestSummary_device = inRange(tDUT, tCurColors, lux_check_enable)
	end 
	
	return tTestSummary_device 
end 


-- prints a test summary for a device 
function printDeviceSummary(tTestSummary_device, info_enable)

	if(tTestSummary_device ~= nil) then  
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dlux") 
		for i = 1, 16 do 
			if(tTestSummary_device[i] ~= nil) then 
				print(string.format("%2d	 	 %2d		%4d		%3.2f		%5d", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
				tTestSummary_device[i].dsat, tTestSummary_device[i].dlux))
				if info_enable >= 1 then 	
					print(tTestSummary_device[i].infotext)
				end 
			end
		end 
	end 

end 


function ON_validateTestSummary(numberOfDevices, tTestSummary)
	-- Iterate over all device summaries
	local devIndex
	local errorFlag = 0 
	
	-- check for missing device entries and warn --
	devIndex = 0
	while(devIndex < numberOfDevices) do 
		if(tTestSummary[devIndex] == nil) then 
			if DEBUG_OUTPUT >= 3 then 
				print(string.format("\n!!!!! WARNING !!!!!  WE HAVE %2d DEVICES BUT TEST ENTRY FOR DEVICE %d IS MISSING.\n", numberOfDevices, devIndex))
			end  
			if DEBUG_OUTPUT >= 4 then
				print(string.format("\n!!!!! QUITTING !!!!! \n", numberOfDevices, devIndex))
				return TEST_RESULT_DEVICE_FAILED
			end 
		end 
		devIndex = devIndex + 1 
	end 
	
	-- check for missing sensor entries and warn -- 
	devIndex = 0 
	while(devIndex < numberOfDevices) do 
		if(tTestSummary[devIndex] ~= nil) then 
			for i = 1, 16 do 
				if(tTestSummary[devIndex][i].infotext == "NO TEST ENTRY") then 
					if DEBUG_OUTPUT >= 2 then 
						print(string.format("!! WARNING !! NO TEST ENTRY FOR SENSOR %2d on DEVICE %2d", i, devIndex))
					end 
				end 
			end 
		end 
		devIndex = devIndex + 1 
	end 
	
	-- now validate all existent entries -- 
	print("\n")
	devIndex = 0
	while(devIndex < numberOfDevices) do
		if(tTestSummary[devIndex] ~= nil) then 
			for i = 1, 16 do
				if tTestSummary[devIndex][i].status ~= 0 and tTestSummary[devIndex][i].infotext ~= "NO TEST ENTRY"	 then 
					if DEBUG_OUTPUT >= 1 then 
						print(string.format("Device %2d Sensor %2d --- %s", devIndex, i, tTestSummary[devIndex][i].infotext))
						print(string.format("			delta nm: %4d nm     delta sat: %3.2f     delta lux: %5d\n", 
											tTestSummary[devIndex][i].dnm, tTestSummary[devIndex][i].dsat, tTestSummary[devIndex][i].dlux))
					end 
					errorFlag = 1
				 end 	
			end 
		end  
		devIndex = devIndex + 1 
	end
		
	
	if errorFlag == 0 then 
		print("")
		print(" #######  ##    ## ")
		print("##     ## ##   ##  ")
		print("##     ## ##  ##   ")
		print("##     ## #####    ")
		print("##     ## ##  ##   ")
		print("##     ## ##   ##  ")
		print(" #######  ##    ## ")
		print("")
		
		return TEST_RESULT_LEDS_ON
	else 
		print("")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!       ERROR       !!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("")
		
		return TEST_RESULT_LEDS_OFF
	end 
	
end  


function OFF_validateTestSummary(numberOfDevices, tTestSummary)
	-- Iterate over all device summaries
	local devIndex
	local errorFlag = 0 
	
	-- check for missing device entries and warn --
	devIndex = 0
	while(devIndex < numberOfDevices) do 
		if(tTestSummary[devIndex] == nil) then 
			if DEBUG_OUTPUT >= 3 then 
				print(string.format("\n!!!!! WARNING !!!!!  WE HAVE %2d DEVICES BUT TEST ENTRY FOR DEVICE %d IS MISSING.\n", numberOfDevices, devIndex))
			end  
			if DEBUG_OUTPUT >= 4 then
				print(string.format("\n!!!!! QUITTING !!!!! \n", numberOfDevices, devIndex))
				return TEST_RESULT_DEVICE_FAILED
			end 
		end 
		devIndex = devIndex + 1 
	end 
	
	-- check for missing sensor entries and warn -- 
	devIndex = 0 
	while(devIndex < numberOfDevices) do 
		if(tTestSummary[devIndex] ~= nil) then 
			for i = 1, 16 do 
				if(tTestSummary[devIndex][i].infotext == "NO TEST ENTRY") then 
					if DEBUG_OUTPUT >= 2 then 
						print(string.format("!! WARNING !! NO TEST ENTRY FOR SENSOR %2d on DEVICE %2d", i, devIndex))
					end 
				end 
			end 
		end 
		devIndex = devIndex + 1 
	end 
	
	-- now validate all existent entries -- 
	print("\n")
	devIndex = 0
	while(devIndex < numberOfDevices) do
		if(tTestSummary[devIndex] ~= nil) then 
			for i = 1, 16 do
				if tTestSummary[devIndex][i].status ~= 1 and tTestSummary[devIndex][i].infotext ~= "NO TEST ENTRY"	 then 
					if DEBUG_OUTPUT >= 1 then 
						print(string.format("Device %2d Sensor %2d detected a LED though it should be off!\n", devIndex, i))		
					end 
					errorFlag = 1
				 end 	
			end 
		end  
		devIndex = devIndex + 1 
	end
		
	if errorFlag == 0 then 
		print("")
		print(" #######  ##    ## ")
		print("##     ## ##   ##  ")
		print("##     ## ##  ##   ")
		print("##     ## #####    ")
		print("##     ## ##  ##   ")
		print("##     ## ##   ##  ")
		print(" #######  ##    ## ")
		print("")
		
		return TEST_RESULT_LEDS_OFF
	else 
		print("")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!       ERROR       !!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("")
		
		return TEST_RESULT_LEDS_ON 
	end 
	
end  