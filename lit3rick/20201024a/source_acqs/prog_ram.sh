lit3prog -p < lit3_v2.0.bin

gpio mode 10  OUT 
gpio mode 11 OUT 
gpio mode 2 IN
gpio mode 3 IN
gpio mode 24 IN
gpio mode 6 OUT
gpio write 10 1
gpio write 11 1
gpio mode 12 alt0 
gpio mode 13 alt0 
gpio mode 14 alt0 
gpio mode 15 IN 
gpio mode 16 IN
gpio write 6 1

i2cdetect -y 1
