/*
 * Alternail: points and usage
 * 
 * Christine Dierk
 * September 15, 2016
 * 
 */

#include <EEPROM.h>

#define CLEAR_PIN 4
#define TOP_DOT 6
#define MIDDLE_DOT 1
#define BOTTOM_DOT 0
#define ACC_Z_PIN 3 
#define EXTRA_DOT 5     //reset pin 
#define REFRESH_DELAY 500 

int count = 0;
byte data;

void clearDisplay()
{

  digitalWrite(CLEAR_PIN, HIGH);
  delay(REFRESH_DELAY);
  digitalWrite(CLEAR_PIN, LOW);

}

void setDisplay(){
  if (count == 0){
    digitalWrite(TOP_DOT, LOW);
    digitalWrite(MIDDLE_DOT, LOW);
    digitalWrite(BOTTOM_DOT, LOW);
  } else if (count == 1){
    digitalWrite(TOP_DOT, LOW);
    digitalWrite(MIDDLE_DOT, LOW);
    digitalWrite(BOTTOM_DOT, HIGH);
  } else if (count == 2){
    digitalWrite(TOP_DOT, LOW);
    digitalWrite(MIDDLE_DOT, HIGH);
    digitalWrite(BOTTOM_DOT, HIGH);
  } else {
    digitalWrite(TOP_DOT, HIGH);
    digitalWrite(MIDDLE_DOT, HIGH);
    digitalWrite(BOTTOM_DOT, HIGH);
  }

  //clear display to update the dots
  clearDisplay();
  delay(REFRESH_DELAY);
}

void setup() {
  pinMode(CLEAR_PIN, OUTPUT);
  pinMode(TOP_DOT, OUTPUT);
  pinMode(MIDDLE_DOT, OUTPUT);
  pinMode(BOTTOM_DOT, OUTPUT);

  clearDisplay();

  count = EEPROM.read(0);         //get current state of the eink
}

void loop() {
  count++;
  if (count > 3){
    count = 0;
  }

  data = (0xff & count);
  EEPROM.write(0, (byte) data);     //save current state
  
  setDisplay();
  delay(5000);          //delay for 5 seconds so that it doesn't update twice

}
