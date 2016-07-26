'''report.py -- BitLib 2.0 Capture Device Report Generator (Python)'''

from bitlib import *
import datetime
import time

usleep = lambda x: time.sleep(x/1000000.0)


MY_DEVICE = 0 # one open device only
MY_CHANNEL_TRIG = 0 # channel to trig on (chan A)
MY_CHANNEL = 1 # channel to capture and display (0 for Chan A, 1 for Chan B)
MY_PROBE_FILE = "" # default probe file if unspecified
MY_MODE = BL_MODE_DUAL # preferred trace mode
MY_RATE = 5000000 # default sample rate we'll use for capture.
MY_SIZE = 1000 # number of samples we'll capture (200us * 5MHz)
TRUE = 1

MODES = ("FAST","DUAL","MIXED","LOGIC","STREAM")
SOURCES = ("POD","BNC","X10","X20","X50","ALT","GND")




def main(argv=None):
    #
    # Open the first device found (only)
    #

    ts = time.time()
    stt = datetime.datetime.fromtimestamp(ts).strftime('%Y%m%d-%H%M%S')

    print "\nStarting: Attempting to open one device..."
    if BL_Open(MY_PROBE_FILE,1):
        #
        # Open succeeded (report versions).
        #
        print " Library: %s (%s)" % (
            BL_Version(BL_VERSION_LIBRARY),
            BL_Version(BL_VERSION_BINDING))
        #
        # Select this device (optional, it's already selected).
        #
        BL_Select(BL_SELECT_DEVICE,MY_DEVICE)
        #
        # Report the link, device and channel information.
        #
        print "    Link: %s" % BL_Name(0)
        print "BitScope: %s (%s)" % (BL_Version(BL_VERSION_DEVICE),BL_ID())
        print "Channels: %d (%d analog + %d logic)" % (
            BL_Count(BL_COUNT_ANALOG)+BL_Count(BL_COUNT_LOGIC),
            BL_Count(BL_COUNT_ANALOG),BL_Count(BL_COUNT_LOGIC))
        #
        # Determine which modes the device supports.
        #
        print "   Modes:" + "".join(["%s" % (
            (" " + MODES[i]) if i == BL_Mode(i) else "") for i in range(len(MODES))])
        #
        # Report canonic capture specification in LOGIC (if supported) or FAST mode (otherwise.
        # BL_Mode(BL_MODE_LOGIC) == BL_MODE_LOGIC or 
       
        BL_Mode(MY_MODE) # prefered trace mode





	# setup channel 0 (analog)
	BL_Select(BL_SELECT_CHANNEL, 0)
	BL_Intro(BL_ZERO)
	BL_Delay(BL_ZERO)
	BL_Rate(MY_RATE)
	BL_Size(MY_SIZE) # optional default BL_MAX_SIZE
        BL_Trigger(2,BL_TRIG_RISE) # optional when untriggered */
	BL_Select(BL_SELECT_SOURCE, BL_SOURCE_POD)
	BL_Range(BL_Count(BL_COUNT_RANGE))
	BL_Offset(BL_ZERO)
	BL_Enable(1)

	# setup channel 1 (analog)
	BL_Select(BL_SELECT_CHANNEL, 1)
	BL_Intro(BL_ZERO)
	BL_Delay(BL_ZERO)
	BL_Rate(MY_RATE)
	BL_Size(MY_SIZE) # optional default BL_MAX_SIZE
	BL_Select(BL_SELECT_SOURCE, BL_SOURCE_POD)
	BL_Range(BL_Count(BL_COUNT_RANGE))
	BL_Offset(BL_ZERO)
	BL_Enable(1)

        print " Capture: %d @ %.0fHz = %fs (%s)" % (
            BL_Size(),BL_Rate(),
            BL_Time(),MODES[BL_Mode()])

	Signal = []
	TimeStamp = []
	for i in range(1000):
		BL_Trace(BL_TRACE_FOREVER)
		BL_Select(BL_SELECT_CHANNEL, 1)
		Signal.append(BL_Acquire())

	print "Saving file"
	st = "/home/kelu/"+stt +"-Signal-bitscope-DATA.log"

	targetFile = open(st, 'w')
	
	for x in range(len(Signal)):
		for y in range(len(Signal[x])):
			targetFile.write(str(Signal[x][y])+"\t")
		targetFile.write("\n")
	targetFile.close()


        print "Finished: close the library to release resources."
        BL_Close()
    else:
        print "  FAILED: device not found (check your probe file)."

if __name__ == "__main__":
    import sys
sys.exit(main()) 
