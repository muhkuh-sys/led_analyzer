

-- calculate the distance between 2 points v1 and v2  
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
	
