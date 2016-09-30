--wifi demo
print("------wifi demo------")

--simply ap mode
cfg={ssid = 'WiFiMCU_Wireless',pwd = ''}
wifi.startap(cfg)
cfg=nil

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
