#include <NewSoftSerial.h>
#define SP2_RX 2
#define SP2_TX 3

NewSoftSerial mySerial(SP2_RX, SP2_TX); // 2 is RX, 3 is TX

int m, i, j;
byte hexread[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte initREAD[] = {0xAA, 0x00, 0x44, 0x44, 0xA8};
int x;

void setup() {
 mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
    for (m=0; m<5; m++){
    // send the request byte
    mySerial.print(initREAD[m],BYTE);
    }
    i = 0;
    while(mySerial.available() && x != 0xA8)    
      {
       hexread[i] = mySerial.read();
       i++;
      }
     for (j = 3; j < (6); j = j+1) {
     Serial.print(hexread[j]);
      }
      Serial.print(".");
    for (j = 6; j < (i-2); j = j + 1) {
    Serial.print(hexread[j]);
    }
    Serial.println("m");
    delay(3000);
}