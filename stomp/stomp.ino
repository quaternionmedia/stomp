#include "MIDIUSB.h"

//Mux control pins
int s0 = 8;
int s1 = 7;
int s2 = 6;
int s3 = 5;
int controlPin[] = {s0, s1, s2, s3};

//Mux in "SIG" pin
int SIG_pin = 15;
int STATE[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(115200);
}


void loop(){
  
  //Loop through and read all 16 values
  for(int i = 0; i < 16; i++) {
    int mux = readMux(i);
    if ((STATE[i] > 0 && mux == 0) || (STATE[i] == 0 && mux > 0)) {
      midiEventPacket_t packet = { 0x09, 0x90, 0x3C + i, (uint8_t) mux };
      MidiUSB.sendMIDI(packet);
      MidiUSB.flush();
      STATE[i] = mux;
    }
    Serial.print(mux);
    Serial.print(" ");
  }
  Serial.println();
  delay(10);
}


float readMux(int channel) {
  digitalWrite(s0, channel & 0b0001);
  digitalWrite(s1, channel & 0b0010);
  digitalWrite(s2, channel & 0b0100);
  digitalWrite(s3, channel & 0b1000);

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);
  
  //return the value
//  float voltage = (val * 5.0) / 1024.0;
  return val >> 3;
}
