#include <Wire.h>
char inChar; // Where to store the character read
bool flag = false;
String serial_data = "";
String comando = "";
String stm_data = "";
void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  Wire.begin(9);          
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
}

void requestEvent() {
  char chardata[6];
  comando.toCharArray(chardata, 6);
  Wire.write(chardata); 
  digitalWrite(6, 1);
  delay(500);
  digitalWrite(6, 0);
}

void get_serial(){
  while(Serial.available() > 0){
    inChar = Serial.read(); // Read a character
    serial_data.concat(inChar);
    flag = true;
  }
  if (flag){
    Serial.println(serial_data);
    comando = serial_data;
    serial_data = "";
    flag = false;
  }
}


void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    stm_data.concat(c);
  }
  Serial.println(stm_data);
  stm_data = "";
}
