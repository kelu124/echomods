
id=0
sda= 11 --pin D11
scl= 10 --pin D10
addr=0x3C -- the I2C address of our device  7 bits

function read_reg(dev_addr, reg_addr)
     i2c.start(id)
     if i2c.address(id, dev_addr ,'w')==nil then 
		print("no response at addr: "..dev_addr)
		return nil
	 end
     i2c.write(id,reg_addr)
     --i2c.stop(id)
     i2c.start(id)
     if i2c.address(id, dev_addr ,'r')==nil then 
		print("no response at addr: "..dev_addr)
		return nil
	 end
     c=i2c.read(id,1)
     i2c.stop(id)
     return c
end

function write_reg(dev_addr, reg_addr, reg_val)
     i2c.start(id)
	 if i2c.address(id, dev_addr,'w')==nil then 
		print("no response at addr: "..dev_addr)
		return nil
	 end
     i2c.write(id, reg_addr)
     i2c.write(id, reg_val)
     i2c.stop(id)
end

function oled_command(cmd)
     write_reg(addr,0,cmd)
end

function oled_data(data)
     write_reg(addr,0x40,data)
end
	
function OLED_Set_Pos(x, y) 
	y = bit.bor(y,0xb0)
	oled_command(y)
	x=bit.band(x,0xF0)
	x=bit.rshift(x,4)
	x=bit.bor(x,0x10)
	oled_command(x)
	x=bit.band(x,0x0F)
	x=bit.rshift(x,4)
	x=bit.bor(x,0x01)
	oled_command(x)
--   OLED_WriteCmd(0xb0|y);//y
--    OLED_WriteCmd(((0xf0&x)>>4))|0x10);//设置x高4位
--    OLED_WriteCmd(((0x0f&x)>>4))|0x01);//设置x低4位
end   	  
   
function OLED_Display_On(void)
	oled_command(0x8D)--SET DCDC
	oled_command(0x14)--DCDC ON
	oled_command(0xAF)--DISPLAY ON
end
  
function OLED_Display_Off(void)
 	oled_command(0x8D)--SET DCDC
	oled_command(0x10)--DCDC OFF
	oled_command(0xAE)--DISPLAY OFF
end

function OLED_Clear()
	for i=0,8 do
		oled_command(0xb0+i)--page address
		oled_command(0x00)--col low addree
		oled_command(0x10)--col high addree
		for j=0,128 do
			oled_data(0x00)
		end
	end
end

function OLED_init() -- Initialises the 128x64 oled
print("starting oled")
oled_command(0xAE)--turn off oled panel
oled_command(0x00)---set low column address
oled_command(0x10)--set high column address
oled_command(0x40)--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
oled_command(0x81)--set contrast control register
oled_command(0xCF)--set SEG Output Current Brightness
oled_command(0xA1)--Set SEG/Column Mapping 
oled_command(0xC8)--Set COM/Row Scan Direction 
oled_command(0xA6)--set normal display
oled_command(0xA8)--set multiplex ratio(1 to 64)
oled_command(0x3F)--1/64 duty
oled_command(0xD3)--set display offset	Shift Mapping RAM Counter (0x00~0x3F)
oled_command(0x00)--not offset
oled_command(0xD5)--set display clock divide ratio/oscillator frequency
oled_command(0x80)--set divide ratio, Set Clock as 100 Frames/Sec
oled_command(0xD9)--set pre-charge period
oled_command(0xF1)--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
oled_command(0xDA)--set com pins hardware configuration
oled_command(0x12)
oled_command(0xDB)--set vcomh
oled_command(0x40)--Set VCOM Deselect Level
oled_command(0x20)--Set Page Addressing Mode (0x00/0x01/0x02)
oled_command(0x02)
oled_command(0x8D)--set Charge Pump enable/disable
oled_command(0x14)--set(0x10) disable
oled_command(0xA4)--Disable Entire Display On (0xa4/0xa5)
oled_command(0xA6)--Disable Inverse Display On (0xa6/a7) 
oled_command(0xAF)--turn on oled panel

OLED_Display_On()
print("Init done")
end

function draw(x,y)
	OLED_Clear()
	OLED_Set_Pos(x,y)
	for i=1,128 do
	oled_data(0x55)
	end
end
-- initialize i2c
i2c.setup(id,sda,scl)
OLED_init()

i=1
repeat
	draw(0,i-1)
	if i==8 then i=1 end
	i = i +1 	
	tmr.delayms(500)
until i>8
