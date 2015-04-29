



-- tTest = a row in the tTesttable containing name, dWavelength, tol, led_state ...
-- tnm is a row with a .nm value 

function compare(row_testboard, row_curset, brightness_check_enable)
	
	-- The row in testboard exists, thus a test for this LED is desired 
	if row_testboard.nm ~= nil then 
		local dnm = row_curset.nm - row_testboard.nm 
		local dsat = row_curset.sat - row_testboard.sat
		local dbrightness 
		
		if brightness_check_enable >= 1 then 
			dbrightness = row_curset.brightness - row_testboard.brightness 
		else 
			dbrightness = 0 
		end 
		
		-- Saturation and wavelength fit 
		if  (row_curset.nm  		  >= (row_testboard.nm  - row_testboard.tol_nm)
		and  row_curset.nm  		  <= (row_testboard.nm  + row_testboard.tol_nm)
		and  row_curset.sat 		  >= (row_testboard.sat - row_testboard.tol_sat)
		and  row_curset.sat		      <= (row_testboard.sat + row_testboard.tol_sat)) then 
		
			-- Brightness check is enabled 
			if brightness_check_enable >= 1 then 
				-- Brightness is OK --
				if row_curset.brightness > (row_testboard.brightness - row_testboard.tol_brightness)
				and row_curset.brightness < (row_testboard.brightness + row_testboard.tol_brightness) then 
					return 0, string.format("%s LED OK!", tReferenceColors[row_testboard.nm].colorname), dnm, dsat, dbrightness
				 
				-- Brightness falls below min_brightness
				elseif row_curset.brightness < (row_testboard.brightness - row_testboard.tol_brightness) then
					return 1, "LED too tark -- Check if right series resisor is used", dnm, dsat, dbrightness
				 
				-- Brightness exceeds max_brightness
				elseif row_curset.brightness > (row_testboard.brightness + row_testboard.tol_brightness) then  
					return 2, "LED too bright -- Check if right series resistor is used or shortcuts exists on the board", dnm, dsat, dbrightness
				end   
			
			--Brightness check is disabled 
			else 
				-- As wavelength and saturations are OK and there's no need for a brightness check we can return OK here
				return 0, string.format("%s LED OK!", tReferenceColors[row_testboard.nm].colorname), 0, 0, 0
			end 
		
		-- Saturation fits but wavelength doesn't 
		elseif ((row_curset.nm  <= (row_testboard.nm  - row_testboard.tol_nm) 
		or 	     row_curset.nm  >= (row_testboard.nm  + row_testboard.tol_nm))
		and      row_curset.sat >= (row_testboard.sat - row_testboard.tol_sat)
		and      row_curset.sat <= (row_testboard.sat + row_testboard.tol_sat)) then 
			-- We probly have a wrong LED in place 
			return 3, string.format("Wrong LED Color! Want: %s with %d nm -- Detected: %s with %d nm", tReferenceColors[row_testboard.nm].colorname,
					tReferenceColors[row_testboard.nm].nm, tReferenceColors[row_curset.nm].colorname, tReferenceColors[row_curset.nm].nm), dnm, dsat, dbrightness
		-- Neither saturation nor wavelength fit -- NO LED 
		else 
			return 4, "NO LED detected!", dnm, dsat, dbrightness
		end 
	
	-- the wavelength field in the row for testboard does not exist, thus we do not need to test this LED "
	else 
		return 0, "NO TEST", 0, 0, 0
	end 
	
end 
	
	 
-- Checks if the LEDs measured by a device are correct 
function inRange(tTestDevice, tWavelengthDevice, brightness_check_enable)
	local tTestSummary_device = {}
	
	local status, infotext, dnm, dsat, dbrightness
	for sensor = 1, 16 do 
		tTestSummary_device[sensor] = {}
		
		status, infotext, dnm, dsat, dbrightness = compare(tTestDevice[sensor], tWavelengthDevice[sensor], brightness_check_enable)
		
		tTestSummary_device[sensor].status = status
		tTestSummary_device[sensor].infotext = infotext
		-- measurement error = x_measured - x_correct
		tTestSummary_device[sensor].dnm  = dnm 
		tTestSummary_device[sensor].dsat = dsat  
		tTestSummary_device[sensor].dbrightness = dbrightness  
	end 
	
	return tTestSummary_device 
	
end 


function validate_device_colors(tTestDevice, tWavelengthDevice, brightness_check_enable)

		local tTestSummary_device = {} 
		tTestSummary_device = inRange(tTestDevice, tWavelengthDevice, brightness_check_enable)
	 
	 
		return tTestSummary_device 
end 


-- prints a test summary for a device 
function print_deviceSummary(tTestSummary_device, info_enable)

	if info_enable >= 0 then 
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dbrightness")
	else 
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dbrightness")
	end 
	
	for i = 1, 16 do 
		if info_enable >= 1 then 
			print(string.format("%2d	 	 %2d		%3d		%2.2f		%1.5f", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
			tTestSummary_device[i].dsat, tTestSummary_device[i].dbrightness))
			print(tTestSummary_device[i].infotext)
		else 
			print(string.format("%2d 		 %2d		%3d		%2.2f		%1.5f", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
			tTestSummary_device[i].dsat, tTestSummary_device[i].dbrightness))
		end 
	end 

end 

