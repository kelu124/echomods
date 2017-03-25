--fogcloud demo
print("------fogcloud demo------")

--全局变量定义
router_ssid='Doit' --无线路由器ssid
router_psw='doit3305' --无线路由器密码
product_id='b6ad115f' --产品id
_,_,_,_,_,mac = wifi.sta.getipadv() --获取模块mac
product_secret_key = '530026c7-8297-43df-ba7a-fce7bf345376' --产品秘钥
string.md5calc(mac..product_secret_key) --生成md5加密秘钥
secret_key = string.md5()
user_id = '9b1bf219-90f9-40eb-ba99-f8aa353bc8a3' --app的user_id
url = 'api.easylink.io' --fogcloud url地址
port = 80	--端口

--连接到无线路由器
cfg={ssid=router_ssid,pwd=router_psw}
wifi.startsta(cfg)
cfg=nil
product_secret_key = nil
--使用定时器检查是否连接成功
tmr.start(1,1000,function()
	print('Check STA Status:'..wifi.sta.getip())
	if(wifi.sta.getip()~='0.0.0.0') then
		tmr.stop(1)
		fogRegist()
	end
end)

--连接成功后，首先注册
function fogRegist()
	print("[fogRegist]")
	skt = net.new(net.TCP,net.CLIENT) 
	net.on(skt,"connect",function(skt) 
		print("connect to :"..url) 
		net.send(skt,'POST /v2/devices HTTP/1.0\r\n')
		net.send(skt,'Content-Type:application/json; charset=utf-8\r\n')
		net.send(skt,'Host:api.easylink.io\r\n')
		local str1 = '{"product_id":"'..product_id..'",'
		local str2 = '"MAC":"'..mac..'",'
		local str3 = '"secret_key":"'..secret_key..'",'
		local str = str1..str2..str3..'"alias":"wifimcu_d99346548d63","encrypt_method":"MD5"}'
		net.send(skt,'Content-Length:'..string.len(str)..'\r\n\r\n')
		--print(str)
		net.send(skt,str)
		str1=nil;str2=nil;str3=nil;str=nil
	end)
	net.on(skt,"receive",function(skt,d)
		print("[Receive from server]")
		print(d)
		net.close(skt)
		fogBind()
	end)
	net.on(skt,"dnsfound",function(skt,ip) 
		print("dnsfound: skt:"..skt.." ip:"..ip)
	end)
	net.start(skt,port,url) 
end

--注册完成后，绑定user_id
function fogBind()
print("[fogBind]")
	skt = net.new(net.TCP,net.CLIENT) 
	net.on(skt,"connect",function(skt) 
		print("connect to :"..url) 
		print('[ready to bind]')
		net.send(skt,'POST /v2/devices/bind HTTP/1.0\r\n')
		net.send(skt,'Content-Type:application/json; charset=utf-8\r\n')
		net.send(skt,'Host:api.easylink.io\r\n')
		local str1 = '{"product_id":"'..product_id..'",'
		local str2 = '"user_id":"'..user_id..'",'
		local str3 = '"MAC":"'..mac..'",'
		local str4 = '"secret_key":"'..secret_key..'",'
		local str = str1..str2..str3..str4..'"bind_mode":"3","encrypt_method":"MD5"}'
		net.send(skt,'Content-Length:'..string.len(str)..'\r\n\r\n')
		--print(str)
		net.send(skt,str)
		str1=nil;str2=nil;str3=nil;str=nil
	end)
	net.on(skt,"receive",function(skt,d)
		print("[Receive from server]")
		print(d)
		net.close(skt)
	end)
	net.on(skt,"dnsfound",function(skt,ip) 
		print("dnsfound: skt:"..skt.." ip:"..ip)
	end)
	net.start(skt,port,url) 
end

--使用udp server在8089端口监听udp广播，用户app通过udp广播发送user_id
print("udp server listen @8089 to recieve user_id")
udpSkt = net.new(net.UDP,net.SERVER)
net.on(udpSkt,"receive",function(clt,d)
	print("[Receive UDP]")
	print(d)
	user_id = d
	print('[user_id]:'..user_id)
	net.send(clt,'ok')
end)
net.start(udpSkt,8089) 