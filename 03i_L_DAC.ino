Wire.beginTransmission (0x60);

if (Wire.endTransmission () == 0) {

  if(init_DAC == true){                 // initialize adxl after first response
  dac.begin(0x60);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 30, "DAC connected");
  display.display(); 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1000);
  display.clear();                                 
  init_DAC = false ;
  DAC_Tool = true ;
  i_display_buffer=0;
  }

  for (int i = 0; i < 256; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_8Bit[i])), false);
  }

  mystring = "Sinus-Wavemode"; 
  display.drawString(20,20,mystring);

}// END OF DAC LOOP 


if (Wire.endTransmission () != 0) {
   init_DAC = true ;
   DAC_Tool=false;
}
