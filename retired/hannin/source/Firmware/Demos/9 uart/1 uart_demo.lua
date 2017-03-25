--uart demo
print("------uart demo------")

--uart pin:D8(RX1), D9(TX1)
--setup uart
uart.setup(1,9600,'n','8','1')

function uartReceive(d)
	print("len(bytes)"..string.len(d).." data:"..d)
	uart.send(1,d)
end
uart.on(1, 'data',uartReceive)

--send function demo
--uart.send(1,'hello wifimcu')
--uart.send(1,'hello wifimcu','hi',string.char(0x32,0x35))
--uart.send(1,string.char(0x01,0x02,0x03))