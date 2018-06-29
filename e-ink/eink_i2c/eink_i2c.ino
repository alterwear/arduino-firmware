/*
 * Christine Dierk
 * September 9, 2017
 * 
 * Arduino code for dynamic wearable displays
 * Reads a value from i2c and then sets the connected eink display to the corresponding image
 */


#if defined(ENERGIA)
#include <Energia.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>
#include <ctype.h>

// required libraries
#include <SPI.h>
#include <EPD_FLASH.h>
#include <EPD_V231_G2.h>
#define SCREEN_SIZE 144
#include <EPD_PANELS.h>
#include <S5813A.h>
#include <EPD_PINOUT.h>

//i2c library
#include <Wire.h>

// EEPROM
#include <EEPROM.h>

// select two images from:  text_image text-hello cat aphrodite venus saturn
#define IMAGE_1  cat
#define IMAGE_2  text_image
#define IMAGE_3 saturn
#define IMAGE_4 venus

//i2c
#define SLAVE_ADDR 0x55
#define int_reg_addr 0x01      //first block of user memory

// Error message for MSP430
#if (SCREEN_SIZE == 270) && defined(__MSP430G2553__)
#error MSP430: not enough memory
#endif

// no futher changed below this point

// current version number
#define DEMO_VERSION "5"


// pre-processor convert to string
#define MAKE_STRING1(X) #X
#define MAKE_STRING(X) MAKE_STRING1(X)

// other pre-processor magic
// token joining and computing the string for #include
#define ID(X) X
#define MAKE_NAME1(X,Y) ID(X##Y)
#define MAKE_NAME(X,Y) MAKE_NAME1(X,Y)
#define MAKE_JOIN(X,Y) MAKE_STRING(MAKE_NAME(X,Y))

// calculate the include name and variable names
#define IMAGE_1_FILE MAKE_JOIN(IMAGE_1,EPD_IMAGE_FILE_SUFFIX)
#define IMAGE_1_BITS MAKE_NAME(IMAGE_1,EPD_IMAGE_NAME_SUFFIX)
#define IMAGE_2_FILE MAKE_JOIN(IMAGE_2,EPD_IMAGE_FILE_SUFFIX)
#define IMAGE_2_BITS MAKE_NAME(IMAGE_2,EPD_IMAGE_NAME_SUFFIX)
#define IMAGE_3_FILE MAKE_JOIN(IMAGE_3,EPD_IMAGE_FILE_SUFFIX)
#define IMAGE_3_BITS MAKE_NAME(IMAGE_3,EPD_IMAGE_NAME_SUFFIX)
#define IMAGE_4_FILE MAKE_JOIN(IMAGE_4,EPD_IMAGE_FILE_SUFFIX)
#define IMAGE_4_BITS MAKE_NAME(IMAGE_4,EPD_IMAGE_NAME_SUFFIX)

// Add Images library to compiler path
#include <Images.h>  // this is just an empty file

// images
PROGMEM const
#define unsigned
#define char uint8_t
#include IMAGE_1_FILE
#undef char
#undef unsigned

PROGMEM const
#define unsigned
#define char uint8_t
#include IMAGE_2_FILE
#undef char
#undef unsigned

PROGMEM const
#define unsigned
#define char uint8_t
#include IMAGE_3_FILE
#undef char
#undef unsigned

PROGMEM const
#define unsigned
#define char uint8_t
#include IMAGE_4_FILE
#undef char
#undef unsigned



// LED anode through resistor to I/O pin
// LED cathode to Ground
#define LED_ON  HIGH
#define LED_OFF LOW


// define the E-Ink display
EPD_Class EPD(EPD_SIZE,
        Pin_PANEL_ON,
        Pin_BORDER,
        Pin_DISCHARGE,
#if EPD_PWM_REQUIRED
        Pin_PWM,
#endif
        Pin_RESET,
        Pin_BUSY,
        Pin_EPD_CS);


//i2c
byte rdata_1;
byte rdata_2;
byte rdata_3;
byte rdata_4;
byte rdata_5;
byte rdata_6;
byte rdata_7;
byte rdata_8;
byte rdata_9;
byte rdata_11;
byte rdata_12;
byte rdata_13;
byte rdata_14;
byte rdata_15;
byte rdata_16;

//EEPROM
int eeprom_addr = 0;
int current_state; 

