#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <iostream>
#include <fstream>

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <navio2/MPU9250.h>
#include <navio2/LSM9DS1.h>
#include <navio2/Util.h>

#include "util.hpp"


// CLASSES
class Accelerometer
{
    public:
        float x;
        float y;
        float z;
        float offset_x;
        float offset_y;
        float offset_z;
        float roll;
        float pitch;

        Accelerometer(void);
};

class Gyroscope
{
    public:
        float x;
        float y;
        float z;
        float offset_x;
        float offset_y;
        float offset_z;
        float roll;
        float pitch;

        Gyroscope(void);
};

class Magnetometer
{
    public:
        float x;
        float y;
        float z;
        float offset_x;
        float offset_y;
        float offset_z;
        float roll;
        float pitch;

        Magnetometer(void);
};

class IMU
{
    private:
        void obtainHardIronErrors(void);
        void obtainSoftIronErrors(void);

    public:
        InertialSensor *mpu9250;
        InertialSensor *lsm9ds1;

        Accelerometer *accel_data;
        Gyroscope *gyro_data;
        Magnetometer *mag_data;

        float roll;
        float pitch;
        float yaw;
        clock_t last_updated;

        IMU(void);
        void calibrateGyroscope(void);
        void calibrateMagnetometer(void);
        void calculateOrientationCF(void);
        void update(void);
        void print(void);
};


#endif
