#
# Testing DFMEM.
#
# This script prompts for a response and prints out what it receives until it
# finds a newline.
#
# Created on 2010-3-1 by fgb
#

import serial, sys

# Check and parse arguments
if len(sys.argv) < 3:
    print "Not enough arguments given. Need serial port and page."
    sys.exit()

port = sys.argv[1] # serial port for the current bluetooth module.
page = int(sys.argv[2]) # page to query.

# Open serial port
ser = serial.Serial('/dev/tty.' + port, 230400, timeout=15, rtscts=1)

# Request the contents of a page of memory
pagesize = 528

print "\nPrompting for an answer:"
ser.write(chr(page))

#print ser.readline()
contents = []
for i in range(pagesize):
    contents.append(ser.read())
print ''.join(contents) + '\n'
#print str(contents) + '\n'
