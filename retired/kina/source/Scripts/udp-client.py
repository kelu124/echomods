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