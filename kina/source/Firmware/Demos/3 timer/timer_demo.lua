--timer demo
print("------timer demo------")
function tmr_cb()
	print('tmr:0,tick:'..tmr.tick()) 
end
tmr.start(0,1000,tmr_cb)

print("Input command: tmr.stop(0) to stop timer")
--stop timer
--tmr.stop(0)

--stop all timer
--tmr.stopall()

--delay in ms
--tmr.delayms(1000)

--restore watchdog counter
--tmr.wdclr()