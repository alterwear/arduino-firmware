# AlterWear
## Setup

### Hardware
**Correct datasheet, we think**
- The working one is , which [has been discontinued.](http://www.pervasivedisplays.com/kits/ext_kit). The datasheet is "EPD Extension board_Schematic_Gerber_v05". The files are available at that link, but also uploaded to this repo.
- Pervasive Displays (e-ink manufacturer) [support](http://www.pervasivedisplays.com/contact). Definitely contact them if you have issues! They should help you with specific questions.

**Another datasheet, not sure what it is for**
- This is a screenshot of ANOTHER circuit diagram [Fig. 5-1](https://www.dropbox.com/s/spbxfzleej3tsp5/Screenshot%202018-02-21%2015.26.41.png?dl=0) from the datasheet.
- PDF [datasheet for the e-ink display.](http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=232432) 
Screenshot.

### Software
- Adafruit's [tutorial on how to use the e-ink display board](https://learn.adafruit.com/repaper-eink-development-board/overview) we have. This also has the Arduino library that runs on the Arduino to power the board.
- Once you've installed the library, the library code we want is EPD_V230_G2 --> demo_200
- The Arduino Pro Mini is programmed over FTDI (3.3V I think).

 

# Breakout board notes

EPD breakout board (green):
- Compatible with: 40+pin e-ink display (connector is zig-zag).
- Goals: Recreate it on the breadboard, then simplify if possible, then create an SMD version.

Teensy e-paper adapter board (red): https://hackaday.io/project/13327-teensy-e-paper-adapter-board
- Original crowdsource campaign: https://www.crowdsupply.com/soniktech/e-paper-shield-kit
- Library code and example: https://github.com/jarek319/EPD215
- Compatible with: 20+-pin e-ink displays (connector is straight).
- Goals: Get it working (library code freezes and we don't know why), recreate and build our own.


## Other notes
Technical support email: 	techsupport@pervasivedisplays.com
