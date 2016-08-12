--sensor demo
print("------dht11 demo------")

pin = 2
sensor.dht11.init(pin)
tmr.start(0,3000,function()
	t,h = sensor.dht11.get()
	if t ~= nil then
		print("Temp: "..t.." Humidity: "..h)
	else
		tmr.stop(0)
		print("Read failed")
	end
end)