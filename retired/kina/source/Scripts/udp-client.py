#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------

'''udp-client.py'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import socket

UDP_ADDR = "localhost"
UDP_PORT = 6666
MESSAGE = "x" * 256

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
	sock.connect((UDP_ADDR, UDP_PORT))
	
	while True:
		sock.send(MESSAGE.encode())
	
finally:
	sock.close()
