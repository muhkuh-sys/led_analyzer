function generate_xml(tTestSummary)
	local retStr 
		
	retStr = gen_xmlHeader()
	retStr = retStr .. ("<LuaReport>\n")
	retStr = retStr .. gen_version()
	
	-- check if errors occured --
	local error_occured, strErrored = errorsOccured(tTestSummary)
	-- iDevIndex = nil if no errors occured 
	if error_occured == false then 
		retStr = retStr .. gen_result("pass", "All readings ok!")
	else 
		retStr = retStr .. gen_result("interrupt", string.format("Errors with LED(s): %s", strErrored ))
	end 
	-- generate traces 
	retStr = retStr .. gen_traces(tTestSummary)
	
	retStr = retStr .. "</LuaReport>\n"
	
	return retStr 
	
end 

function gen_xmlHeader(version, encoding)
	local lStrVersion 
	local lStrEncoding

	if version then 
		lStrVersion = version 
	else 
		lStrVersion = "1.0"
	end 
	
	if encoding then 
		lStrEncoding = encoding 
	else 
		lStrEncoding = "UTF-8"
	end 
	
	-- Write to the xml file -- 
	return string.format("<?xml version=\"%s\" encoding=\"%s\"?>\n", lStrVersion, lStrEncoding)
		
end 

function gen_version(major, minor)
	local lMajor 
	local lMinor 
	
	if major then 
		lMajor = major 
	else 
		lMajor = 1
	end 
	
	if minor then 
		lMinor = minor
	else 
		lMinor = 0 
	end 
	
	return (string.format("	<Version minor=\"%d\" major=\"%d\"/>\n", lMinor, lMajor))
	
end 

function gen_result(result, description)
	
	return string.format("	<Result description=\"%s\" result=\"%s\"/>\n", description, result)
	
end 

 function truncate_min(value)
	if value < 0 then 
		value = 0
	end 
	
	return value 
end 

local function truncate_max(value)
	if value > 100 then 
		value = 100 
	end 
	
	return value 
end 

-- returns nil if no error occured 
-- returns iDevIndex (starts with 0) iSensorIndex ( starts with 1) and the infotext of the first sensor that failed
function gen_traces(tTestSummary)
	local retStr 
	local min_nm, min_sat, min_lux 
	local max_nm, max_sat, max_lux
	local tol_nm, tol_sat, tol_lux 
	
	retStr = ("	<Traces>\n")

	for iDevIndex, tTestSummaryDevice in pairs(tTestSummary) do 
		for iSensorIndex, tTestrowDevice in pairs(tTestSummaryDevice) do 
			tol_nm = tTestrowDevice.tol_nm 
			tol_sat = tTestrowDevice.tol_sat 
			tol_lux = tTestrowDevice.tol_lux 
			
			min_nm  = truncate_min(tTestrowDevice.sp_nm - tol_nm) 
			min_sat = truncate_min(tTestrowDevice.sp_sat - tol_sat)
			min_lux = truncate_min(tTestrowDevice.sp_lux - tol_lux)
			max_nm  = tTestrowDevice.sp_nm + tol_nm 
			max_sat = truncate_max(tTestrowDevice.sp_sat + tol_sat)
			max_lux = tTestrowDevice.sp_lux + tol_lux 
			
			
			if tTestrowDevice.status ~= 1 then			
				retStr = retStr .. (string.format("		<Trace minThreshold=\"%3d\" maxThreshold=\"%3d\" unit=\"nm\"  value=\"%3d\" message=\"#%2d - %s\"/>\n", 
									min_nm, max_nm, tTestrowDevice.nm,(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[1]))
				retStr = retStr .. (string.format("		<Trace minThreshold=\"%3d\" maxThreshold=\"%3d\" unit=\"%%\"   value=\"%3d\" message=\"#%2d - %s\"/>\n", 
									min_sat, max_sat, tTestrowDevice.sat,(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[2]))
				-- only show the illumination if it was really tested and it failed (that means status must be 5 or 6)
				if tTestrowDevice.infotext[3] ~= "Illumination was not tested" then 
					retStr = retStr .. (string.format("		<Trace minThreshold=\"%3d\" maxThreshold=\"%3d\" unit=\"lux\" value=\"%3d\" message=\"#%2d - %s\"/>\n", 
										min_lux, max_lux, tTestrowDevice.lux,(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[3]))
				end 
			end 
		end 					
	end 
	retStr = retStr .. ("	</Traces>\n")
	return retStr 
end
