 /* 
Shamelessly copied from:
MehranMaleki: Arduino Examples
https://electropeak.com/learn/
*/


//Mux control pins
int s0 = 8;
int s1 = 7;
int s2 = 6;
int s3 = 5;

//Mux in "SIG" pin
int SIG_pin = 15;

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};

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
  for(int i = 0; i < 16; i ++){
//    Serial.print("Value at channel ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(readMux(i));
    
  }
  Serial.println();
  delay(10);

}


float readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};


  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  float voltage = (val * 5.0) / 1024.0;
  return voltage;
}
