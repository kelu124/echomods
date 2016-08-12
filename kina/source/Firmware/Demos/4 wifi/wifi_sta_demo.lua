--wifi demo
print("------wifi demo------")

--simply sta mode
ap_ssid="Doit" --change to your ap ssid
ap_pwd="123456789" --change to your ap pwd
cfg={ssid = ap_ssid,pwd = ap_pwd}
wifi.startsta(cfg)
cfg=nil
ap_ssid=nil
ap_pwd=nil

function tmr_cb()
--get link information of sta mode
print("wifi.sta.getlink()")
print(wifi.sta.getlink())
--get ip address of sta mode
print("wifi.sta.getip()")
print(wifi.sta.getip())
--get adv ip information of sta mode
print("wifi.sta.getipadv()")
print(wifi.sta.getipadv())
end
tmr.start(1,3000,tmr_cb)

print("Input command string: wifi.sta.stop() to stop ap")
--wifi.sta.stop()

--Enable IEEE power save mode
--wifi.powersave()
