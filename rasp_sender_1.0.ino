#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

int counter = 0;
String rasp_data = "";
int i = 0;
int ledState = LOW;         
unsigned long previousMillis = 0;     
const long interval = 1000;  
String lora_data = "";
String oi = "oi jonny";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin(0x8);               
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(rasp_pediu);
  pinMode(6, OUTPUT);

  Serial.println("LoRa Sender");
  LoRa.setPins(7, 9, 3);
  if (!LoRa.begin(915E6)) {
    Serial.println("Lora fail");
    digitalWrite(6, 1);
    while (1);
  }
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSpreadingFactor(7);
  LoRa.enableCrc();
}

void loop() {
   unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 4000) {
    send_data("esperando");
    Serial.println("esperando");
    previousMillis = currentMillis;
    }
  receive_data();
}

void send_data(String data_to_send){
  LoRa.beginPacket();
  LoRa.print(data_to_send);
  LoRa.endPacket(); 
}


void receiveEvent(int howMany) {
  digitalWrite(6, 1);
  Serial.println("Recebi");
  while (Wire.available()) { 
    char c = Wire.read();
    if (c != 'x'){
      rasp_data.concat(c);
      Serial.print( rasp_data);
    }else{
      send_data(rasp_data);
      rasp_data = "";
    }
    digitalWrite(6, 0);           
  }
}

void receive_data(){
  int packetSize = LoRa.parsePacket();
  lora_data = "";
  if (packetSize) {
    while (LoRa.available()) {
      lora_data.concat((char)LoRa.read());
    }
    Serial.println(lora_data); 
  }
}

void rasp_pediu() {
  char chardata[32];
  oi.toCharArray(chardata, 32);
  Wire.write(chardata); 
}
