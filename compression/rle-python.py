from PIL import Image
# useful: http://pillow.readthedocs.io/en/3.3.x/handbook/tutorial.html

imgfile = Image.open("test.xbm")

print imgfile
# size attribute is a 2-tuple containing width and height (in pixels)
# "mode" defines the number and names of the bands in the image, and also the pixel type and depth
print(imgfile.format, imgfile.size, imgfile.mode) 
# mode = 1, (1-bit pixels, black and white, stored with one pixel per byte)
# more info: https://pillow.readthedocs.io/en/5.1.x/handbook/concepts.html#concept-modes

#imgfile.show(); # opens preview w/ the image. Appears to be inverted colors.

# Returns the contents of this image as a sequence object containing pixel values. 
# The sequence object is flattened, so that values for line one follow directly 
# after the values of line zero, and so on.
imgdata = imgfile.getdata()
imgdataList = list(imgdata)

# https://github.com/python-pillow/Pillow/blob/5e1a528eb25fdaa5d2761ce7f13c1bb4d97cc1eb/selftest.py
print("len of imgdata: " + str(len(imgdata)))

# Notes on imgdata structure:
# Each element at an index represents a pixel.
# For some reason, when I print them out using python, an individual element
# prints out as 8 bits: either 255 (int) or 0b11111111 (binary).
# But, if my test file has: 0x81  (0b10000001) as the very first entry, what gets correctly printed out is:
# i: 0, imgdata[i]: 0b11111111
# i: 1, imgdata[i]: 0b0
# i: 2, imgdata[i]: 0b0
# i: 3, imgdata[i]: 0b0
# i: 4, imgdata[i]: 0b0
# i: 5, imgdata[i]: 0b0
# i: 6, imgdata[i]: 0b0
# i: 7, imgdata[i]: 0b11111111

# 0x81, 0xFF, 0x03
# = 0b10000001, 0b11111111, 0b00000011
# RLE = {[0:1], [1:6], [7:9], [16:6], [22:2]}
# NOTE: The above is what it SHOULD be, this is what I'm getting:
""" imgdata[0]: 255
imgdata[1]: 0
imgdata[2]: 0
imgdata[3]: 0
imgdata[4]: 0
imgdata[5]: 0
imgdata[6]: 0
imgdata[7]: 255
imgdata[8]: 255
imgdata[9]: 255
imgdata[10]: 255
imgdata[11]: 255
imgdata[12]: 255
imgdata[13]: 255
imgdata[14]: 255
imgdata[15]: 255
imgdata[16]: 255
imgdata[17]: 255 --> should flip to 0s at index 16
imgdata[18]: 0
imgdata[19]: 0
imgdata[20]: 0
imgdata[21]: 0 --> both index 21 and 22 should be 1s. wtf is happening.
imgdata[22]: 0 """

for i in range(0, 23):
    print("imgdata["+str(i)+"]: " + str(imgdata[i]))

# Same in a list:
for index, item in enumerate(imgdataList):
    print("imgdataList["+str(index)+"]: " + str(item))

"""
imgdataList[0]: 255
imgdataList[1]: 0
imgdataList[2]: 0
imgdataList[3]: 0
imgdataList[4]: 0
imgdataList[5]: 0
imgdataList[6]: 0
imgdataList[7]: 255
imgdataList[8]: 255
imgdataList[9]: 255
imgdataList[10]: 255
imgdataList[11]: 255
imgdataList[12]: 255
imgdataList[13]: 255
imgdataList[14]: 255
imgdataList[15]: 255
imgdataList[16]: 255
imgdataList[17]: 255 --> why is this extended like this?
imgdataList[18]: 0
imgdataList[19]: 0
imgdataList[20]: 0
imgdataList[21]: 0 --> where are my other ones?
imgdataList[22]: 0
"""

# 0b11010001 or 0xD1 gets printed as  10001011
# imgdata[8]: 255
# imgdata[9]: 0
# imgdata[10]: 0
# imgdata[11]: 0
# imgdata[12]: 255
# imgdata[13]: 0
# imgdata[14]: 255
# imgdata[15]: 255

#Endianness is backwards from what I expect.
# From stackoverflow: https://stackoverflow.com/questions/1400012/endianness-of-integers-in-python
#   Python's int has the same endianness as the processor it runs on.

# Big Endian Byte Order: The most significant byte (the "big end") of the data is placed at 
# the byte with the lowest address. The rest of the data is placed in order in the next three bytes in memory.

#Little Endian Byte Order: The least significant byte (the "little end") of the data is placed 
# at the byte with the lowest address. The rest of the data is placed in order in the next three bytes in memory.

rle = {}
currentPixel = imgdata[0] #start w whatever the first pixel is.
runLength = 0
index = 0
for i in range(0, len(imgdata)):
    print("i: " + str(i) + ", imgdata[i]: " + str(bin(imgdata[i])) + 
        ", currentPixel: " + str(currentPixel))
    if (imgdata[i] == currentPixel):
        runLength += 1
    else:
      rle[index] = runLength
      print("rle["+str(index)+"]: " + str(rle[index]) + ", i: " + str(i) + ", curr: " 
            + str(currentPixel) + " imgdata["+str(i)+"]: " + str(imgdata[i]) )
      runLength = 1
      index = i
      currentPixel = imgdata[i]
    if (i > 23):
        break
print(rle)

# To convert it to an ordinary sequence (e.g. for printing), use 
#print(list(imgfile.getdata()))