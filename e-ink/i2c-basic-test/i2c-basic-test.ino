/*
 * Based on the examples from the Arduino Wire library: 
 *    https://www.arduino.cc/en/Reference/Wire
 *    https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * 
 * For the UNO, these pins should be connected to I2C: Uno, Ethernet  A4 (SDA), A5 (SCL)
 */

//i2c
#define SLAVE_ADDR 0x55
#define int_reg_addr 0x01      //first block of user memory

#include <Wire.h>

void setup() {
  Wire.begin();       // join i2c bus (address optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.println("i2c-basic-test");
}

void loop() {
  Serial.println("requesting from i2c....");
  // step 4: request reading from sensor
  Wire.requestFrom(85, 16);    // request 6 bytes from slave device (address in decimal)

  // step 5: receive reading from sensor
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read();    // receive a byte as character
    Serial.print("char: ");
    Serial.println(c);         // print the character

    Serial.print("bits: ");
    printBits(c);
  }

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
