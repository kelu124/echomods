--gpio demo
print("------gpio demo------")
print("Test gpio input function")
print("Set gpio 0 as input")
print("gpio 0 connect to button BOOT on WiFiMCU board")
gpio.mode(0, gpio.INPUT)
print("Press BOOT button to go on...")
repeat
   print("gpio 0 status:"..gpio.read(0))
   tmr.delayms(1000)
until gpio.read(0)==0

print("Test gpio interrupt function")
print("Set gpio 0 as input interrupt")
print("Press BOOT button to test")
local cnt=0
function gpioINT_cb()
	cnt = cnt + 1
end
gpio.mode(0, gpio.INT,'falling',gpioINT_cb)
repeat
   print("gpioINT_cb called times:"..cnt)
   tmr.delayms(1000)
until cnt>20