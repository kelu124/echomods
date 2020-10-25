lit3prog -f < lit3_v2.0.bin

gpio mode 10 IN
gpio mode 11 IN
gpio mode 12 IN
gpio mode 13 IN
gpio mode 14 IN
gpio mode 6 OUT 
gpio write 6 0 
gpio mode 6 OUT
gpio write 6 1

gpio mode 10  OUT 
gpio mode 11 OUT 
gpio mode 2 IN
gpio mode 3 IN
gpio mode 24 IN

gpio write 10 1
gpio write 11 1
gpio mode 12 alt0 
gpio mode 13 alt0 
gpio mode 14 alt0 
gpio mode 15 IN 
gpio mode 16 IN


i2cdetect -y 1
