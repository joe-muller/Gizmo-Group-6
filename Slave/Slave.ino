
#define baudRate 57600

#include <Wire.h>

void setup() {
  Wire.begin(8);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(baudRate);

}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    char c = Wire.read(); 
    Serial.print(c);       
  }
  int x = Wire.read();    
  Serial.println(x);      
}
