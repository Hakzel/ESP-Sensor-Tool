#include "MPU9250.h"  //https://github.com/bolderflight/MPU9250

MPU9250 IMU(Wire,0x68);
int status;

bool init_imu = true;
