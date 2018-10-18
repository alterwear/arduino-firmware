/*
 * Based on the examples from the Arduino Wire library: 
 *    https://www.arduino.cc/en/Reference/Wire
 *    https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * 
 * For the UNO, these pins should be connected to I2C: Uno, Ethernet  A4 (SDA), A5 (SCL)
 */

#if defined(ENERGIA)
#include <Energia.h>
#else
#include <Arduino.h>
#endif

// required libraries
#include <SPI.h>
#include <EPD_FLASH.h>
#include <EPD_V231_G2.h>
#define SCREEN_SIZE 200
#include <EPD_PANELS.h>
#include <S5813A.h>
#include <EPD_PINOUT.h>

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

// pre-processor convert to string
#define MAKE_STRING(X) #X

// Error message for MSP430
#if (SCREEN_SIZE == 270) && defined(__MSP430G2553__)
#error MSP430: not enough memory
#endif

// EEPROM
#include <EEPROM.h>
//int eeprom_addr = 0;
//int current_state = 0; 

//i2c
#include <Wire.h>
#define SLAVE_ADDR 0x55
#define int_reg_addr 0x01      //first block of user memory

byte rdata[17];

// current version number
#define DEMO_VERSION "6"

void pinSetup(){
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
}

void initializePins(){
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
}

void reportEPDInfo(){
  Serial.println();
  Serial.println();
  Serial.println("Demo version: " DEMO_VERSION);
  Serial.println("Display size: " MAKE_STRING(EPD_SIZE));
  Serial.println("Film: V" MAKE_STRING(EPD_FILM_VERSION));
  Serial.println("COG: G" MAKE_STRING(EPD_CHIP_VERSION));
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
}

void setup() {
  Wire.begin();       // join i2c bus (address arg optional for master)
  
  pinSetup();
  initializePins();
  
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.println("Code: read-bytes-from-nfc");

  reportEPDInfo();

  // configure temperature sensor
  S5813A.begin(Pin_TEMPERATURE);

  //current_state = EEPROM.read(eeprom_addr);
}

// from comment #4: https://forum.arduino.cc/index.php?topic=241663.0
unsigned long convertFromHex(int ascii){ 
 if(ascii > 0x39) ascii -= 7; // adjust for hex letters upper or lower case
 return(ascii & 0xf);
}

void loop() {

  Wire.beginTransmission(byte(SLAVE_ADDR));
  Wire.write(int_reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(byte(SLAVE_ADDR),16);

  if (Wire.available()){
    Serial.println("Wire Available, reading now...");

    // Notes from Christie:
    // you always have to read data in chunks of 16 or it'll fail, 
    // the first 9 bytes are ntag metadata,
    for (int i = 1; i <= 16; i++) {
      rdata[i] = Wire.read();
      if (i >= 10) {
        Serial.print("i: ");
        Serial.print(i);
        Serial.print(", byte: ");
        Serial.print(rdata[i]);
        Serial.print(", converted: ");
        long converted = convertFromHex(rdata[i]);
        Serial.println(converted);
      }
     }
  }
    
    //EEPROM.write(eeprom_addr, current_state);

  delay(500);                  // wait a bit since people have to read the output :)
}

