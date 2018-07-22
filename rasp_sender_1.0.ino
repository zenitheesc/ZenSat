#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

int counter = 0;
String rasp_data = "";
int i = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin(0x5E);               
  Wire.onReceive(receiveEvent); 

  Serial.println("LoRa Sender");
  LoRa.setPins(7, 9, 3);
  if (!LoRa.begin(915E6)) {
    Serial.println("Lora fail");
    while (1);
  }
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSpreadingFactor(11);
  LoRa.enableCrc();
}

void loop() {

}

void send_data(String data_to_send){
  LoRa.beginPacket();
  LoRa.print(data_to_send);
  LoRa.endPacket(); 
}


void receiveEvent(int howMany) {
  while (Wire.available()) { 
    char c = Wire.read();
    if (c != 'x'){
      rasp_data.concat(c);
      Serial.print( rasp_data);
    }else{
      send_data(rasp_data);
      rasp_data = "";
    }           
  }
}
