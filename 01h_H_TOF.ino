
//#include "Adafruit_VL53L0X.h"
//
//Adafruit_VL53L0X tof = Adafruit_VL53L0X();

#include <VL53L0X.h>

VL53L0X tof;



bool init_tof = true;

int tof_distance;
int tof_rangeStatus;
int tof_offset=0;

