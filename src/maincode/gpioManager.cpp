#include "gpioManager.h"
#include<Arduino.h>
#include "servoDriver.h"

servoDriver LEDdriver =servoDriver(0x40);

void pinManager::pinInit(int maxRooms){
  LEDdriver.begin();
  LEDdriver.setPWMFreq(100);   // 1 KHz for Led's
  delay(10);
  //LEDdriver.setPWM(0,4095,0);
  if(maxRooms>8){
    Serial.print("Number of light crossing the limit");
  }

}

void pinManager::setPinState(int roomNumber, int roomBrightness){
        //Serial.println("Setting all the data properly. Checking all the data: ");
        /*Serial.print("Room Number: ");
        Serial.println(roomNumber);
        Serial.print("LED Brightness: ");
        Serial.println(roomBrightness*16);*/
        switch(roomNumber){
                case 0: //LEDdriver.setPWM(0, ledState ? 4095:0,0);
                        LEDdriver.setPin(1,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(1, roomBrightness*16);
                        break;
                case 1: //LEDdriver.setPin(2, ledState?4095:0,0);
                        LEDdriver.setPin(3,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(3, roomBrightness*16);
                        break;
                case 2: LEDdriver.setPin(5,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(5, roomBrightness*4);
                        break;
                case 3: LEDdriver.setPin(7,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(7, roomBrightness*4);
                        break;
                case 4: LEDdriver.setPin(9,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(9, roomBrightness);
                        break;
                case 5: LEDdriver.setPin(11,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(11, roomBrightness);
                        break;
                case 6: LEDdriver.setPin(13,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(13, roomBrightness);
                        break;
                case 7: LEDdriver.setPin(15,roomBrightness*16,0);
                        //LEDdriver.writeMicroseconds(15, roomBrightness);
                        break; 
                default: Serial.println("invalid state");        

         }
  
}
void pinManager::setPinState(int roomNumber, bool ledState){
        //Serial.println("Setting all the data properly. Checking all the data: ");
        /*Serial.print("Room Number: ");
        Serial.println(roomNumber);
        Serial.print("LED state : ");
        Serial.println(ledState);*/
        
        switch(roomNumber){
                case 0: //LEDdriver.setPWM(0, ledState?950:0,0);
                        LEDdriver.setPin(0,ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(1, roomBrightness);
                        break;
                case 1: LEDdriver.setPin(2, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(3, roomBrightness);
                        break;
                case 2: LEDdriver.setPin(4, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(5, roomBrightness);
                        break;
                case 3: LEDdriver.setPin(6, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(7, roomBrightness);
                        break;
                case 4: LEDdriver.setPin(8, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(9, roomBrightness);
                        break;
                case 5: LEDdriver.setPin(10, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(11, roomBrightness);
                        break;
                case 6: LEDdriver.setPin(12, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(13, roomBrightness);
                        break;
                case 7: LEDdriver.setPin(14, ledState?4095:0,0);
                        //LEDdriver.writeMicroseconds(15, roomBrightness);
                        break; 
                default: Serial.println("invalid state");        

        }

}
int pinManager::getPinState(){
  return 0;

}