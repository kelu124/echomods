--pwm demo
print("------pwm demo------")
----pwm pin: D1, D3, D8, D9, D10, D11, D12, D13, D14, D15, D16

print("Breathing LED")
--connect a led to D1 for demo
pin = 1
freq =10000
duty =0
dir = 1
tmr.start(1,50,function()
	if dir ==1 then
		duty = duty + 5
		if duty>100 then 
			duty =100
			dir = 0
		end
	else 
		duty = duty - 5
		if duty< 0 then 
			duty = 0
			dir = 1
		end
	end
	pwm.start(pin,freq,duty)
end)