/*
  Conditionals - If statement

This example demonstrates the use of if() statements.
It reads the state of a potentiometer (an analog input) and turns on an LED
only if the LED goes above a certain threshold level. It prints the analog value
regardless of the level.

The circuit:
* potentiometer connected to analog pin 0.
Center pin of the potentiometer goes to the analog pin.
side pins of the potentiometer go to +5V and ground
* LED connected from digital pin 13 to ground

* Note: On most Arduino boards, there is already an LED on the board
connected to pin 13, so you don't need any extra components for this example.

created 17 Jan 2009
modified 9 Apr 2012
by Tom Igoe

This example code is in the public domain.

http://arduino.cc/en/Tutorial/IfStatement

*/
#include <SHT1x.h>
#define dataPin 10
#define clockPin 11
SHT1x sht1x(dataPin,clockPin);
// These constants won't change:
const int analogPin0 = 0;    // pin that the sensor is attached to
const int analogPin1 = 1;
const int analogPin2 = 2;
const int ledPin = 13;       // pin that the LED is attached to
const int threshold = 60;   // an arbitrary threshold level that's in the range of the analog input
//int A = 600;
//int B = 600;
//int C = 600;
int cal_threshold;
int sensorValue;
int state;
int lastState;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communications:
  Serial.begin(9600);
  Serial.flush();
 
 
}
 
void loop() {
  // read the value of the potentiometer:
  // Serial.flush();
   // wait for incoming data
  //if (Serial.available() < 1) return; // if serial empty, return to loop().
  
   checkTemperature();
 
    checkRoadCondition();
    switch(state){
      case 0:
      Serial.println("Rain Stopped");
      break;
     case 1:
      Serial.println("Yellow: Be Aware");
      break;
     case 2:
      Serial.println("Orange: Be Prepared");
      break;
      case 3:
        Serial.println("Red: Take Action");
       break;
     default:
       Serial.println("Error: In water Sensor");
    }

  
  delay(3000);

}


  void checkTemperature(){
   float temp_c;
   //temp_c = 8;
   temp_c = sht1x.readTemperatureC();
   //Serial.println(temp_c, DEC);
   //Serial.println("C /");
  
   if( (temp_c >= -5)  && (temp_c <= 7)){
       Serial.println("Danger: Black Ice");
   }
  else if ((temp_c >= 8)&&(temp_c <=9)){
      Serial.print("Carefull: Cold");
  }
  else if ((temp_c >= 10 )&&(temp_c <= 25)){
    Serial.println("Ice Free");
  }
    delay(2000);
  }
  void checkRoadCondition(){
   
  int A = analogRead(analogPin0);
  int B = analogRead(analogPin1);
  int C = analogRead(analogPin2);
 
     // Serial.println(A);
     // Serial.println(B);
     //Serial.println(C);
      //Serial.println();
      //Serial.println();

   
    calibrate(A);
    A = sensorValue;
    //Serial.println(A);
    calibrate(B);
    B = sensorValue;
   // Serial.println(B);
    calibrate(C);
    C = sensorValue;
    //Serial.println(C);

   
    cal_threshold = A+B+C;
   // lastState = cal_threshold;
    //Serial.println(cal_threshold);
   
    if(cal_threshold == 0)
    {
      //Serial.println("Green");
      state = 0;
    }
    else if (cal_threshold == 1)
    {
      // Serial.println("Water on road.");
       state = 1;
    }
    else if (cal_threshold == 2)
    {
      state = 2;
       //Serial.println("Rain");
    }    
    else if (cal_threshold == 3)
    {
      state = 3;
       //Serial.println("Heavy Rain or Flood on road!");
    }
   delay(3000);
  }

  int calibrate(int Value)
  {
    if( (Value > 900) && (Value < 1050))
    {
        sensorValue = 0;
      //  Serial.println("Open Circuit");
    }
    if((Value > 50) && (Value < 860))
    {
     // Serial.println("Close Circuit");
      sensorValue = 1;
    }
    if(Value == 0){sensorValue = 0;}
    if(Value == 1){sensorValue = 1;}
   
  }  