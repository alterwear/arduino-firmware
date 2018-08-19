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

rle = {}
currentPixel = 0
runLength = 0
index = 0
for i in range(0, len(imgdata)):
    print("i: " + str(i) + ", imgdata[i]: " + str(bin(imgdata[i])) + 
        ", currentPixel: " + str(currentPixel))
    if (imgdata[i] == currentPixel):
        runLength += 1
    else:
      rle[index] = runLength
      index += 1
      runLength = 0
      currentPixel = imgdata[i]
print(rle)

# To convert it to an ordinary sequence (e.g. for printing), use 
#print(list(imgfile.getdata()))