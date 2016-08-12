--gpio demo
print("------gpio demo------")
print("Test gpio output function")
print("Set gpio 17 as output")
print("gpio 17 connect to LED on WiFiMCU board")
gpio.mode(17,gpio.OUTPUT)
local i=0
repeat 
	print("Light on LED")
	gpio.write(17,gpio.LOW)
	tmr.delayms(500)
	print("Light off LED")
	gpio.write(17,gpio.HIGH)
	tmr.delayms(500)
	i = i+1
until i>10
