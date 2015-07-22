function generate_xml(tTestSummary)

		f = io.open("xmlfile.xml", "w")
		gen_xmlHeader(f)
		f:write("<LuaReport>\n")
		gen_version(f)
		
		-- check if errors occured --
		local error_occured, strErrored = errorsOccured(tTestSummary)
		-- iDevIndex = nil if no errors occured 
		if error_occured == false then 
			gen_result(f, "pass", "All readings ok!")
		else 
			gen_result(f, "interrupt", string.format("Errors with LED(s) -%s", strErrored ))
		end 
		-- generate traces 
		gen_traces(f, tTestSummary)
		
		f:write("</LuaReport>\n")
		f:close()

end 

function gen_xmlHeader(filehandle, version, encoding)
	local lStrVersion 
	local lStrEncoding 
	
	if filehandle then 
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
		filehandle:write(string.format("<?xml version=\"%s\" encoding=\"%s\"?>\n", lStrVersion, lStrEncoding))
		
	else
		error("no xml file opened")
	end 

end 

function gen_version(filehandle, major, minor)
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
	
	filehandle:write(string.format("	<Version minor=\"%d\" major=\"%d\"/>\n", lMinor, lMajor))
	
end 

function gen_result(filehandle, result, description)
	
	filehandle:write(string.format("	<Result description=\"%s\" result=\"%s\"/>\n", description, result))
	
end 


-- returns nil if no error occured 
-- returns iDevIndex (starts with 0) iSensorIndex ( starts with 1) and the infotext of the first sensor that failed
function gen_traces(filehandle, tTestSummary)
	
	filehandle:write("	<Traces>\n")
	for iDevIndex, tTestSummaryDevice in pairs(tTestSummary) do 
		for iSensorIndex, tTestrowDevice in pairs(tTestSummaryDevice) do 
			if tTestrowDevice.status ~= 1 then 
				filehandle:write(string.format("		<Trace maxThreshold=\"\" minThreshold=\"\" unit=\"nm\"  value=\"%3d\" message=\"#%2d - %s\"/>\n", tTestrowDevice.nm,
												(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[1]))
				filehandle:write(string.format("		<Trace maxThreshold=\"\" minThreshold=\"\" unit=\"%%\"   value=\"%3d\" message=\"#%2d - %s\"/>\n", tTestrowDevice.sat,
												(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[2]))
				filehandle:write(string.format("		<Trace maxThreshold=\"\" minThreshold=\"\" unit=\"lux\" value=\"%3d\" message=\"#%2d - %s\"/>\n", tTestrowDevice.lux,
												(iDevIndex*16 + iSensorIndex), tTestrowDevice.infotext[3]))
			end 
		end 					
	end 
	filehandle:write("	</Traces>\n")
end

