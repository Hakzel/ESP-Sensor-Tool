#include <Adafruit_ADS1015.h>
Adafruit_ADS1015 adc(0x48);



bool init_adc = true;

double filter[128];
int i_filter,f_scale_ADC=4;

float temp_val;
