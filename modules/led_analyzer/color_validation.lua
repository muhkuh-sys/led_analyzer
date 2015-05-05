

-- tReferenceColorSensor is a row in testboard.lua which contains LED, sat, lux and nm values and tolerances
-- tnm is a row with a .nm value 

function compareRows(tReferenceColorSensor, tCurColorSensor, lux_check_enable)
	
	-- The row in testboard exists, thus a test for this LED is desired 
	if tReferenceColorSensor ~= nil then 
		-- d prefix describes a delta value 
		local dnm = tCurColorSensor.nm - tReferenceColorSensor.nm 
		local dsat = tCurColorSensor.sat - tReferenceColorSensor.sat
		local dlux 
		
		if lux_check_enable >= 1 then 
			dlux = tCurColorSensor.lux - tReferenceColorSensor.lux 
		else 
			dlux = 0 
		end 
		
		-- Saturation and wavelength fit 
		if  (tCurColorSensor.nm  		  >= (tReferenceColorSensor.nm  - tReferenceColorSensor.tol_nm)
		and  tCurColorSensor.nm  		  <= (tReferenceColorSensor.nm  + tReferenceColorSensor.tol_nm)
		and  tCurColorSensor.sat 		  >= (tReferenceColorSensor.sat - tReferenceColorSensor.tol_sat)
		and  tCurColorSensor.sat		  <= (tReferenceColorSensor.sat + tReferenceColorSensor.tol_sat)) then 
		
			-- Brightness check is enabled 
			if lux_check_enable >= 1 then 
				-- Brightness is OK --
				if tCurColorSensor.lux > (tReferenceColorSensor.lux - tReferenceColorSensor.tol_lux)
				and tCurColorSensor.lux < (tReferenceColorSensor.lux + tReferenceColorSensor.tol_lux) then 
					return 0, string.format("%s LED with %d nm OK - PASS!\n", tReferenceLEDcolors[tReferenceColorSensor.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
				 
				-- Brightness falls below min_brightness
				elseif tCurColorSensor.lux < (tReferenceColorSensor.lux - tReferenceColorSensor.tol_lux) then
					return 1, "LED too dark -- Check if right series resisor is used\n", dnm, dsat, dlux
				 
				-- Brightness exceeds max_brightness
				elseif tCurColorSensor.lux > (tReferenceColorSensor.lux + tReferenceColorSensor.tol_lux) then  
					return 2, "LED too bright -- Check if right series resistor is used or shortcuts exists on the board\n", dnm, dsat, dlux
				end   
			
			--Brightness check is disabled 
			else 
				-- As wavelength and saturations are OK and there's no need for a lux check we can return OK here
				return 0, string.format("%s LED with %d nm OK - PASS!", tReferenceLEDcolors[tReferenceColorSensor.nm].colorname, tCurColorSensor.nm), dnm, dsat, dlux
			end 
		
		-- Saturation fits but wavelength doesn't 
		elseif ((tCurColorSensor.nm  <= (tReferenceColorSensor.nm  - tReferenceColorSensor.tol_nm) 
		or 	     tCurColorSensor.nm  >= (tReferenceColorSensor.nm  + tReferenceColorSensor.tol_nm))
		and      tCurColorSensor.sat >= (tReferenceColorSensor.sat - tReferenceColorSensor.tol_sat)
		and      tCurColorSensor.sat <= (tReferenceColorSensor.sat + tReferenceColorSensor.tol_sat)) then 
			return 3, string.format("Wrong LED Color! Want: %s with %d nm -- Detected: %s with %d nm\n", tReferenceLEDcolors[tReferenceColorSensor.nm].colorname,
					tReferenceLEDcolors[tReferenceColorSensor.nm].nm, tReferenceLEDcolors[tCurColorSensor.nm].colorname, tReferenceLEDcolors[tCurColorSensor.nm].nm), dnm, dsat, dlux
			
		-- Neither saturation nor wavelength fit -- NO LED 
		else 
			return 4, "NO LED detected!\n", dnm, dsat, dlux
		end 
	
	-- the wavelength field in the row for testboard does not exist, thus we do not need to test this LED "
	else 
		return 0, "NO TEST ENTRY\n", 0, 0, 0
	end 
	
end 
	
	 
-- Checks if the LEDs measured by a device are correct 
function inRange(tReferenceColors, tCurColors, lux_check_enable)
	local tTestSummary_device = {}
	
	local status, infotext, dnm, dsat, dlux
	
	for sensor = 1, 16 do 
			tTestSummary_device[sensor] = {}
			status, infotext, dnm, dsat, dlux = compareRows(tReferenceColors[sensor], tCurColors[sensor], lux_check_enable)
			tTestSummary_device[sensor].status = status
			tTestSummary_device[sensor].infotext = infotext
			tTestSummary_device[sensor].dnm  = dnm 
			tTestSummary_device[sensor].dsat = dsat  
			tTestSummary_device[sensor].dlux = dlux  
	end 
	
	return tTestSummary_device 
end 


function getDeviceSummary(tReferenceColors, tCurColors, lux_check_enable)
	
	local tTestSummary_device = {}
	
	if(tReferenceColors ~= nil) then 
			  tTestSummary_device = inRange(tReferenceColors, tCurColors, lux_check_enable)
	end 
	
	return tTestSummary_device 
end 


-- prints a test summary for a device 
function printDeviceSummary(tTestSummary_device, info_enable)

	if(tTestSummary_device ~= nil) then  
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dlux") 
		for i = 1, 16 do 
			if(tTestSummary_device[i] ~= nil) then 
				print(string.format("%2d	 	 %2d		%3d		%2.2f		%1.5f", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
				tTestSummary_device[i].dsat, tTestSummary_device[i].dlux))
				if info_enable >= 1 then 	
					print(tTestSummary_device[i].infotext)
				end 
			end
		end 
	end 

end 

function validateTestSummary(numberOfDevices, tTestSummary)
	-- Iterate over all device summaries
	local devIndex = 0
	local errorFlag = 0 
	
	print("\n\n")
	while(devIndex < numberOfDevices) do
		if(tTestSummary[devIndex] ~= nil) then 
			for i = 1, 16 do
				if tTestSummary[devIndex][i] ~= nil then 
					if tTestSummary[devIndex][i].status ~= 0 then 
						print(string.format("Device %2d Sensor %2d --- 	dnm: %3d, 	dsat: %2.2f,	 dlux %1.5f", 
											devIndex, i, tTestSummary[devIndex][i].dnm, tTestSummary[devIndex][i].dsat, tTestSummary[devIndex][i].dlux))
						print(tTestSummary[devIndex][i].infotext)					
						errorFlag = 1
					end 
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
	end 
	print("\n\n")
	
end  
