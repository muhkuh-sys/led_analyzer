-- a helper to print a color table 
function print_color(devIndex, colortable, length, mode)
	print(string.format("\n"))
	print(string.format("------------------- Colors --------------------- ", devIndex))
	
	
	if mode == "RGB" then 
		print("     Clear   Red     Green    Blue")
		for i=1,length do
		   print(string.format("%2d - 0x%04x, 0x%04x, 0x%04x, 0x%04x", i, colortable[devIndex+1][i].clear,
													colortable[devIndex+1][i].red, colortable[devIndex+1][i].green,
													colortable[devIndex+1][i].blue))
		end
	
	elseif mode == "RGB_n" then
		print("     Clear   Red     Green    Blue")
		for i=1,length do
		   print(string.format("%2d - 0x%04x, %.5f, %.5f, %.5f", i, colortable[devIndex+1][i].clear,
													(colortable[devIndex+1][i].red/colortable[devIndex+1][i].clear)*255, 
													(colortable[devIndex+1][i].green/colortable[devIndex+1][i].clear)*255,
													(colortable[devIndex+1][i].blue/colortable[devIndex+1][i].clear)*255))
		end
		
	elseif mode == "XYZ" then
		print("     X        Y	       Z    ")
		for i=1, length do
			print(string.format("%2d - %.5f, %.5f, %.5f", i, colortable[devIndex+1][i].X,
											colortable[devIndex+1][i].Y, colortable[devIndex+1][i].Z))
		end
		
	elseif mode == "Yxy" then
		print("     Y        x	       y    ")
		for i=1, length do
			print(string.format("%2d - %.7f, %.7f, %.7f", i, colortable[devIndex+1][i].Y,
											colortable[devIndex+1][i].x, colortable[devIndex+1][i].y))
		end
		
	elseif mode == "wavelength" then
	    print(" dominant wavelength	              saturation  ")
		for i=1, length do
			print(string.format("%2d)   %3.3f nm, 			%.2f ", i, colortable[devIndex+1][i].nm, colortable[devIndex+1][i].sat))
		end								
	
	elseif mode == "HSV" then
	print("     H        S	       V    ")
		for i=1,length do
		   print(string.format("%2d -  %.5f, %.5f, %.5f", i, 
													colortable[devIndex+1][i].H,
													colortable[devIndex+1][i].S,
													colortable[devIndex+1][i].V))
		end	
		
	elseif mode == "test" then
	print("	x	y ")
			print(string.format("%.8f %.8f", colortable[devIndex+1][8].x, colortable[devIndex+1][8].y))
	end 
	print("\n")
end

--print(string.format("0x%04x\n", tColor[1][1].clear))

function aus_to_table(devIndex, clear, red, green, blue, length)
	local x,y,z
	
	local tRGB = {}
	local tXYZ = {}
	local tYxy = {}
	local tnm = {}
	local tHSV = {}
	
	
	tRGB[devIndex+1] = {}
	tXYZ[devIndex+1] = {}
	tYxy[devIndex+1] = {}
	tnm[devIndex+1]  = {}
	tHSV[devIndex+1] = {}
	
	-- Lua starting index (1) differs from C index (0)
	for i = 0, length-1 do
		-- table containing sensorindices with R, G, B values 
		tRGB[devIndex+1][i+1] = {	clear = led_analyzer.ushort_getitem(clear, i),
								red   = led_analyzer.ushort_getitem(red, i),
								green = led_analyzer.ushort_getitem(green, i),
								blue  = led_analyzer.ushort_getitem(blue, i)}
		
		-- table containing sensorindices with X,Y,Z  values
		local r_n = led_analyzer.ushort_getitem(red, i)/led_analyzer.ushort_getitem(clear, i)
		local g_n = led_analyzer.ushort_getitem(green, i)/led_analyzer.ushort_getitem(clear, i)
		local b_n = led_analyzer.ushort_getitem(blue, i)/led_analyzer.ushort_getitem(clear, i)
		
		
		-- testing E 
		-- table containing XYZ values dependent on the RGB working space
		-- adobe, not good
		-- apple good for orange, worse for red 
		-- best rgb sucks 
		-- beta rgb good for red bad for orange, ok for green 
		-- similiar to srgb
		-- cie too strong reds and oranges 
		-- coloarmatch good for green, sux for others 
		-- ntsc ok for green, ok for red, bad for yellow 
		
		
		
		local X, Y, Z = RGB2XYZ(r_n, g_n, b_n, "sRGB")									  
		tXYZ[devIndex+1][i+1] = { X = X,
								  Y = Y,
								  Z = Z }
								  
								
								  
		-- table containing sensorindices with Yxy values
		local Y, x, y = XYZ2Yxy(X, Y, Z)
		local x_chroma = x
		local y_chroma = y
		tYxy[devIndex+1][i+1] = { Y = Y,
								  x = x,
								  y = y }
								  
		
		-- table containing sensorindices with wavelength in nanometers
		local wavelength, saturation = Yxy2wavelength(x_chroma, y_chroma)
		tnm[devIndex+1][i+1] = {nm = wavelength,
								sat = saturation*100}
		
		local H,S,V = RGB2HSV(r_n, g_n, b_n)
		tHSV[devIndex+1][i+1] = { H = H,
								  S = S,
								  V = V }
	
								
	end
	
	return tRGB, tXYZ, tYxy , tnm, tHSV
