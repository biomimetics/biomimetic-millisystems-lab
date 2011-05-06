#
# Testing ADC via DMA:
# After sending a 1, the script starts receiving the addresses in the DMA
# RAM space currently being accessed by the DMA when triggered by the ADC.
#
# Created on 2010-3-22 by fgb
#

import serial, sys

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)

# Send a 1 to start receiving bEMF values from the motor
print "\nStart stepping the motor: "

while 1:
    # [Re]Start stepping/transmission
    ser.write(chr(1))

    # Get a word (2-bytes) and print it
    highByte = ord(ser.read()) << 8
    lowByte = ord(ser.read())
    print str(highByte + lowByte) + " " + str(highByte) + " " + str(lowByte)
