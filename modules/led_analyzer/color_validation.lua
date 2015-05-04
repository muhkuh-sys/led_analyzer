



-- tTest = a row in the tTesttable containing name, dWavelength, tol, led_state ...
-- tnm is a row with a .nm value 

function compare(row_testboard, row_curset, lux_check_enable)
	
	-- The row in testboard exists, thus a test for this LED is desired 
	if row_testboard.nm ~= nil then 
		local dnm = row_curset.nm - row_testboard.nm 
		local dsat = row_curset.sat - row_testboard.sat
		local dlux 
		
		if lux_check_enable >= 1 then 
			dlux = row_curset.lux - row_testboard.lux 
		else 
			dlux = 0 
		end 
		
		-- Saturation and wavelength fit 
		if  (row_curset.nm  		  >= (row_testboard.nm  - row_testboard.tol_nm)
		and  row_curset.nm  		  <= (row_testboard.nm  + row_testboard.tol_nm)
		and  row_curset.sat 		  >= (row_testboard.sat - row_testboard.tol_sat)
		and  row_curset.sat		      <= (row_testboard.sat + row_testboard.tol_sat)) then 
		
			-- Brightness check is enabled 
			if lux_check_enable >= 1 then 
				-- Brightness is OK --
				if row_curset.lux > (row_testboard.lux - row_testboard.tol_lux)
				and row_curset.lux < (row_testboard.lux + row_testboard.tol_lux) then 
					return 0, string.format("%s LED with %d nm OK - PASS!\n", tReferenceColors[row_testboard.nm].colorname, row_curset.nm), dnm, dsat, dlux
				 
				-- Brightness falls below min_brightness
				elseif row_curset.lux < (row_testboard.lux - row_testboard.tol_lux) then
					return 1, "LED too tark -- Check if right series resisor is used", dnm, dsat, dlux
				 
				-- Brightness exceeds max_brightness
				elseif row_curset.lux > (row_testboard.lux + row_testboard.tol_lux) then  
					return 2, "LED too bright -- Check if right series resistor is used or shortcuts exists on the board", dnm, dsat, dlux
				end   
			
			--Brightness check is disabled 
			else 
				-- As wavelength and saturations are OK and there's no need for a lux check we can return OK here
				return 0, string.format("%s LED with %d nm OK - PASS!\n", tReferenceColors[row_testboard.nm].colorname, row_curset.nm), dnm, dsat, dlux
			end 
		
		-- Saturation fits but wavelength doesn't 
		elseif ((row_curset.nm  <= (row_testboard.nm  - row_testboard.tol_nm) 
		or 	     row_curset.nm  >= (row_testboard.nm  + row_testboard.tol_nm))
		and      row_curset.sat >= (row_testboard.sat - row_testboard.tol_sat)
		and      row_curset.sat <= (row_testboard.sat + row_testboard.tol_sat)) then 
			-- We probly have a wrong LED in place 
			return 3, string.format("Wrong LED Color! Want: %s with %d nm -- Detected: %s with %d nm\n", tReferenceColors[row_testboard.nm].colorname,
					tReferenceColors[row_testboard.nm].nm, tReferenceColors[row_curset.nm].colorname, tReferenceColors[row_curset.nm].nm), dnm, dsat, dlux
			
		-- Neither saturation nor wavelength fit -- NO LED 
		else 
			return 4, "NO LED detected!", dnm, dsat, dlux
		end 
	
	-- the wavelength field in the row for testboard does not exist, thus we do not need to test this LED "
	else 
		return 0, "NO TEST", 0, 0, 0
	end 
	
end 
	
	 
-- Checks if the LEDs measured by a device are correct 
function inRange(tTestDevice, tWavelengthDevice, lux_check_enable)
	local tTestSummary_device = {}
	
	local status, infotext, dnm, dsat, dlux
	for sensor = 1, 16 do 
		tTestSummary_device[sensor] = {}
		
		status, infotext, dnm, dsat, dlux = compare(tTestDevice[sensor], tWavelengthDevice[sensor], lux_check_enable)
		
		tTestSummary_device[sensor].status = status
		tTestSummary_device[sensor].infotext = infotext
		-- measurement error = x_measured - x_correct
		tTestSummary_device[sensor].dnm  = dnm 
		tTestSummary_device[sensor].dsat = dsat  
		tTestSummary_device[sensor].dlux = dlux  
	end 
	
	return tTestSummary_device 
	
end 


function validate_device_colors(tTestDevice, tWavelengthDevice, lux_check_enable)

		local tTestSummary_device = {} 
		tTestSummary_device = inRange(tTestDevice, tWavelengthDevice, lux_check_enable)
	 
	 
		return tTestSummary_device 
end 


-- prints a test summary for a device 
function print_deviceSummary(tTestSummary_device, info_enable)

	if info_enable >= 0 then 
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dlux")
	else 
		print("Sensor -------- Status --------- dnm ----------- dsat -------- dlux")
	end 
	
	for i = 1, 16 do 
		if info_enable >= 1 then 
			print(string.format("%2d	 	 %2d		%3d		%2.2f		%1.5f", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
			tTestSummary_device[i].dsat, tTestSummary_device[i].dlux))
			print(tTestSummary_device[i].infotext)
		else 
			print(string.format("%2d 		 %2d		%3d		%2.2f		%1.5f", i, tTestSummary_device[i].status, tTestSummary_device[i].dnm, 
			tTestSummary_device[i].dsat, tTestSummary_device[i].dlux))
		end 
	end 

end 

