#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <PID_v1.h>

int w = 0;
int set_time = 10;
float k1 = 1;
int k2 = 80;
int elapsed_time = 0;
int acel_time = 0;
int Pin = 9;
bool Dir = 1;
int Dir_Pin = 7;
int set_delay = 5;
long start_time_ms = 5000;
int start_vel = 50;
long start_time = 0;
int vel = 0;
int encoder_speed = 0;
int action = 0;
int read_speed = 0;
int slow_rate = 0;
int medium_rate = 0;
double Setpoint, Input, Output;
String stringdata = "";
int pos = 1;
int distance = 0;
int mode_int = 10;
String  mode_1_pos = "";
String  mode_2_pos = "";
String  mode_3_pos = "";
String  mode_4_pos = ""; 
unsigned long previousMillis = 0;
bool _flag = false;
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
  //start();
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  w = -1*gyro.z();
  Input = w;
  Setpoint = 0;
  myPID.SetOutputLimits(-100, 50);
  myPID.SetMode(AUTOMATIC);
  start();
}

void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  wait();
}

void wait(){
  delay(500);
  Serial.println("esperando");
  analogWrite(9, 200);
  //if (change_mode()){
  //  set_mode(mode_1_pos, mode_2_pos, mode_3_pos, mode_4_pos);
  //}
}


void start(){
  digitalWrite(Dir_Pin, Dir);
  analogWrite(Pin, 100);
  delay(start_time_ms);
  vel = 100;
}
