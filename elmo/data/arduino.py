#!/usr/bin/python
import time
import os

Angles = 5*60 


#Loop
for i in range(int(Angles)):
	time.sleep( 0.1 )
	os.system('./read > ./Offset-'+str(i)+".DAT")
	print(str(i))



