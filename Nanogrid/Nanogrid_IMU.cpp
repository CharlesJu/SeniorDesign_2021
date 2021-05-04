#include "Nanogrid_IMU.h"
#include "Constants.h"

Nanogrid_IMU::Nanogrid_IMU(Print &print) : bno(Adafruit_BNO055(IMU_I2C_ID, IMU_I2C_ADDRESS)){
    printer = &print;
}

void Nanogrid_IMU::setup(){
    if(!bno.begin()){
        printer->println("[IMU] No module detected, check wiring");
    }
}

float Nanogrid_IMU::getRotation(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    return euler.x();
}

void Nanogrid_IMU::calibrate(){
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  printer->print("\t");
  if (!system)
  {
    printer->print("! ");
  }
  while(!(gyro > 0 && accel > 0 && mag > 0))
  if(IMUDEBUG){
    /* Display the individual values */
    printer->print("Sys:");
    printer->print(system, DEC);
    printer->print(" G:");
    printer->print(gyro, DEC);
    printer->print(" A:");
    printer->print(accel, DEC);
    printer->print(" M:");
    printer->println(mag, DEC);
  }

}