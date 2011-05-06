#
# Testing ADC:
# After sending a 1, the motor will start stepping through 4 different voltages in cycles,
# while the board sends back the bEMF at each of these steps.
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

# Send a 1 to start receiving bEMF values from the motor
print "\nStart stepping the motor: "

while 1:
    # [Re]Start stepping/transmission
    ser.write(chr(1))

    # Get bEMF measurements
    flag = True
    
    while flag:
        # Read first byte
        while not ser.inWaiting():
            pass
        byte1 = ord(ser.read())
    
        if (byte1 & int('01100000',2)) != int('01100000',2):
    
            if (byte1 & int('10000000', 2) == int('10000000', 2)):
                highByte = (byte1 & int('00011111', 2)) << 5
            else:
                print "\nI have received a low byte out of order."
            
            # Read second byte
            while not ser.inWaiting():
                pass
            byte2 = ord(ser.read())
    
            if (byte2 & int('10000000', 2)) == int('00000000', 2):
                lowByte = (byte2 & int('00011111', 2))
                print str(highByte + lowByte) + " " + str(highByte) + " " + str(lowByte)
            else:
                print "Received out-of-order high byte as expected."
                recoveryByte = ord(ser.read())
                if (recoveryByte & int('10000000', 2)) == int('0000000', 2):
                    print "Recovering..."
                else:
                    print "This process will probably not recover."
                    break
        else:
            flag = False
            break
