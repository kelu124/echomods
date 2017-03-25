--net demo
print("------net demo------")

--setup a ap
cfg={ssid = 'WiFiMCU_Wireless',pwd = ''}
wifi.startap(cfg)
cfg=nil

print("udp server started")
skt = net.new(net.UDP,net.SERVER)
net.on(skt,"sent",function(clt) print("sent:clt:"..clt) end)
net.on(skt,"disconnect",function(clt) print("disconnect:clt:"..clt) end)
net.on(skt,"receive",function(clt,d)
	print("Receive:"..d)
	net.send(clt,'From Server:'..d.."\n")
end)

net.start(skt,8000) 