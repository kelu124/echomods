--wifi demo
print("------wifi demo------")

--advanced ap mode
cfg={ssid = 'WiFiMCU_Wireless_adv',
	pwd = '12345678',
	ip='192.168.1.1',
	netmask='255.255.255.0',
	gateway='192.168.1.1',
	dnsSrv='192.168.1.1'}
function wifi_cb(info)
	print(info)
end
wifi.startap(cfg,wifi_cb)

function tmr_cb()
--get ip address of ap mode
print("wifi.ap.getip()")
print(wifi.ap.getip())
--get adv ip information of ap mode
print("wifi.ap.getipadv()")
print(wifi.ap.getipadv())
end
tmr.start(1,3000,tmr_cb)

print("Input command string: wifi.ap.stop() to stop ap")
--wifi.ap.stop()

--Enable IEEE power save mode
--wifi.powersave()