// -*- mode: c++ -*-
// Copyright 2013-2015 Pervasive Displays, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at:
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied.  See the License for the specific language
// governing permissions and limitations under the License.

// Updated 2015-08-01 by Rei Vilo
// . Added #include Energia
// . For Energia, changed pin names to pin numbers (see comment below)
// . Works on MSP430F5529, LM4F120, TM4C123
// . Fails on MSP432 and CC3200

// Notice: ***** Generated file: DO _NOT_ MODIFY, Created on: 2016-01-12 00:11:21 UTC *****


// Simple demo to toggle EPD between two images.

// Operation from reset:
// * display version
// * display compiled-in display setting
// * display EPD FLASH detected or not
// * display temperature (displayed before every image is changed)
// * clear screen
// * delay 5 seconds (flash LED)
// * display text image
// * delay 5 seconds (flash LED)
// * display picture
// * delay 5 seconds (flash LED)
// * back to text display


#if defined(ENERGIA)
#include <Energia.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>
#include <ctype.h>

// required libraries
#include <SPI.h>
//#include <EPD_FLASH.h>
//#include <EPD_V110_G1.h>
#include <EPD_V231_G2.h>
#define SCREEN_SIZE 200
#include <EPD_PANELS.h>
//#include <S5813A.h>
#include <EPD_PINOUT.h>

// select two images from:  text_image text-hello cat aphrodite venus saturn
#define IMAGE_1  cat
#define IMAGE_2  saturn

// Error message for MSP430
//#if (SCREEN_SIZE == 270) && defined(__MSP430G2553__)
//#error MSP430: not enough memory
//#endif

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

// button setup
//const int buttonPin = PUSH2;     // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
//int lastButtonState = LOW;   // the previous reading from the input pin
//long lastDebounceTime = 0;  // the last time the output pin was toggled
//long debounceDelay = 50;    // the debounce time; increase if the output flickers

#define Pin_RED_LED 13

// I/O setup
void setup() {
  
  //pinMode(buttonPin, INPUT_PULLUP);
        
//        WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
//        P1DIR = 0x01;                             // P1.0 output, else input
//        P1OUT =  0x8;                            // P1.4 set, else reset
//        P1REN |= 0x8;                            // P1.4 pullup
//        P1IE |= 0x8;                             // P1.4 interrupt enabled
//        P1IES |= 0x8;                            // P1.4 Hi/lo edge
//        P1IFG &= ~0x8;                           // P1.4 IFG cleared
        
  pinMode(Pin_RED_LED, OUTPUT);
  //pinMode(Pin_SW2, INPUT);
  //pinMode(Pin_TEMPERATURE, INPUT);
#if EPD_PWM_REQUIRED
  pinMode(Pin_PWM, OUTPUT);
#endif
  pinMode(Pin_BUSY, INPUT);
  pinMode(Pin_RESET, OUTPUT);
  pinMode(Pin_PANEL_ON, OUTPUT);
  pinMode(Pin_DISCHARGE, OUTPUT);
  pinMode(Pin_BORDER, OUTPUT);
  pinMode(Pin_EPD_CS, OUTPUT);
  //pinMode(Pin_EPD_FLASH_CS, OUTPUT);

  digitalWrite(Pin_RED_LED, LOW);
#if EPD_PWM_REQUIRED
  digitalWrite(Pin_PWM, LOW);
#endif
  digitalWrite(Pin_RESET, LOW);
  digitalWrite(Pin_PANEL_ON, LOW);
  digitalWrite(Pin_DISCHARGE, LOW);
  digitalWrite(Pin_BORDER, LOW);
  digitalWrite(Pin_EPD_CS, LOW);
  //digitalWrite(Pin_EPD_FLASH_CS, HIGH);

  Serial.begin(9600);
  delay(500);

  Serial.println();
  Serial.println();
  Serial.println("Demo version: " DEMO_VERSION);
}


static int STATE = 1;


// main loop
void loop() {
    digitalWrite(Pin_RED_LED, LED_ON);
    changeimage();
    Serial.println("LED on...");
    Serial.print("STATE: ");
    Serial.println(STATE);
    delay(5000);
    digitalWrite(Pin_RED_LED, LED_OFF);
    changeimage();
    Serial.println("LED off...");
    Serial.print("STATE: ");
    Serial.println(STATE);
    delay(5000);  
}

void changeimage(){
  int temperature = 40;

  EPD.begin(); // power up the EPD panel
  EPD.setFactor(temperature); // adjust for current temperature

  int delay_counts = 0;
  switch(STATE) {
  default:
  case 1:         // clear -> text
#if EPD_IMAGE_ONE_ARG
    EPD.image(IMAGE_1_BITS);
#elif EPD_IMAGE_TWO_ARG
    EPD.image_0(IMAGE_1_BITS);
#else
#error "unsupported image function"
#endif
    ++STATE;
    break;

  case 2:         // text -> picture
#if EPD_IMAGE_ONE_ARG
    EPD.image(IMAGE_2_BITS);
#elif EPD_IMAGE_TWO_ARG
    EPD.image(IMAGE_1_BITS, IMAGE_2_BITS);
#else
#error "unsupported image function"
#endif
    ++STATE;
    break;

  case 3:        // picture -> text
#if EPD_IMAGE_ONE_ARG
    EPD.image(IMAGE_1_BITS);
#elif EPD_IMAGE_TWO_ARG
    EPD.image(IMAGE_2_BITS, IMAGE_1_BITS);
#else
#error "unsupported image function"
#endif
    STATE = 2;  // back to picture next time
    break;
  }
  EPD.end();   // power down the EPD panel  
  
}
