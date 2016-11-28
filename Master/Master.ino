// serial rate
#define baudRate 57600

#include <MPR121.h>
#include <Wire.h>

const int touchThreshold = 40;
const int releaseThreshold = 20;

int motorReceived[9];
byte motorValue[9];

void setup(){
  Wire.begin();  
  Serial.begin(baudRate);
  while(!Serial); 

  // 0x5C is the MPR121 I2C address on the Bare Touch Board
  if(!MPR121.begin(0x5C)){ 
    Serial.println("error setting up MPR121");  
    switch(MPR121.getError()){
      case NO_ERROR:
        Serial.println("no error");
        break;  
      case ADDRESS_UNKNOWN:
        Serial.println("incorrect address");
        break;
      case READBACK_FAIL:
        Serial.println("readback failure");
        break;
      case OVERCURRENT_FLAG:
        Serial.println("overcurrent on REXT pin");
        break;      
      case OUT_OF_RANGE:
        Serial.println("electrode out of range");
        break;
      case NOT_INITED:
        Serial.println("not initialised");
        break;
      default:
        Serial.println("unknown error");
        break;      
    }
    while(1);
  }


  MPR121.setTouchThreshold(touchThreshold);
  MPR121.setReleaseThreshold(releaseThreshold);  
}


void loop() {
  readData();
  
  Wire.beginTransmission(8);
  Wire.write(motorValue[0]);
  Wire.endTransmission();    

  delay (500);
}

void readData(){
  if(MPR121.touchStatusChanged()) MPR121.updateTouchData();
  for(int i=0; i<9; i++){     
    motorReceived[i] = MPR121.getTouchData(i);
    motorValue[i] = char(motorReceived[i]);
  }       
}


