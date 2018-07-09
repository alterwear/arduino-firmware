/*
 * Based on the examples from the Arduino Wire library: 
 *    https://www.arduino.cc/en/Reference/Wire
 *    https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * 
 * For the UNO, these pins should be connected to I2C: Uno, Ethernet  A4 (SDA), A5 (SCL)
 */

// EEPROM
#include <EEPROM.h>

//i2c
#define SLAVE_ADDR 0x55
#define int_reg_addr 0x01      //first block of user memory

byte rdata[17];

//EEPROM
int eeprom_addr = 0;
int current_state = 0; 

#include <Wire.h>

void setup() {
  Wire.begin();       // join i2c bus (address arg optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.println("Code: i2c-basic-test");

  current_state = EEPROM.read(eeprom_addr);
}

static int state = 0;
byte desired_state;

void loop() {
  Serial.print("Current state: ");
  Serial.println(current_state);
  
  Serial.println("requesting from i2c....");
  //i2c: read block of user data from the device
  Wire.beginTransmission(byte(SLAVE_ADDR));
  Wire.write(int_reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(byte(SLAVE_ADDR),16);

  if (Wire.available()){
    Serial.println("Wire Available, reading now...");
    
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
      
    }
    if (idesired_state == 49){
      Serial.println("idesired_state is 49");
    } else if (idesired_state == 48){
      Serial.println("idesired_state is 48");
    } else if (idesired_state = 50){
      Serial.println("idesired_state is 50");
    }

    current_state = idesired_state;
    //EEPROM
    EEPROM.write(eeprom_addr, current_state);

  
  
  // step 5: receive reading from sensor
  /*
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read();    // receive a byte as character
    Serial.print("char: ");
    Serial.println(c);         // print the character

    Serial.print("bits: ");
    printBits(c);
  }
  */

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
