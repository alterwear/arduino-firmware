from PIL import Image
# useful: http://pillow.readthedocs.io/en/3.3.x/handbook/tutorial.html

imgfile = Image.open("trip_start_1_44.xbm")

print imgfile

#imgfile.show(); # opens preview w/ the image. Appears to be inverted colors.