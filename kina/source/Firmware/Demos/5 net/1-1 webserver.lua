--net demo
print("------net demo------")
print("------webserver demo------")

cfg={ssid = 'WiFiMCU_Wireless',pwd = ''}
wifi.startap(cfg)
cfg=nil

skt = net.new(net.TCP,net.SERVER) 
net.on(skt,"accept",function(clt,ip,port) 
print("accept ip:"..ip.." port:"..port.." clt:"..clt) 
net.send(clt,[[HTTP/1.1 200 OK
Server: WiFiMCU
Content-Type:text/html
Content-Length: 28
Connection: close


<h1>Welcome to WiFiMCU!</h1>]])
end)
net.start(skt,80) 