#
# Testing Camera
#
# After sending a delay to take a picture, it will receive and display this
# picture.
#
# Created on 2010-3-1 by fgb
#

import serial, sys
from PIL import Image

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)


#*** Requesting contents of a camera register
reg = 0x35
ser.write(chr(reg))
print "\nThe content of register " + str(hex(reg)) + " is " + str(hex(ord(ser.read()))) + "."


#*** Image request
h = 160
v = 100
im = Image.new("L",(h,v))
imarray = im.load()

# Requesting and image of the above resolution
ser.write(chr(1))
ser.write(chr(h))
ser.write(chr(v))

# Confirming resolution
h_rx = ord(ser.read())
v_rx = ord(ser.read())
if h != h_rx or v != v_rx:
    print "\nResolutions don't match. Received " + str(h_rx) + "x" + str(v_rx) + ".\n"
    sys.exit()

# Receiving the image
print "\nReceiving a " + str(h) + "x" + str(v) + " image...\n"
for j in range(0,v):
    for i in range(0,h):
        imarray[i,j] = ord(ser.read())
        #print i, j, imarray[i,j]
im.show()
