--net demo
print("------net demo------")

--setup a ap
cfg={ssid = 'WiFiMCU_Wireless',pwd = ''}
wifi.startap(cfg)
cfg=nil

print("tcp server started")
skt = net.new(net.TCP,net.SERVER) 
net.on(skt,"accept",function(clt,ip,port) print("accept: client ip:"..ip.."port:"..port) end)
net.on(skt,"sent",function(clt) print("sent:clt:"..clt) end)
net.on(skt,"disconnect",function(clt) print("disconnect:clt:"..clt) end)
net.on(skt,"receive",function(clt,d)
	print("Receive:"..d)
	net.send(clt,'From Server:'..d.."\n")
end)

net.start(skt,9000) 