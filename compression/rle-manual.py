#import sys
from struct import *

# example https://stackoverflow.com/questions/1400012/endianness-of-integers-in-python

#pack('hhl', 1, 2, 3)
#unpack('hhl', '\x00\x01\x00\x02\x00\x00\x00\x03')

#print(sys.byteorder) #returns "little"
img  = open("test.xbm", "r") # r = read-only
print(img.read())