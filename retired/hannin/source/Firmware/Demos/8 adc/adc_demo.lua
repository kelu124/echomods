--adc demo
print("------adc demo------")

--adc pin: D1, D13, D15, D16, D17
pin = 1
tmr.start(0,1000,function()
	print("pin:"..pin.."adc value:"..adc.read(pin))
end)