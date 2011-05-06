#
# Testing IMU.
#
# Created on 2010-9-3 by fgb
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
print "\nValues from accelerometers or gyroscopes: "
while 1:
    for i in range(0,3):
        val1 = str(ser.read()) + str(ser.read())
        val2 = str(ser.read()) + str(ser.read())
        val3 = str(ser.read()) + str(ser.read())
        print(struct.unpack('h', val1)[0], struct.unpack('h', val2)[0], struct.unpack('h', val3)[0])
