#
# Testing Stopwatch.
#
# Prints the time elapsed on the MCU
#
# Created on 2010-8-30 by fgb
#

import serial, sys, struct

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)

# Receive elapsed time from stopwatch test
print "\nElapsed time: "
ser.write(chr(1))
print str(struct.unpack('L', ser.readline()[:-1])[0]) + '\n'
