#
# Testing UART:
# Sending 256 ASCII characters and checking the returned character for a match.
#
# Created on 2010-3-1 by fgb
#

import serial, sys

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)

# Send ascii byte and check the returned byte for a match
print "\nSending entire ascii set: "
for tx in range(256):

    ser.write(chr(tx))
    rx = ord(ser.read())

    if (tx == rx):
        print str(tx) + " - ok..."
    else:
        print str(tx) + " - err: received " + str(rx) + " instead..."