end

-- devIndex starts with 1, get first element with 1 => devIndex +1 
-- k = rowindex 
-- In tolerance range checks if the values which were returned by the sensor, are the ones looked for
-- If the measured LED lies in the tolerance range we return 0, else 13
-- The table we compare the measured sensor values to is found in tTest and contains EITHER 
-- the dominant wavelength searched for OR x and y chromaticity points, as some datasheets provide dom. wavelengths
-- and others provide the bins (x and y points)
-- If dom. wavelength, x and y chroma points are given, we will only evaluate wavelength


-- distance 
function get_distance(v1, v2)
	return math.sqrt(math.pow((v1.x - v2.x),2) + math.pow((v1.y - v2.y),2))
end 


-- tTest = a row in the tTesttable containing name, dWavelength, tol, led_state ...
-- tnm is a row with a .nm value 
function inToleranceRange(tTest, tnm, tYxy) 
	
	
	
	if tTest.dWavelength ~= nil then
			if tnm.nm > (tTest.dWavelength - tTest.tol_nm)
			and tnm.nm < (tTest.dWavelength + tTest.tol_nm) 
			and tnm.sat < (tTest.sat + (tTest.tol_sat/100)*tTest.sat)
			and tnm.sat > (tTest.sat - (tTest.tol_sat/100)*tTest.sat)then 
				return 0 

			else 
				if tnm.nm > (tTest.dWavelength - tTest.tol_nm)
				and tnm.nm < (tTest.dWavelength + tTest.tol_nm) then
					return 1 
				else 
					return 2
				end 
			end
			
			
		
	else
		if tTest.x ~= nil and tTest.y ~= nil then
			
			distance = get_distance(tTest, tYxy)
			if distance <= tTest.tol_xy then
				return 0 
			else 
				return 1
			end 
							
		else 
			print("Table needs input values! Either dom. wavelength or x/y points")
		end 
	end 
	
end 


function validate_color(tTest, tnm, tYxy)
	
	
	for k,v in ipairs(tTest) do
			if inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 0 then 
				tTest[k].LED_State = 1
			elseif inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 1 then
			    tTest[k].LED_State = 2 			
		    end 
	end 	
	 
end 
	-- k = 1 
			-- if inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 0 then 
				-- tTest[k].LED_State = 1
			
			-- elseif inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 1 then
				-- tTest[k].LED_State = 2 		
			-- end 

	-- k = 8
			-- if inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 0 then 
				-- tTest[k].LED_State = 1
			
			-- elseif inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 1 then
				-- tTest[k].LED_State = 2 
			-- end 
	
	-- k  = 13 
	
			-- if inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 0 then 
				-- tTest[k].LED_State = 1
			
			-- elseif inToleranceRange(tTest[k], tnm[k], tYxy[k]) == 1 then
				-- tTest[k].LED_State = 2 
			-- end 
	
--end 

function print_LEDs(tTest)
	local flag = 0
	for k,v in ipairs(tTest) do
		if tTest[k].LED_State ~=nil then
			if tTest[k].LED_State == 1 then
			 print(string.format("%i - %s found.", k, tTest[k].name))			
			
			
			 elseif tTest[k].LED_State == 2 then
		     print(string.format("%i, %s color recognized, but purity out of tolerance range.", k, tTest[k].name))
				
			else 
			 print(string.format("%i, %s NOT FOUND.", k, tTest[k].name))
				 flag = 0
			 end 
		 end
	 end
 end 

-- function print_LEDs(tTest)
-- k = 1
			-- if tTest[k].LED_State == 1 then
				-- print(string.format("%s found.", tTest[k].name))	
			
			-- elseif tTest[k].LED_State == 2 then
				-- print(string.format("%s color recognized, but purity out of tolerance range.", tTest[k].name))
			
			-- else 
				-- print(string.format("%s NOT FOUND.", tTest[k].name))
			-- end 
			
-- k = 8
			-- if tTest[k].LED_State == 1 then
				-- print(string.format("%s found.", tTest[k].name))	
			
			-- elseif tTest[k].LED_State == 2 then
				-- print(string.format("%s color recognized, but purity out of tolerance range.", tTest[k].name))
			
			-- else 
				-- print(string.format("%s NOT FOUND.", tTest[k].name))
			-- end 
			
-- k = 13 
			-- if tTest[k].LED_State == 1 then
				-- print(string.format("%s found.", tTest[k].name))	
			
			-- elseif tTest[k].LED_State == 2 then
				-- print(string.format("%s color recognized, but purity out of tolerance range.", tTest[k].name))
			
			-- else 
				-- print(string.format("%s NOT FOUND.", tTest[k].name))
			-- end 
-- end 
	
