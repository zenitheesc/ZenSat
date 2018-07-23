#include <SPI.h>
#include <LoRa.h>

char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
String serial_data = "";
bool flag = false;



void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(7, A0, 2);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSpreadingFactor(7);
  LoRa.enableCrc();
}

void loop() {
  get_serial();
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    delay(500);
    send_data("oie recebi");
  }
  
}
void send_data(String data_to_send){
  LoRa.beginPacket();
  LoRa.print(data_to_send);
  LoRa.endPacket(); 
}

void get_serial(){
  while(Serial.available() > 0){
    inChar = Serial.read(); // Read a character
    serial_data.concat(inChar);
    flag = true;
  }
  if (flag){
    send_data(serial_data);
    Serial.println(serial_data);
    serial_data = "";
    flag = false;
  }
}
