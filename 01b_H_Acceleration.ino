/// for FFT etc /////////////////////////////////////////////////////////

#include <SparkFun_ADXL345.h>
ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

#include "arduinoFFT.h" // Standard Arduino FFT library
// https://github.com/kosme/arduinoFFT, in IDE, Sketch, Include Library, Manage Library, then search for FFT
arduinoFFT FFT = arduinoFFT();

#define SAMPLING_FREQUENCY 512 //Hz, must be 10000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT.
#define SAMPLES 1024              //Must be a power of 2
#define amplitude 45  //max amplitude in Pixel
#define dmg_width 128 //maximum width of bearing detection bars
//#define DEVICE (0x53)      //ADXL345 device address
//#define DEVICE (0x3A)      //ADXL345 alternative device address
bool init_adxl=true;

unsigned int sampling_period_us, counter = 0;
unsigned long microseconds;
int x, y, z; //acceleration values of all axis
double max_peak =0;
byte peak[] = {0, 0, 0, 0, 0, 0, 0};
double vReal[SAMPLES];
double vImag[SAMPLES];
float  fReal[SAMPLES / 2];
double median;
float fres; //resolution of frequency spectrum
int    dTime[SAMPLES];
unsigned long newTime = 0, oldTime = 0;
String mystring; //temporary string for multiple usage


double   dmg_inner, dmg_outer, dmg_ball, dmg_max;
int dmg_temp;
