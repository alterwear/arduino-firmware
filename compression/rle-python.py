from PIL import Image
# useful: http://pillow.readthedocs.io/en/3.3.x/handbook/tutorial.html

imgfile = Image.open("trip_start_1_44.xbm")

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

for i in range(0, len(imgdata)):
    print(imgdata[i])

# To convert it to an ordinary sequence (e.g. for printing), use 
#print(list(imgfile.getdata()))