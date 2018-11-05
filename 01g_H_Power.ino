#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

bool init_power = true;

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
