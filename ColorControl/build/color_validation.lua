-- DEBU OUTPUT LEVELS
-- 0 : no warnings if test entries are missing for a device or test entries are missing for sensors
-- 1 : prints out information about the failed sensors and info text 
-- 2 : prints out warnings if test entries are missing for devices or sensors 
-- 3 : if test entries for devices miss we throw an error 

DEBUG_OUTPUT = 0

-- The result of the text will be a value in status and some information text in info text 
-- following values are possible for the test status of a sensor :
	-- 0: PASS ALL FITS
	-- 1: There's no test entry for the row, thus we do not need a test 
	-- 2: Wrong color as saturation fits but the wavelength does not 
	-- 3: Wavelength fits but saturation does not 
	-- 4: Neither wavelength nor saturation fit (environmental lightning ?)
	-- if You can optionally pass a lux_check_enable parameter, it is not nil then 
	-- the test will also check for the brightness (illumination) of the LED
	-- 0: color ok, sat ok, brightness ok 
	-- 5: color ok, sat ok, brightness too low 
	-- 6: color ok, sat ok, brightness too high 

function compareRows(tDUTrow, tCurColorSensor, lux_check_enable)
	
	-- The row in testboard exists, thus a test for this LED is desired 
	if tDUTrow ~= nil then 
		-- current values 
		local nm  = tCurColorSensor.nm 
		local sat = tCurColorSensor.sat 
		local lux = tCurColorSensor.lux 
		--tolerances 
		local tol_nm = tDUTrow.tol_nm 
		local tol_sat = tDUTrow.tol_sat 
		local tol_lux = tDUTrow.tol_lux 
		-- set points --
		local sp_nm = tDUTrow.nm 
		local sp_sat = tDUTrow.sat 
		local sp_lux = tDUTrow.lux 
		
		-- Saturation and wavelength fit 
		if  (nm  		  >= (sp_nm  - tol_nm)
		and  nm  		  <= (sp_nm  + tol_nm)
		and  sat 		  >= (sp_sat - tol_sat)
		and  sat		  <= (sp_sat + tol_sat)) then 		
		
			-- Brightness check is enabled
			if lux_check_enable ~= nil then 
					-- Brightness is OK --
					if (lux > (sp_lux - tol_lux)
					and lux < (sp_lux + tol_lux)) then 
						return 0, {"Wavelength   is in range",
								   "Saturation   is in range",
								   "Illumination is in range"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
					 
					-- Brightness falls below min_brightness
					elseif lux < (sp_lux - tol_lux) then
						return 5, {"Wavelength is in range",
								   "Saturation is in range",
								   "Illumination is too low"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
					-- Brightness exceeds max_brightness
					elseif lux > (sp_lux + tol_lux) then  
						return 6, {"Wavelength is in range",
								   "Saturation is in range",
								   "Illumination is too high"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
					end   
			--Brightness check is disabled 
			else 
				-- As wavelength and saturations are OK and there's no need for a lux check we can return OK here
				return 0, {"Wavelength is in range", 
						   "Saturation is in range",
						   "Illumination check is disabled"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
			end 
		-- Saturation fits but wavelength doesn't (wrong color)
		elseif ((nm  <= (sp_nm  - tol_nm) 
		or 	     nm  >= (sp_nm  + tol_nm))
		and      sat >= (sp_sat - tol_sat)
		and      sat <= (sp_sat + tol_sat)) then 
			return 2, {"Wavelength is not in range",
					   "Saturation is in range",
					   "Illumination was not tested"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
		-- Wavelength fits but saturation doesn't 
		elseif   (nm <= (sp_nm + tol_nm)
		and		  nm >= (sp_nm - tol_nm) 
		and		 (sat <= sp_sat - tol_sat
		or		  sat >= sp_sat + tol_sast)) then 
			return 3, {"Wavelength is in range",
					   "Saturation is not in range",
				       "Illumination was not tested"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
		-- Neither saturation nor wavelength fit --
		else 
			return 4, {"Wavelength is not in range",
					   "Saturation is not in range",
					   "Illumination was not tested"}, nm, sat, lux, tol_nm, tol_sat, tol_lux
		end 
	
	-- the row field is nil thus we do not need a test 
	else 
		return 1, {"NO TEST ENTRY",
				   "NO TEST ENTRY",
				   "NO TEST ENTRY"}, -1, -1, -1, -1, -1, -1
	end
	
end 	
	
-- function compareRows(tDUTrow, tCurColorSensor, lux_check_enable)
	
	-- -- The row in testboard exists, thus a test for this LED is desired 
	-- if tDUTrow ~= nil then 
		-- -- d prefix describes a delta value 
		-- local dnm = tCurColorSensor.nm - tDUTrow.nm 
		-- local dsat = tCurColorSensor.sat - tDUTrow.sat
		-- local dlux 
		
		-- if lux_check_enable ~= nil then 
			-- dlux = tCurColorSensor.lux - tDUTrow.lux 
		-- else 
			-- dlux = 0 
		-- end 
		
		-- -- Saturation and wavelength fit 
		-- if  (tCurColorSensor.nm  		  >= (tDUTrow.nm  - tDUTrow.tol_nm)
		-- and  tCurColorSensor.nm  		  <= (tDUTrow.nm  + tDUTrow.tol_nm)
		-- and  tCurColorSensor.sat 		  >= (tDUTrow.sat - tDUTrow.tol_sat)
		-- and  tCurColorSensor.sat		  <= (tDUTrow.sat + tDUTrow.tol_sat)) then 
		
			-- -- Brightness check is enabled
			-- if lux_check_enable ~= nil then 
				-- if (tDUTrow.lux ~= nil) and (tDUTrow.tol_lux ~= nil) then 
					-- -- Brightness is OK --
					-- if tCurColorSensor.lux > (tDUTrow.lux - tDUTrow.tol_lux)
					-- and tCurColorSensor.lux < (tDUTrow.lux + tDUTrow.tol_lux) then 
						-- return 0, string.format("%s LED with %3d nm OK - PASS!", tReferenceLEDcolors[tDUTrow.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
					 
					-- -- Brightness falls below min_brightness
					-- elseif tCurColorSensor.lux < (tDUTrow.lux - tDUTrow.tol_lux) then
						-- return 5, "LED too dark!\n			Check if right series resisor is used.", dnm, dsat, dlux
					 
					-- -- Brightness exceeds max_brightness
					-- elseif tCurColorSensor.lux > (tDUTrow.lux + tDUTrow.tol_lux) then  
						-- return 6, "LED too bright!\n			Check if right series resistor is used.\n			Check if shortcuts exists on the board", dnm, dsat, dlux
					-- end   
				-- elseif tDUTrow.lux == nil and tDUTrow.tol_lux ~= nil then 
						-- return 7, "value for lux or tol_lux is missing, please check.\n"
				
				-- elseif tDUTrow.lux ~= nil and tDUTrow.tol_lux == nil then 
						-- return 7, "value for lux or tol_lux is missing, please check.\n"
				-- end 
				
			-- --Brightness check is disabled 
			-- else 
				-- -- As wavelength and saturations are OK and there's no need for a lux check we can return OK here
				-- return 0, string.format("%s LED with %3d nm OK - PASS!", tReferenceLEDcolors[tDUTrow.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
			-- end 
		
		-- -- Saturation fits but wavelength doesn't (wrong color)
		-- elseif ((tCurColorSensor.nm  <= (tDUTrow.nm  - tDUTrow.tol_nm) 
		-- or 	     tCurColorSensor.nm  >= (tDUTrow.nm  + tDUTrow.tol_nm))
		-- and      tCurColorSensor.sat >= (tDUTrow.sat - tDUTrow.tol_sat)
		-- and      tCurColorSensor.sat <= (tDUTrow.sat + tDUTrow.tol_sat)) then 
			-- return 2, string.format("Wrong LED Color!\n			Want: %s with %3d nm\n 			Detected: %s with %3d nm", 
					-- tReferenceLEDcolors[tDUTrow.nm].colorname, tDUTrow.nm,
					-- tReferenceLEDcolors[tCurColorSensor.nm].colorname, tReferenceLEDcolors[tCurColorSensor.nm].nm), dnm, dsat, dlux
		
		-- -- Wavelength fits but saturation doesn't 
		-- elseif   (tCurColorSensor.nm <= (tDUTrow.nm + tDUTrow.tol_nm)
		-- and		  tCurColorSensor.nm >= (tDUTrow.nm - tDUTrow.tol_nm) 
		-- and		 (tCurColorSensor.sat <= tDUTrow.sat - tDUTrow.tol_sat
		-- or		  tCurColorSensor.sat >= tDUTrow.sat + tDUTrow.tol_sast)) then 
			-- return 3, string.format("Wrong Saturation!\n			Want: %3d sat\n 			Detected: %3d sat", 
					-- tDUTrow.sat, tCurColorSensor.sat) ,dnm, dsat, dlux
					
		-- -- Neither saturation nor wavelength fits --
		-- else 
			-- return 4, string.format("Both saturation and wavelength do not fit!\nWant %s with %3d nm and %3d sat \nDetected %s with %3d nm and %3d sat", 
				    -- tReferenceLEDcolors[tDUTrow.nm].colorname, tDUTrow.nm, tDUTrow.sat,
					-- tReferenceLEDcolors[tCurColorSensor.nm].colorname, tCurColorSensor.nm, tCurColorSensor.sat),
					-- dnm, dsat, dlux
		-- end 
	
	-- -- the row field is nil thus we do not need a test 
	-- else 
		-- return 1, "NO TEST ENTRY", 0, 0, 0
	-- end 
	
-- end 
	 
	 
	 
function getDeviceSummary(tDUT, tCurColors, lux_check_enable)
	
	local tTestSummary_device = {}
	local status, infotext, nm, sat, lux, tol_nm, tol_sat, tol_lux 
	

	if tDUT ~= nil then 
		for sensor = 1, MAXSENSORS do 
				tTestSummary_device[sensor] = {}
				status, infotext, nm, sat, lux, tol_nm, tol_sat, tol_lux = compareRows(tDUT[sensor], tCurColors[sensor], lux_check_enable)
				tTestSummary_device[sensor].status 	 = status
				tTestSummary_device[sensor].infotext = infotext
				tTestSummary_device[sensor].nm  	 = nm 
				tTestSummary_device[sensor].sat 	 = sat  
				tTestSummary_device[sensor].lux 	 = lux  
				tTestSummary_device[sensor].tol_nm   = tol_nm  
				tTestSummary_device[sensor].tol_sat  = tol_sat   
				tTestSummary_device[sensor].tol_lux  = tol_lux  
		end 
	else 
		for sensor = 1, MAXSENSORS do 
				tTestSummary_device[sensor] = {}
				tTestSummary_device[sensor].status 	 = 1 -- means no test entry 
				tTestSummary_device[sensor].infotext = {"NO TEST ENTRY","NO TEST ENTRY","NO TEST ENTRY"} 
				tTestSummary_device[sensor].nm  	 = -1  
				tTestSummary_device[sensor].sat 	 = -1   
				tTestSummary_device[sensor].lux 	 = -1   
				tTestSummary_device[sensor].tol_nm   = -1   
				tTestSummary_device[sensor].tol_sat  = -1    
				tTestSummary_device[sensor].tol_lux  = -1 
		end 
	end  
	
	return tTestSummary_device 
end 


-- prints a test summary for a device 
function printDeviceSummary(tTestSummary_device, info_enable)

	-- if(tTestSummary_device ~= nil) then  
		-- print("Sensor -------- Status --------- nm ----------- sat -------- lux") 
		-- for i = 1, 16 do 
			-- if(tTestSummary_device[i] ~= nil) then 
				-- print(string.format("%2d	 	 %2d		%3d		%3d		%5d", i, tTestSummary_device[i].status, tTestSummary_device[i].nm, 
				-- tTestSummary_device[i].sat, tTestSummary_device[i].lux))
				-- if info_enable >= 1 then 	
					-- print(tTestSummary_device[i].infotext)
				-- end 
			-- end
		-- end 
	-- end

	for iSensorIndex, tTestrowDevice in pairs(tTestSummary_device) do 
		print("Sensor -------- Status --------- nm ----------- sat ------------- lux") 		
		if tTestrowDevice ~= nil then 
			print(string.format("%2d	 	 %2d		%3d		%3d		%5d", iSensorIndex, tTestrowDevice.status, tTestrowDevice.nm, 
			tTestrowDevice.sat, tTestrowDevice.lux))
			if info_enable >= 1 then 	
				for iIndex, strText in ipairs(tTestrowDevice.infotext) do 
					print(strText)
				end 
			end
		end 
	end 
end 


function validateTestSummary(numberOfDevices, tTestSummary)
	-- Iterate over all device summaries
	local devIndex
	local errorFlag = 0 
	
	-- check for missing device entries and warn --
	devIndex = 0
	while(devIndex < numberOfDevices) do 
		if(tTestSummary[devIndex] == nil) then 
			if DEBUG_OUTPUT >= 2 then 
				print(string.format("\n!!!!! WARNING !!!!!  WE HAVE %2d DEVICES BUT TEST ENTRY FOR DEVICE %d IS MISSING.\n", numberOfDevices, devIndex))
			end  
			if DEBUG_OUTPUT >= 3 then
				print(string.format("\n!!!!! QUITTING !!!!! \n", numberOfDevices, devIndex))
				error(string.format("We have %2d devices connected but fewer device entries in the testsets!", numberOfDevices)) 
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
					if DEBUG_OUTPUT >= 1 then 
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
		
		return TEST_RESULT_OK 
	-- else the test was not successfull --
	else 
		print("")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!       ERROR       !!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!			!!!!!!!!!!!!!")
		print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
		print("")
		
		return TEST_RESULT_FAIL
	end 
	
end  

-- returns nil if no error occured 
-- returns iDevIndex (starts with 0) iSensorIndex ( starts with 1) and the infotext of the first sensor that failed
function errorsOccured(tTestSummary)
	local atErrors = {}
	local error_occured = false 
	for iDevIndex, tTestSummaryDevice in pairs(tTestSummary) do 
		for iSensorIndex, tTestrowDevice in pairs(tTestSummaryDevice) do 
			-- Status was not okay -- 
			if tTestrowDevice.status ~= 0 then 
				--return iDevIndex, iSensorIndex, tTestrowDevice.infotext 
				table.insert(atErrors, string.format("%2d", iDevIndex*16+iSensorIndex))
				error_occured = true 
			end 
		end 
	end 

	return error_occured, table.concat(atErrors, ",")

end 


