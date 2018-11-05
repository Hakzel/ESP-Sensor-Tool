//#include "MLX90615.h"

//MLX90615 thermo(0x5B, &Wire);

#include "IO_MLX90615.h"

IO_MLX90615 thermo = IO_MLX90615();

bool init_thermo = true;

float thermo_signal_amb = 0;
float thermo_signal_obj = 0;


