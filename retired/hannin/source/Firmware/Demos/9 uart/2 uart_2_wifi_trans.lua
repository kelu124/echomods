--uart demo
print("------uart demo------")
--setup a ap
cfg={ssid = 'WiFiMCU_Wireless',pwd = ''}
wifi.startap(cfg)
cfg=nil

print("tcp server started")
skt = net.new(net.TCP,net.SERVER) 
uartClt = nil --save the clt socket
net.on(skt,"accept",function(clt,ip,port) uartClt = clt; end)
net.on(skt,"disconnect",function(clt) uartClt=nil end)
net.on(skt,"receive",function(clt,d)
	print("Receive:"..d)
	uartClt = clt
	--send to uart 1
	uart.send(1,d)
end)

net.start(skt,9000) 

--uart pin:D8(RX1), D9(TX1)
--setup uart
uart.setup(1,9600,'n','8','1')

function uartReceive(d)
	print("len(bytes)"..string.len(d).." data:"..d)
	if uartClt ~=nil then
		net.send(uartClt,d)
	end
end
uart.on(1, 'data',uartReceive)