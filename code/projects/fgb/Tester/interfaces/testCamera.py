#
# Testing Camera
# After sending a delay to take a picture, it will receive and display this picture
#
# Created on 2010-3-1 by fgb
#

import serial, sys
from PIL import Image

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port. "
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)

#*** Image request
h = 160
v = 100
im = Image.new("L",(h,v))
imarray = im.load()

print "\nRequesting image..."
ser.write(chr(1)) # Send a 1 to request a picture

for j in range(0,v):
    for i in range(0,h):
        imarray[i,j] = ord(ser.read())

im.show()
