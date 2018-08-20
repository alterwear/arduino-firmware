#import sys
from struct import *

# example https://stackoverflow.com/questions/1400012/endianness-of-integers-in-python

#pack('hhl', 1, 2, 3)
#unpack('hhl', '\x00\x01\x00\x02\x00\x00\x00\x03')

#print(sys.byteorder) #returns "little"
img  = open("test.xbm", "r") # r = read-only
print(img.read())

# might be useful: https://auth0.com/blog/image-processing-in-python-with-pillow/

# WAIT:
#   each byte in the array contains the information for eight pixels, 
#   with the upper left pixel in the bitmap represented by the low bit of the first byte in the array.
#   low bit means if I have 0b10010011, then that "far right" 1 is the upper left pixel?