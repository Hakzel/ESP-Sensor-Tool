#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;


bool init_apds = true;

uint16_t r, g, b, a;