// I/O setup
void setup() {
  Wire.begin();                         // join i2c bus 
  pinMode(Pin_RED_LED, OUTPUT);
  pinMode(Pin_SW2, INPUT);
  pinMode(Pin_TEMPERATURE, INPUT);
#if EPD_PWM_REQUIRED
  pinMode(Pin_PWM, OUTPUT);
#endif
  pinMode(Pin_BUSY, INPUT);
  pinMode(Pin_RESET, OUTPUT);
  pinMode(Pin_PANEL_ON, OUTPUT);
  pinMode(Pin_DISCHARGE, OUTPUT);
  pinMode(Pin_BORDER, OUTPUT);
  pinMode(Pin_EPD_CS, OUTPUT);
  pinMode(Pin_EPD_FLASH_CS, OUTPUT);

  digitalWrite(Pin_RED_LED, LOW);
#if EPD_PWM_REQUIRED
  digitalWrite(Pin_PWM, LOW);
#endif
  digitalWrite(Pin_RESET, LOW);
  digitalWrite(Pin_PANEL_ON, LOW);
  digitalWrite(Pin_DISCHARGE, LOW);
  digitalWrite(Pin_BORDER, LOW);
  digitalWrite(Pin_EPD_CS, LOW);
  digitalWrite(Pin_EPD_FLASH_CS, HIGH);

  Serial.begin(9600);
  delay(500);

#if defined(__AVR__)
  // // indefinite wait for USB CDC serial port to connect.  Arduino Leonardo only
  // while (!Serial) {
  // }
  // additional delay for USB CDC serial port to connect.  Arduino Leonardo only
  if (!Serial) {       // allows terminal time to sync as long
    delay(500);  // as the serial monitor is opened before
  }                    // upload
#endif

  Serial.println();
  Serial.println();
  Serial.println("Demo version: " DEMO_VERSION);
  Serial.println("Display size: " MAKE_STRING(EPD_SIZE));
  Serial.println("Film: V" MAKE_STRING(EPD_FILM_VERSION));
  Serial.println("COG: G" MAKE_STRING(EPD_CHIP_VERSION));
  Serial.println();

  Serial.println("Image 1: " IMAGE_1_FILE);
  Serial.println("Image 2: " IMAGE_2_FILE);
  Serial.println();

  EPD_FLASH.begin(Pin_EPD_FLASH_CS);
  if (EPD_FLASH.available()) {
    Serial.println("EPD FLASH chip detected OK");
  } else {
    uint8_t maufacturer;
    uint16_t device;
    EPD_FLASH.info(&maufacturer, &device);
    Serial.print("unsupported EPD FLASH chip: MFG: 0x");
    Serial.print(maufacturer, HEX);
    Serial.print("  device: 0x");
    Serial.print(device, HEX);
    Serial.println();
  }

  // configure temperature sensor
  S5813A.begin(Pin_TEMPERATURE);

  current_state = 0;
  current_state = EEPROM.read(eeprom_addr);
}

static int state = 0;
byte desired_state;


// main loop
void loop() {

  Serial.print("Current state: ");
  Serial.println(current_state);
  
  int temperature = S5813A.read();
  Serial.print("Temperature = ");
  Serial.print(temperature, DEC);
  Serial.println(" Celsius");

  //i2c: read block of user data from the device
  Wire.beginTransmission(byte(SLAVE_ADDR));
  Wire.write(int_reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(byte(SLAVE_ADDR),16);

  if (Wire.available()){
    Serial.println("Wire Available");
    rdata_1 = Wire.read();
    rdata_2 = Wire.read();
    rdata_3 = Wire.read();
    rdata_4 = Wire.read();
    rdata_5 = Wire.read();
    rdata_6 = Wire.read();
    rdata_7 = Wire.read();
    rdata_8 = Wire.read();
    rdata_9 = Wire.read();
    desired_state = Wire.read();
    rdata_11 = Wire.read();
    rdata_12 = Wire.read();
    rdata_13 = Wire.read();
    rdata_14 = Wire.read();
    rdata_15 = Wire.read();
    rdata_16 = Wire.read();
  }
    Serial.println(desired_state, HEX);
    int idesired_state = (int) desired_state;
    

    // this cast makes things weird
    // send 0 via NFC, i2c reads 48
    // send 1 via NFC, i2c reads 49
    // send 2 via NFC, i2c reads 50
    // send 3 via NFC, i2c reads 51

    //right now this only supports switching between two images, but we can expand to have more!
    if (idesired_state == 255 || idesired_state == 0){
      //DO NOTHING; start-up bug
    }
    //WE CAN PROBABLY MOVE ALL OF THIS TO SETUP, SINCE EVERY I2C CHANGE WILL BE MARKED BY A POWER ON STATE
    else if (idesired_state == current_state){
      delay(1000);
      //DO NOTHING; keep checking
    } else {
          //only power on eink if we need to change it
          EPD.begin(); // power up the EPD panel
          switch (EPD.error()) {
          case EPD_OK:
            Serial.println("EPD: ok");
            break;
          case EPD_UNSUPPORTED_COG:
            Serial.println("EPD: unsuppported COG");
            break;
          case EPD_PANEL_BROKEN:
            Serial.println("EPD: panel broken");
            break;
          case EPD_DC_FAILED:
            Serial.println("EPD: DC failed");
            break;
          }
        
          EPD.setFactor(temperature); // adjust for current temperature  
      
        if (idesired_state == 49){
            EPD.image_0(IMAGE_2_BITS);
        } else if (idesired_state == 48){
            EPD.image_0(IMAGE_1_BITS);
        } else if (idesired_state = 50){
          for (int i = 0; i < 10; i++){
            EPD.image_0(IMAGE_3_BITS);
            delay(50);
            EPD.image_0(IMAGE_4_BITS);
            delay(50);
          }
        }
        

        current_state = idesired_state;
        //EEPROM
        EEPROM.write(eeprom_addr, current_state);
  
        EPD.end();   // power down the EPD panel
    }
  
}
