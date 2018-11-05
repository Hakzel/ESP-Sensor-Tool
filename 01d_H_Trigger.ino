
//Configuration of Trigger input and output

#include <pcf8574_esp.h>

PCF857x trigger(0x20, &Wire);
PCF857x trigger_out(0x27, &Wire);    


// for trigger input
bool init_trigger = true;
bool init_trigger_out = true;
bool trigger_old;

int trigger_temp;
int trigger_signal = 0;
int i_trigger_frequency;

double trigger_frequency;

String trigger_active;






//for trigger output

bool trigger_out_state = false; 
