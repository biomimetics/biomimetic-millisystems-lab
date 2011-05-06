#
# Testing Camera with Memory
#
#
# Created on 2010-8-30 by fgb
#

import serial, sys, struct
from PIL import Image

# Check and parse arguments
if len(sys.argv) < 2:
    print "Not enough arguments given. Need serial port."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=600, rtscts=1)


#*** Requesting data capture
ser.write(chr(1))

# Get image resolution
h = ord(ser.read())
v = ord(ser.read()) * ord(ser.read())

im = Image.new("L",(h,v))
imarray = im.load()

#print '\n' + str(struct.unpack('L', ser.readline()[:4])[0])

# Receiving the image
print "\nReceiving a " + str(h) + "x" + str(v) + " image...\n"
for j in range(0,v):
    for i in range(0,h):
        imarray[i,j] = ord(ser.read())
        #print i, j, imarray[i,j]
im.show()
