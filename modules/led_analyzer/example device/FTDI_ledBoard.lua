require("ul_ftdi")
--[[
        io.ftdi.ndevs() - get number of connected devices
        io.ftdi.devs() - get array of connected devices as Dev objects
        dev = io.ftdi.open(n) - open n-th device (starting from 1)
        dev:latency() - get latency timer (ms)
        dev:latency(2) - set latency timer (ms)
        dev:BM() - get bit mode
        dev:BM(dev.modes.BM_SYNC, 15) - switch to synchronous mode
        dev:BM(0) - reset back to default mode (serial port)
        dev:baud() - get current baud rate
        dev:baud(9600) - set communication speed to 9600x16 Bps
        dev:write(string.rep('U',100)) - send 100 bytes 0x55
        rxNum = dev:availRX() - get count of bytes in receive buffer
        buf = dev:read() - read received bytes
        timeout = dev:waitRX(100, 100); if timeout > 0 then buf = dev:read() end
            - wait for reception of 100 bytes with 10ms timeout.
              If timeout not occured - read received data.
        dev:close() - close device
--]]

function sleep(s)
	local t0 = os.time()
	while os.difftime(os.time(), t0) < s do 
	end
end	

CMD_SET_GPIO_LOW = 0x80   -- write AD / BD 
CMD_SET_GPIO_HIGH = 0x82  -- write AC / BC 
CMD_READ_GPIO_LOW = 0x81  -- read  AD / BD 
CMD_READ_GPIO_HIGH = 0x83 -- read  AC / BC 


local tDevA
local tDevB

function init_openFTDI() 
	iDevs = io.ftdi.ndevs()
	atDevs = io.ftdi.devs()

	for iDev = 1, iDevs do
		local dev = atDevs[iDev]
		print("Device ", iDev)
		for k,v in pairs(dev) do print(k,v) end
		print()
		print()
	end

	tDevA = io.ftdi.open(1)
	tDevB = io.ftdi.open(2)
	assert(tDevA)
	assert(tDevB)
	tDevA:BM(io.ftdi.MODES.BM_MPSSE)
	tDevB:BM(io.ftdi.MODES.BM_MPSSE)

end 

function onLED_red(lednr)
	if(lednr ~= nil) then
	tDevA:write(string.char(CMD_SET_GPIO_LOW,  lednr, 0xff))
	tDevA:write(string.char(CMD_SET_GPIO_HIGH, lednr, 0xff))
	
	else 
	tDevA:write(string.char(CMD_SET_GPIO_LOW,  0xff, 0xff))
	tDevA:write(string.char(CMD_SET_GPIO_HIGH, 0xff, 0xff))	
	end 
end 

function offLED_red()
	tDevA:write(string.char(CMD_SET_GPIO_LOW, 0x00, 0xff))
	tDevA:write(string.char(CMD_SET_GPIO_HIGH, 0x00, 0xff))
end 
	
function onLED_green(lednr)
	if(lednr ~= nil) then 
	tDevB:write(string.char(CMD_SET_GPIO_LOW, lednr, 0xff))
	tDevB:write(string.char(CMD_SET_GPIO_HIGH, lednr, 0xff))
	else 
	tDevB:write(string.char(CMD_SET_GPIO_LOW, 0xff, 0xff))
	tDevB:write(string.char(CMD_SET_GPIO_HIGH, 0xff, 0xff))	
	end 
end 

function offLED_green()
	tDevB:write(string.char(CMD_SET_GPIO_LOW, 0x00, 0xff))
	tDevB:write(string.char(CMD_SET_GPIO_HIGH, 0x00, 0xff))
end 

function close_FTDI()
	tDevA:close()
	tDevB:close()
end 

function offLEDs()
	tDevA:write(string.char(CMD_SET_GPIO_LOW, 0x00, 0xff))
	tDevA:write(string.char(CMD_SET_GPIO_HIGH, 0x00, 0xff))
	tDevB:write(string.char(CMD_SET_GPIO_LOW, 0x00, 0xff))
	tDevB:write(string.char(CMD_SET_GPIO_HIGH, 0x00, 0xff))
end 


