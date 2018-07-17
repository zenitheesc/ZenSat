/*  
 *  ZenSat 1.0 ADC STM32 Code
 *  (C) Francesco Rossi Lena
 *  francesco.lena@usp.br
 *  Jul. 2018
 *  
 *  
 *  ACTIONS
 *  0 = wait;
 *  1 = stabilize spin!
 *  2 = stabilize to an angle
 *  3 = send all K values
 *  4 = slow slew rate CW
 *  5 = slow slew rate CCW
 *  6 = medium slew rate CW
 *  7 = medium slew rate CCW
 *  8 = spin to an desidered speed CW (next int is the speed from 0 to 100%)
 *  9 = spin to an desideres speed CCW (next int is the speed from 0 to 100%)
 *  10 = no change, keep running
 */


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
  start();
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  w = -1*gyro.z();
  Input = w;
  Setpoint = 0;
  myPID.SetOutputLimits(-100, 50);
  myPID.SetMode(AUTOMATIC);
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

}

void set_mode(int mode){
  switch (mode){
    case 0:
       wait();
       break;
    case 1:
        slew_control(0, 0);
       break;
    case 2:
        go_to_angle();
       break;
    case 3:
        send_k_values();
       break;
    case 4:
       slew_control(slow_rate, 1);
       break;
     case 5: 
       slew_control(slow_rate, 0);
       break;
     case 6:
       slew_control(medium_rate, 1);
       break;
     case 7:
       slew_control(medium_rate, 1);
       break;
     case 8:
       direct_motor_speed(1,1);
       break;
     case 9:
       direct_motor_speed(1,1);
     case 10:
       break;
     default:
       wait();
       break;
  }
}


void slew_control(int slew_rate, int slew_direction){
  Setpoint = slew_rate;
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  delay(300);
  Input = gyro.z();
  myPID.Compute();
  vel = 255*read_speed/6000 + Output;
  Serial.println(vel);
  analogWrite(Pin, vel);
}

void go_to_angle(){
}

void send_k_values(){

}

void direct_motor_speed(int percentage, int speed_dir){
  digitalWrite(Dir_Pin, speed_dir);
  analogWrite(Pin, 255*percentage);
}

void wait(){
  delay(500);
  set_mode(request_action());
}

int request_encoder(){
  Wire.requestFrom(8, 1);    
  while (Wire.available()) { 
    int requested_speed = Wire.read()*120; 
    return(requested_speed);
  } 
}

int request_action(){
  Wire.requestFrom(9, 1);    
  while (Wire.available()) { 
    int action = Wire.read(); 
    return action; 
  } 
}

void start(){
  digitalWrite(Dir_Pin, Dir);
  analogWrite(Pin, 100);
  delay(start_time_ms);
  vel = 100;
}

void send_status(int mode, int angular_speed_z, int euler_x, int encoder_speed, int target_slew, int temperature){
  stringdata.concat(mode); stringdata.concat(";");
  stringdata.concat(angular_speed_z); stringdata.concat(";");
  stringdata.concat(euler_x); stringdata.concat(";");
  stringdata.concat(encoder_speed); stringdata.concat(";");
  stringdata.concat(target_slew); stringdata.concat(";");
  stringdata.concat(temperature); stringdata.concat(";");
  char chardata[32];
  stringdata.toCharArray(chardata, 32);
  Wire.beginTransmission(9);
  Wire.write(chardata);             
  Wire.endTransmission();  
}
