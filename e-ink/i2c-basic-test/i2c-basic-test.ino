/*
 * Based on the examples from the Arduino Wire library: 
 *    https://www.arduino.cc/en/Reference/Wire
 *    https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * 
 * For the UNO, these pins should be connected to I2C: Uno, Ethernet  A4 (SDA), A5 (SCL)
 */

// EEPROM
//#include <EEPROM.h>

//i2c
#define SLAVE_ADDR 0x55
#define int_reg_addr 0x01      //first block of user memory

byte rdata[17];

//EEPROM
//int eeprom_addr = 0;
//int current_state = 0; 

#include <Wire.h>

void setup() {
  Wire.begin();       // join i2c bus (address arg optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.println("Code: i2c-basic-test");

  //current_state = EEPROM.read(eeprom_addr);
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
      Serial.print("i: ");
      Serial.print(i);
      if (i == 10) {
        Serial.print(", desired_state: ");
        Serial.println(rdata[i]);
      } else {
        Serial.print(", byte: ");
        Serial.println(rdata[i]);
      }
     }
     
     Serial.println("");
     Serial.println("printBits: ");
     for (int i = 1; i <=16; i++) {
       Serial.print("byte ");
       Serial.print(i);
       Serial.print(": ");
       printBits(rdata[i]);
       Serial.println("");
     }
    }
    
    //EEPROM.write(eeprom_addr, current_state);

  delay(500);                  // wait a bit since people have to read the output :)
}

// from here; http://forum.arduino.cc/index.php?topic=46320.0
void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
}
