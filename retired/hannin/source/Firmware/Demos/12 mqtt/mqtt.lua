--mqtt demo
print("------mqtt demo------")

cfg={};cfg.ssid='Doit';cfg.pwd='doit3305';wifi.startsta(cfg);cfg=nil;

tmr.start(1,1000,function()
	print('Check STA Status:'..wifi.sta.getip())
	if(wifi.sta.getip()~='0.0.0.0') then
		tmr.stop(1)
		doMQTT()
	end
end)
 
function doMQTT()
	clientid = "wifimcu"
	keepalive = 30
	username = 'DOIT-SN-67A0-70334'
	password = '3aad0f59af42691eed72769bda7c34f2'
	mqttClt	= mqtt.new(clientid,keepalive, username,password)
	mqtt.on(mqttClt,'connect',function() 
		print('mqtt connected to server')
		topic = username
		QoS = mqtt.QOS0
		mqtt.subscribe(mqttClt,topic,QoS)
		print('mqtt subscribe topic:'..topic)
	end)
	mqtt.on(mqttClt,'offline',function()
		print('mqtt disconnected from server')
	end)
	mqtt.on(mqttClt,'message',cb_messagearrived)
	--server = "test.mosquitto.org"
	--server = 'mqtt.doit.am'
	server = 'wechat.doit.am'
	port = 1883
	mqtt.start(mqttClt,server,port)
end
--mqtt.publish(mqttClt,topic,mqtt.QOS0, 'hiwifimcu')
function cb_messagearrived(topic,message)
	print('[Message Arrived]\r\ntopic:'..topic..' \r\nmessage:'..message)
end
