# AlterWear
### Setup

#### E-ink Circuit
- The working one is , which [has been discontinued.](http://www.pervasivedisplays.com/kits/ext_kit). The datasheet is "EPD Extension board_Schematic_Gerber_v05" (available at the earlier link). The relevant part of [the datasheet is here.](qwantz.com)
- Adafruit's [tutorial on how to use the e-ink display board](https://learn.adafruit.com/repaper-eink-development-board/overview) we have. This also has the Arduino library that runs on the Arduino to power the board.
- Once you've installed the library, the library code we want is EPD_V230_G2 --> demo_200
- This is a screenshot of the circuit diagram [Fig. 5-1](https://www.dropbox.com/s/spbxfzleej3tsp5/Screenshot%202018-02-21%2015.26.41.png?dl=0) from the datasheet.
- PDF [datasheet for the e-ink display.](http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=232432) 
Screenshot.
- The Arduino Pro Mini is programmed over FTDI (3.3V I think).
- Pervasive Displays (e-ink manufacturer) [support](http://www.pervasivedisplays.com/contact).
 
