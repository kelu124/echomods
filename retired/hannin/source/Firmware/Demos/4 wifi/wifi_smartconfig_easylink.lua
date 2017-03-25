--this is a demo

print('It is recommand to start smartconfig function without setting up AP or STA')
print('start smartconfig')

easylink=0
airkiss=1
timeout=60
wifi.smartconfig(easylink,timeout,function(ssid,psw)
	if ssid~=nil then 
		print('smartconfig OK! ssid:'..ssid..' psw:'..psw)
	else
		print('smartconfig Timeout!')
	end
	print("Smartconfig finish")
 end)
 
 --wifi.stopsmartconfig()
