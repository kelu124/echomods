--net demo
print("------net demo------")

--setup a wifi interface first
ap_ssid="Doit" --change to your ap ssid
ap_pwd="123456789" --change to your ap pwd
cfg={ssid = ap_ssid,pwd = ap_pwd}
wifi.startsta(cfg)
cfg=nil
ap_pwd=nil

--check if connect to ap
stat,_,_,_ = wifi.sta.getlink()
while stat ~= 'connected'   do
	print("Wating for connecting to AP:"..ap_ssid)
	tmr.delayms(1000)
	stat,_,_,_ = wifi.sta.getlink()
end
print("WiFiMCU connected to ap successful")

print("tcp client started")
skt = net.new(net.TCP,net.CLIENT) 
net.on(skt,"connect",function(skt) print("connect: skt:"..skt) end)
net.on(skt,"dnsfound",function(skt,ip) print("dnsfound: skt:"..skt.." ip:"..ip) end)
net.on(skt,"sent",function(skt) print("sent:skt:"..skt) end)
net.on(skt,"disconnect",function(skt) print("disconnect:skt:"..skt) end)
net.on(skt,"receive",function(skt,d)
	print("Receive:"..d)
	net.send(skt,'From Client:'..d.."\n")
end)
--connect to server(ip:192.168.1.105) at port 9001
net.start(skt,9001,"192.168.1.105") 

--connect to server(ip:192.168.1.105) at port 9001 with local port 8989
--net.start(skt,9001,"192.168.1.105",8989) 