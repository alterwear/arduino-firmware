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