#ifndef SUMSENSOR_H
#define SUMSENSOR_H
#include "display.h"
#include <Arduino.h>
#include <Adafruit_MPU6050.h> // Library for MPU6050 accelerometer and gyroscope
#include <Adafruit_Sensor.h>  // Generic sensor library needed for the MPU6050
#include <Wire.h>             // Wire library for I2C communication

class sumsensor
{
public:
    float sumacc[3];
    float accnorm;
    float sumgyro[3];
    uint32_t sumpress[3];
    int Pin1_mode;
    int Pin2_mode;
    int Pin3_mode;
    bool being_shaked;
    bool falling;
    sumsensor(){};
    void getmpudata();
    void getpressdata();
    void sumdata();
    void dealthetft();
    void dataprint();
    void refresh()
    {
        Pin1_mode = 0;
        Pin2_mode = 0;
        Pin3_mode = 0;
        being_shaked = false;
        falling = false;
    };
};

#endif