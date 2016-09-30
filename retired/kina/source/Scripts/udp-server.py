import socket
import time
import codecs

UDP_ADDR = ""
UDP_PORT = 6666
BUFFER_SIZE = 4096

logFile = open('log.txt', 'w')
 
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_ADDR, UDP_PORT))

# Start speed measurement after receiving the first packet
print("Waiting for connection...")
data = sock.recv(BUFFER_SIZE)
print("A client is connected!")
startTime = time.time()
bytesReceived = 0
lastRefresh = 0 

while True:
	data = sock.recv(BUFFER_SIZE)
	bytesReceived += len(data)
	mBitsReceived = bytesReceived * 8 / 1024 / 1024;
	elapsedTime = time.time() - startTime
	logFile.write(data.hex() + '\n')
	
	# Refresh the result no more than once a second
	if (elapsedTime > lastRefresh + 1):
		lastRefresh = int(elapsedTime)
		print("Transfered data: {0:.6f} MBit".format(mBitsReceived), end=", ")
		print("Elapsed time: {0:.2f} s".format(elapsedTime), end=", ")
		print("Average speed: {0:.6f} MBit/s".format(mBitsReceived / elapsedTime), end="\r")
		logFile.flush()