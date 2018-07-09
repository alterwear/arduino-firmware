# AlterWear
## Basic E-Ink Setup

### Hardware
**Correct datasheet, we think**
- The working one is , which [has been discontinued.](http://www.pervasivedisplays.com/kits/ext_kit). The datasheet is "EPD Extension board_Schematic_Gerber_v05". The files are available at that link, but also uploaded to this repo.
- Pervasive Displays (e-ink manufacturer) [support](http://www.pervasivedisplays.com/contact). Definitely contact them if you have issues! They should help you with specific questions.

**Another datasheet, not sure what it is for**
- This is a screenshot of ANOTHER circuit diagram [Fig. 5-1](https://www.dropbox.com/s/spbxfzleej3tsp5/Screenshot%202018-02-21%2015.26.41.png?dl=0) from the datasheet.
- PDF [datasheet for the e-ink display.](http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=232432) 
Screenshot.

### Software
#### Default (Arduino UNO and GRATIS library)
1. Download the Arduino library from Adafruit's [tutorial on how to use the e-ink display board](https://learn.adafruit.com/repaper-eink-development-board/overview) we have.
2. Once you've installed the library, the library code we want is EPD_V230_G2 --> demo_200 (should work out of the box).



#### Arduino Pro Mini
1. The Arduino Pro Mini is programmed over FTDI (3.3V I think).

#### Experimental
1. Paul Schow's github: https://github.com/paulschow/epapercard
(specifically firmware -> paul_demo_200, which is an updated, simplified version of the same library w/ "excess" parts removed.)
2. "Our" version of Paul's code: https://github.com/molecule/epapercard
3. Paul Schow's blog: https://www.paulschow.com//2016/08/epaper-business-card.html?m=1
 
## Basic NFC Setup on Uno

Notes: I2C communicates over 2 lines (SDA and SCLK). These both need pull-up resistors because they are "open drain".[2] According to [1], the tag click has pull-up resistors on SDA and SCLK already. Table 15[3] says the I2C address is 04h. [A good tutorial on I2C from Sparkfun](https://learn.sparkfun.com/tutorials/i2c). Uno: A4 (SDA), A5 (SCL).

0. Note that the NFC cannot be connected to Tx, Rx while uploading.
1. Connect GND, 3.3V to the Arduino power pins. Connect SDA to A4 and SCL to A5.
3. Use eink_i2c (which use Wire library) to read from NFC and update code.


2. Possibly relevant:
   - https://community.nxp.com/message/977712?commentID=977712#comment-977712
   - Confirmed we're using the NT3H1101 (in the paper). [Datasheet](https://www.nxp.com/docs/en/data-sheet/NT3H1101_1201.pdf). Ch. 9.6 has addressing info. I believe it's 85, 0b1010101, or 0x55. 
   - Trying to use this library: https://www.arduino.cc/en/Reference/Wire
   - I contacted Angela Lee via NXP: https://community.nxp.com/thread/469669
   - Info re: I2C: https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/
   - Added a follow-up to this comment: https://community.nxp.com/message/1026052

## NFC on Arduino Pro Mini
Note: Somehow this pro mini 3.3v w/ FTDI cable really messes up my USB ports on my Mac (need to restart my computer to reset them).

0. Connect PWR and GND like normal, solder the two little extra pins (A4, A5) in the middle of the board next to A3. This is what connects to the SDL and SCLK of the NFC board).
1. Use eink_i2c.

[1][Potentially slightly useful NFC tag docs.](https://download.mikroe.com/documents/add-on-boards/click/nfc-tag/nfc-tag-click-manual-v100.pdf)

[2][How To Mechatronics - I2C](https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/)

[3][NT3H2111_2211 Datasheet](https://download.mikroe.com/documents/datasheets/NT3H2111_2211.pdf)
(Relevant portion [here](https://www.dropbox.com/s/d4i99ricvakj35r/Screenshot%202018-06-27%2012.02.47.png?dl=0) )

## Making custom images
[These instructions from alexhadik.com](http://www.alexhadik.com/blog/2014/10/30/display-custom-e-ink-images-with-repaper-and-arduino-uno) were very helpful. 

Dimensions:

- 1.44": 96x128 pixels
- 2": 96x200 pixels
- 1.44": 176x264 pixels

Steps summarized here:

1. For a 2.0" board, open an Illustrator file.
2. Create an artboard that is 95x199 pixels in dimensions (note: one pixel smaller than you want the final one to be).
3. The image should be longer than it is wide.
4. Export that artboard as a jpg. Make sure it is now 96x200 pixels.
5. Using [this web app](https://www.online-utility.org/image/convert/to/XBM), convert to xbm.
6. Validate the file was built correctly:

You'll want to open your image files in a text editor like Sublime or Atom and check that the first lines have the following format:

```
#define myimage_2_0_width 200
#define myimage_2_0_height 96
static unsigned char myimage_2_0_bits[] = {
    ...
}
```

That is, the #define and char array declaration are named the same as your file and have the proper width, height, and screen size set. Open some of the images that exist in the Images directory for reference if you like.
7. Add your new xbm file to Arduino/libraries/Images
8. That should work.

# Breakout board notes

How to find the COG #:
- official page: http://www.pervasivedisplays.com/products/label_info
- semi-helpful Adafruit forum thread: https://forums.adafruit.com/viewtopic.php?f=19&t=56535&start=15


EPD breakout board (green):
- Compatible with: 40+pin e-ink display (connector is zig-zag).
- Goals: Recreate it on the breadboard, then simplify if possible, then create an SMD version.

Teensy e-paper adapter board (red): https://hackaday.io/project/13327-teensy-e-paper-adapter-board
- Original crowdsource campaign: https://www.crowdsupply.com/soniktech/e-paper-shield-kit
- Library code and example: https://github.com/jarek319/EPD215
- Compatible with: 20+-pin e-ink displays (connector is straight).
- Goals: Get it working (library code freezes and we don't know why), recreate and build our own.


## Other notes
- Technical support email: 	techsupport@pervasivedisplays.com
- [Old badger link.](https://web.archive.org/web/20170802044828/http://wyolum.com/projects/badger/)
- [BADGEr code](https://github.com/wyolum/EPD)
- [BADGEr v4 from Seeed Studio ($50)](https://www.seeedstudio.com/BADGEr_v4-p-1587.html)
- [Instructions from MSR for making custom e-ink thing.](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7508851)
- [Semi-helpful review from Paul Schow](https://www.paulschow.com/2017/02/pervasive-displays-epd-extension-kit.html).
- [Much more helpful review](https://embeddedcomputing.weebly.com/pervasive-displays-e-paper-epd-extension-kit-gen-2.html)

To debug from the .cpp library code, just add Serial.print() statements - they show up like normal in the serial monitor.

## Current Status

#### July 9 2018
**TODO**
- 

**Notes**
- Reading from the NFC works via Android. Basically, you capture the intent and automatically do a read whenever you write. Specifically, this line:

```
record.setText(new String(message.getRecords()[0].getPayload(), "UTF-8"));
```

Displays whatever was last written to the NFC tag. (That line is called just before I write, so the basic interaction with an NFC tag automatically reads it. (THere are probably ways to encrypt or hide stuff, but this is fine for now).
- This app will also successfully read: https://github.com/codexpedia/android_nfc_read_write
- **Q:** Where is it reading FROM?
   - [This code from the codexpedia example](https://github.com/codexpedia/android_nfc_read_write/blob/master/app/src/main/java/com/example/peng/nfcreadwrite/MainActivity.java#L89) seems to imply it's automatically bundled in an "NdefRecord" that gets sent when an NFC tag is activated.
   - [This article by Shane Tully](https://shanetully.com/2012/12/writing-custom-data-to-nfc-tags-with-android-example/) further confirms that you capture an intent when the tag is activated, and can immediately read and write.
- **Q2:** What is the actual memory layout of the NFC, and how does that interact with I2C and NFC?



#### July 5 2018
**TODO**
- ~~read: https://shanetully.com/2012/12/writing-custom-data-to-nfc-tags-with-android-example/~~
- App changes
  - ~~Upload to my phone~~
  - ~~Add ability to send more data (up to 10MB?)~~ - At least can send a full sentence now. Need to try w bitmaps eventually.
  - Try to send a simple pic.

#### July 3 2018
- Take out lines from lib code:
```
this->frame_fixed_repeat(0xaa, EPD_compensate); // changes nothing obvious, at least w/ 4 image switches.
this->frame_fixed_repeat(0xaa, EPD_white); // changes nothing obvious, w/ 4 image switches.
this->frame_data_repeat(image, EPD_inverse); // Didn't "do inverse of image", image seems darker (need to compare w/ orig video)
this->frame_data_repeat(image, EPD_normal);
```
Next: need to try actually timing.

- Learning about NDEF Messages ([source](https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/nfc/NdefMessage.java)), and NDEF Records ([source](https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/nfc/NdefRecord.java)
```
An NDEF Record contains typed data, such as MIME-type media, a URI, or a custom application payload. An NDEF Message is a container for one or more NDEF Records.
 ```
 ```
 An NDEF Message contains one or more NDEF Records.
 ```
 ```
 public static NdefRecord createMime(String mimeType, byte[] mimeData) {
 Create a new NDEF Record containing MIME data. Use this method to encode MIME-typed data into an NDEF Record, such as "text/plain", or "image/jpeg".
 ```
 Relevant? 
 ``` 
 private static final int MAX_PAYLOAD_SIZE = 10 * (1 << 20);  // 10 MB payload limit
 ```

#### July 2 2018
- Pro mini janks up my USB ports: too annoying to work with since I have to continually restart.
- Uno works well, reads NFC fine.
- How big are my current images? Does the code currently store all of them on the Uno? Where exactly? What's the capacity? What's the transfer time?
- Would there be a way to do a "diff" of two images, and only redraw the "different" pixels? Could use less memory.
- ~~Can I run the Uno off the NFC power? (almost def note but should try it).~~ --> NO.
