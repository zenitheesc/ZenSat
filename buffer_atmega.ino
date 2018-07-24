#include <Wire.h>
#include <SPI.h>
String spi_data = "";
char inChar; // Where to store the character read
bool flag = false;
String serial_data = "";
String comando = "";
String stm_data = "";
String received_data = "";
String data_spi = "";
unsigned char hello[] = {'H','e','l','l','o',' ',
                         'R','a','s','p','i','\n'};
unsigned char health [] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
                          '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

int size_health = 0;
byte marker = 0;
int i = 0;
int a = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);

  pinMode(6, OUTPUT);
  Wire.begin(9);          
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  get_serial();
  delay(1);
  //get_SPI_data();
}

void requestEvent() {
  char chardata[6];
  comando.toCharArray(chardata, 6);
  Wire.write("1;x"); 
  digitalWrite(6, 1);
  delay(500);
  digitalWrite(6, 0);
}

void get_serial(){
  while(Serial.available() > 0){
    inChar = Serial.read();
    if (inChar != '\n'){
      serial_data.concat(inChar);
      flag = true;
    }delay(2);
  } 
  if (flag){
    Serial.println(serial_data);
    comando = serial_data;
    serial_data = "";
    flag = false;
  }
}


void receiveEvent(int howMany) {
  clean();
  i = 0;
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    health[i] = c;
    i++;
    size_health = i;
    stm_data.concat(c);
  }
  Serial.println(stm_data);
  stm_data = "";
}

void get_SPI_data(){
  if((SPSR & (1 << SPIF)) != 0){
    SPDR = health[marker];
    char c = SPDR;
    if (c != 'x'){
      data_spi.concat((char)SPDR);
    }else{
      data_spi.concat("x");
      //comando = data_spi;
      data_spi = "";
      Serial.println(comando);
    }
    marker++;
    if(marker > 30)){
      marker = 0; 

     
    }
  }  
}
