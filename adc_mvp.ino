#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <PID_v1.h>
#include <Wire.h>
int w = 0;
int set_time = 10;
float k1 = 1;
int k2 = 80;
int elapsed_time = 0;
int acel_time = 0;
int desacel_time = 0;
int Pin = 9;
bool Dir = 1;
int Dir_Pin = 8;
int set_delay = 5;
long start_time_ms = 5000;
int start_vel = 50;
long start_time = 0;
int vel = 0;
int acel_torque = 10;
int desacel_torque = -10;
int e = 0;
int encoder_speed = 0;
int multiplier = 1;
String direction_rw = "";
bool run_rw = false;
float boost = 1;

double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,0.2,1,0.1, DIRECT);

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();
  if(!bno.begin())
  {
    Serial.print("BNO falhou");
    while(1);
  }

  delay(1000);
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");
  bno.setExtCrystalUse(true);
  pinMode(Pin, OUTPUT);
  pinMode(Dir_Pin, OUTPUT);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  w = gyro.z();
  Input = w;
  Setpoint = 0;
  myPID.SetOutputLimits(-100, 100);
  myPID.SetMode(AUTOMATIC);
  analogWrite(Pin, 0);
}

void loop(void)
{
  request_action();
  delay(300);
  Serial.println("on loop");
  start();
}
void start(){
  if ( abs(get_gyro_z()) > 200 && run_rw){
    set_dir();
    stabilize();
  }
}

void set_dir(){
  float set_dir_speed = get_gyro_z();
  if (set_dir_speed > 0){
    digitalWrite(Dir_Pin, 1);
    multiplier = -1;
    direction_rw = "cw";
  }else{
    digitalWrite(Dir_Pin, 0);
    multiplier = 1;
    direction_rw = "ccw";
  }
}

float get_gyro_z(){
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  float gyro_z = gyro.z();
  return gyro_z;
}

void stabilize(){
  while(1){
    Serial.print("on stabilize, direction");Serial.println(direction_rw);
    imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    delay(300);
    w = gyro.z()*multiplier;
    Serial.println(w);
    
    if (abs(w) > 200){
      boost = 1.5;
    }else{
      boost = 1;
    }
    Input = w;
    
    myPID.Compute();
    vel = 100 + Output*boost;
    Serial.println(vel);
    analogWrite(Pin, vel);
  }
}

void request_action(){
  char c = 'o';
  Wire.requestFrom(9, 1); 
  while (Wire.available()) {  
    c = Wire.read();
  }
  if (c == 'r'){
    run_rw = true;
  }
}
    
