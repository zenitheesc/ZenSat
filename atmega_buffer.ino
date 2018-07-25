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

byte marker = 0;
int i = 0;
int a = 0;
bool write_flag = false;



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
  get_SPI_data();
  //get_serial();
}

void requestEvent() {
  char chardata[6];
  comando.toCharArray(chardata, 6);
  Wire.write(chardata); 
  digitalWrite(6, 1);
  delay(500);
  digitalWrite(6, 0);
  Serial.println(comando);
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
  i = 0;
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
      stm_data.concat(c);
      health[i] = c;
      i++;
  }
  health[i] = 'x';
  Serial.println(stm_data);
  stm_data = "";
}

void get_SPI_data(){
  if((SPSR & (1 << SPIF)) != 0){
    if (write_flag){
      SPDR = health[marker];
      marker++;
    }else{
      SPDR = '0';
    }
    char c = SPDR;
    if (char c = 'c'){
      write_flag = true;
    }
    if (c != 'x'){
      data_spi.concat((char)SPDR);
    }else{
      write_flag = false;
      //data_spi.concat("x");
      comando = data_spi;
      Serial.println(data_spi);
      data_spi = "";
      Serial.println(data_spi);
    }
    if(marker > sizeof(health)){
      marker = 0;      
    }
  }  
}

