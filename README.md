# AlterWear
## Basic E-Ink Setup

### Hardware
**Correct datasheet, we think**
- The working one is [here, which has been discontinued.](http://www.pervasivedisplays.com/kits/ext_kit). The datasheet is "EPD Extension board_Schematic_Gerber_v05". The files are available at that link, but also uploaded to this repo.
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

#### 23 July 2018
**TODO**
- 
- 

**Notes**
- For EPD 2_0: ``` this->bytes_per_scan = 96 / 4; ```
- Overall flow is this:
Image_0 in EPD_V231_G2.h passes the byte pointer to the image (presumably):
```
// assuming a clear (white) screen output an image (PROGMEM data)
	void image_0(PROGMEM const uint8_t *image) {
		this->frame_fixed_repeat(0xaa, EPD_compensate);
		this->frame_fixed_repeat(0xaa, EPD_white);
		this->frame_data_repeat(image, EPD_inverse);
		this->frame_data_repeat(image, EPD_normal);
	}
```
To frame_fixed_repeat in EPD_V231_G2.cpp, where it's called "Fixed_value":
```
void EPD_Class::frame_fixed_repeat(uint8_t fixed_value, EPD_stage stage) {
```
Which actually just calls this:
```
// One frame of data is the number of lines * rows. For example:
// The 1.44” frame of data is 96 lines * 128 dots.
// The 2” frame of data is 96 lines * 200 dots.
// The 2.7” frame of data is 176 lines * 264 dots.

// the image is arranged by line which matches the display size
// so smallest would have 96 * 32 bytes

void EPD_Class::frame_data(PROGMEM const uint8_t *image, EPD_stage stage){
	for (uint8_t line = 0; line < this->lines_per_display ; ++line) {
		this->line(line, &image[line * this->bytes_per_line], 0, true, stage);
	}
}
```

That bit of code loops the number of lines in the display. The code that reads in lines looks like this:
```
// output one line of scan and data bytes to the display
void EPD_Class::line(uint16_t line, const uint8_t *data, uint8_t fixed_value, bool read_progmem, EPD_stage stage) {
```
Note that line is the line #, data is a pointer to the image, indexed in based on the line number, fixed_value is zeroe, read_progmem is true, not sure what stage is.
```
..........
if (this->middle_scan) { // true for EPD_1_44 and 2_0, false for EPD_1_9 and 2_6.
    // data bytes
    //Serial.println("odd pixels in middle scan...");
    this->odd_pixels(data, fixed_value, read_progmem, stage);

    // scan line
    for (uint16_t b = this->bytes_per_scan; b > 0; --b) { // bytes_per_scan = 96/4 = 24
	uint8_t n = 0x00;
	if (line / 4 == b - 1) {                         // 
		n = 0x03 << (2 * (line & 0x03));
	}
	SPI_put(n);
    }
.....
```
Note that data is the pointer to the image, fixed_val is zero, and line is just the line # of the current line we're looking at. I THINK SPI_put just basically does a new line or flushes the buffer or something. So the part of the code that actually matters is odd_pixels:

```
// pixels on display are numbered from 1 so odd is actually bits 0,2,4,...
void EPD_Class::odd_pixels(const uint8_t *data, uint8_t fixed_value, bool read_progmem, EPD_stage stage) {
```
data is the pointer to the image, fixed_value is 0, read_progmem is true, stage is ?
```
...
for (uint16_t b = this->bytes_per_line; b > 0; --b) { // loops over all the bytes in a line.
...
// AVR has multiple memory spaces
uint8_t pixels;
if (read_progmem) {                                       // this is true, so the image is stored in progmem??
    pixels = pgm_read_byte_near(data + b- 1) & 0x55;
} else {
    pixels = data[b - 1] & 0x55;                          
}
...
```
Info about progmem: Flash (program) memory (can store data here instead of SRAM).
I COULD HAVE REALIZED THIS FROM THE FACT THAT the image byte always is labeled PROGMEM LOL.
From [Arduino docs](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/): 
- "While PROGMEM could be used on a single variable, it is really only worth the fuss if you have a larger block of data that needs to be stored, which is usually easiest in an array.
- "Using PROGMEM is also a two-step procedure. After getting the data into Flash memory, it requires special methods (functions), also defined in the pgmspace.h library, to read the data from program memory back into SRAM, so we can do something useful with it." This is the "pgm_read_byte_near" method above.

Later there's a switch statement and the part that uploads the image is:
```
case EPD_normal:       // B -> B, W -> W (New Image)
    pixels = 0xaa | pixels;
    break;
```

[More info](http://playground.arduino.cc/Learning/Memory) about different Arduino memory spaces:
- Flash memory (program space), is where the Arduino sketch is stored.
- SRAM (static random access memory) is where the sketch creates and manipulates variables when it runs.
- EEPROM is memory space that programmers can use to store long-term information.
- Flash memory and EEPROM memory are non-volatile (the information persists after the power is turned off). SRAM is volatile and will be lost when the power is cycled.
- Flash (PROGMEM) memory can only be populated at program burn time. You can’t change the values in the flash after the program has started running.

| Info | ATMega328p | MSP430 **G2553** IPW20R |
|:--- | :---|:---|
Flash | 32 kBytes (1 kByte used for bootloader) | 16KB |
| SRAM | 2048 bytes| ? |
| EEPROM | 1024 bytes | ? |
| RAM | ? | 512Bytes |
| Memory | ? | 2kB |

[More about MSP430 flash](http://www.ti.com/lit/ds/symlink/msp430g2553.pdf):
The flash memory can be programmed via the Spy-Bi-Wire/JTAG port or in-system by the CPU. The CPU can
perform single-byte and single-word writes to the flash memory. Features of the flash memory include:
• Flash memory has n (**what is n?**) segments of main memory and four segments of information memory (A to D) of
64 bytes each. Each segment in main memory is 512 bytes in size.
• Segments 0 to n may be erased in one step, or each segment may be individually erased.
• Segments A to D can be erased individually or as a group with segments 0 to n. Segments A to D are also
called information memory.
• Segment A contains calibration data. After reset segment A is protected against programming and erasing. It
can be unlocked but care should be taken not to erase this segment if the device-specific calibration data is
required.

Note the cat_2_0 image is 15,094 bytes (16 KB on disk). So it's burned into flash, then loaded line by line into SRAM and sent to the epaper display.

Could send it over in SRAM-sized chunks, let's assume best-case and can use the entire SRAM:
15,094 / 2028 = 7.44 chunks.

Writing that to the EPD sounds reallllly complicated tho...

**Image compression information**
- The four different approaches[3],[5] to compression are 
    - Statistical Compression, 
    - Spatial compression, 
    - Quantizing compression, 
    - Fractal compression. 
    - [src](https://arxiv.org/pdf/1112.2261.pdf)
- Run-length encoding (RLE) is a very simple form of data compression in which runs of data (that
is, sequences in which the same data value occurs in many consecutive data elements) are stored
as a single data value and count, rather than as the original run. This is most useful on data that
contains many such runs: for example, simple graphic images[8] such as icons, line drawings, and
animations.
- Huffman coding removes coding redundancy. Huffman’s procedure creates the
optimal code for a set of symbols and probabilities subject to the constraint that the symbols be
coded one at a time. After the code has been created, coding and/or decoding is accomplished in
the simple look-up table . When large number of symbols is to be coded, the construction of the
optimal binary Huffman code is a difficult task.

**Weird idea:**
Store a bunch of "image primitives" that you can reference when constructing a new image. As long as the instructions to reconstruct an image from the primitives are smaller than the image themselves would be, this would actually save you some space.

#### 16 July 2018
**TODO**
- ~~Look at the partial update code for etc from nxp.~~ Will need to figure out how to use TI LaunchPad stuff before I can try that.
- Check Adafruit forum post re: Arduino image handling questions: https://forums.adafruit.com/viewtopic.php?f=19&t=138304
- Look into compressing .xbm? 
  - https://stackoverflow.com/questions/8417034/how-to-make-bitmap-compress-without-change-the-bitmap-size
  - https://android--code.blogspot.com/2015/09/android-how-to-compress-bitmap.html
- Send MIME data format instead? (Look up android way to do this).
- Send an .xbm of size Tag maxsize=820 bytes?

**Notes:**
- Reading image over nfc: How about if I just send the image file exactly as is, and just change what the file points to in arduino code?
  - Tried that, got this error message:  ```E/BrcmNfcNfa: Unable to write NDEF. Tag maxsize=820, request write size=15118 ```
  - From the NXP NFC tag datasheet:
      -  EEPROM is a non volatile memory that stores 1904 bytes user data (888 byte user data in case of the NTAG I2C 1k version).
      - I'm guessing we have the 1k version?
      - Sec. 8.3.9 says: "Pages 04h to E1h via the RF interface - Block 01h to 37h, plus the first 8 bytes of block 38h via the I2C interface are the user memory read/write areas for NTAG I2C 1k version."
 - Trying MIME type data format?
   - https://tools.ietf.org/html/rfc2045
   - Multipurpose Internet Mail Extensions, or MIME, redefines the format of messages to allow for **(1)** textual message bodies in character sets other than US-ASCII, **(2) an extensible set of different formats for non-textual message bodies**,  **(3) multi-part message bodies**, and (4) textual header information in character sets other than US-ASCII.


#### 13 July 2018
**TODO**
- Bitmap via NFC: looks like I need to send the bits over...*what is getting sent over now?*. Added a new arduino file: read-img-from-nfc to start to see what the file looks like. Seems like I'll need to send it over in the format? Many questions abound here.
- figure out if I can use [GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) on the MSP430
- Look at partial update code from NXP: https://github.com/molecule/AlterWear/blob/master/e-ink/EPD%20extension%20board%20for%20partial%20update%20v1.0_beta.rar
- ~~prettify/customize the app~~ (Renamed it, added launch icon) (will need more updating later but need to decide on interactions first).

**Notes**
- memory map: Still haven't found good docs, but experiments (and Christie) confirm NFC and I2C read from/to the same spot in memory (in other words I can write via NFC and read it via I2C). Haven't tried the reverse, but should be fine.
- Android app: switched over to the example from codexpedia since it is sooo much simpler. Brought the "dialog box" way of updating an NFC tag because the UX is so much better. Frankenstein is pretty good. New code: https://github.com/molecule/android_nfc_read_write
- Info about how the code goes through the images.
```
  case EPD_2_0: {
  this->lines_per_display = 96;
		this->dots_per_line = 200;
		this->bytes_per_line = 200 / 8;
		this->bytes_per_scan = 96 / 4;
  ```
- There are 96 lines per display for 2.0. Each line has 200/8=25 bytes, so that's 25 * 96 = 2400 bytes just in the image part. ~~So reading 1000 bytes might get me somewhere.~~ It didn't....the bits that I'm printing out dont' seem to match the bits I see in the cat_2_0.xbm file at all. I assume it's a printing issue....
- This might be useful at some point: Display bitmap in Android: https://stackoverflow.com/questions/4929989/how-to-display-bitmap-image-in-android
- I should get the teeniest xbm file, see what it looks like in bits, and see if I can send it over nfc.
  - Useful: https://stackoverflow.com/questions/15941643/nfc-send-image-jpeg
  - Useful: https://developer.android.com/training/beam-files/send-files
- But the arduino code just references the name "IMAGE_X_FILE_BITS" - so reading the bits directly wouldn't be the right thing. There must be somehwere where they actually use the .xbm file format....**Q:** where is that?
   - arduino printing out bits starting at ImAGE_1_BITS seems to be...gibberish?

#### July 9 2018
**TODO**
- try sending over a simple bitmap, and loading it from memory in Arduino code (as opposed to compiling it in).
- figure out memory map: get good docs
- figure out if I can use [GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library) on the MSP430

**Notes**
- Reading from the NFC works via Android. Basically, you capture the intent and automatically do a read whenever you write. Specifically, this line:

```
record.setText(new String(message.getRecords()[0].getPayload(), "UTF-8"));
```

Displays whatever was last written to the NFC tag. (That line is called just before I write, so the basic interaction with an NFC tag automatically reads it. (THere are probably ways to encrypt or hide stuff, but this is fine for now).
- This app will also successfully read: https://github.com/codexpedia/android_nfc_read_write
- eink/i2c-basic-test seems to be reading from memory somewhere. I need to read the docs to understand where, and would ideally like to confirm that it contains what I sent over "Sell your cleverness and buy bewilderment".

- **Q:** Where is it reading FROM?
   - [This code from the codexpedia example](https://github.com/codexpedia/android_nfc_read_write/blob/master/app/src/main/java/com/example/peng/nfcreadwrite/MainActivity.java#L89) seems to imply it's automatically bundled in an "NdefRecord" that gets sent when an NFC tag is activated.
   - [This article by Shane Tully](https://shanetully.com/2012/12/writing-custom-data-to-nfc-tags-with-android-example/) further confirms that you capture an intent when the tag is activated, and can immediately read and write.
- **Q2:** What is the actual memory layout of the NFC, and how does that interact with I2C and NFC?
   - All links to docs I've found are giving [404 page not found errors](https://github.com/repaper/gratis/issues/78) :(
  
Printout from eink/i2c-basic-test (after loading "sell your cleverness and buy bewilderment":
```
i: 10, desired_state: 83
i: 11, byte: 101              e
i: 12, byte: 108              l
i: 13, byte: 108              l
i: 14, byte: 32               [space]
i: 15, byte: 121              y
i: 16, byte: 111              o

```
  - BOOM: Ok, so NFC and I2C are certainly reading from the same memory space, starting at address: ```#define int_reg_addr 0x01      //first block of user memory``` Next I need to try sending over a simple bitmap, and loading it from there in Arduino code.

- **Q3:** What about partial update?
   - This seems to be all done in SW. See video demos [here](https://www.youtube.com/watch?v=enzUbiSWenQ) and [here.](https://github.com/repaper/gratis#fast-update-notes-july-2017)
   - [Rumor](https://github.com/repaper/gratis/issues/48) has it that Adafruit's GFX library also does it. (as well as [text](https://github.com/repaper/gratis/issues/46))
        - More info about the GFX lib [here](https://learn.adafruit.com/adafruit-gfx-graphics-library)
- **Q4:** Can I use GFX on the MSP430?
   - The GFX lib "require 2 complete frame-buffers to update the display from SRAM." [[src](https://learn.adafruit.com/repaper-eink-development-board/libraries-and-examples)]


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
