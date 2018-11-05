

#include <SPI.h>    //include SPI library
#include <SD.h>     //include SD-Card library
#include "Wire.h"   //include I2C library

#include "SH1106.h"     // https://github.com/squix78/esp8266-oled-ssd1306
SH1106 display(0x3c, 4, 5); // 1.3" OLED display object definition (address, SDA, SCL) Connect OLED SDA , SCL pins to ESP SDA, SCL pins






