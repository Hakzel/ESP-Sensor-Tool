Wire.beginTransmission (0x5B);

if (Wire.endTransmission () == 0) {

  if(init_thermo == true){                 // initialize adxl after first response

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 30, "Thermo connected");
  display.display(); 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1000);
  display.clear();                                 
  init_thermo = false ;
  Thermo_Tool = true ;
  i_display_buffer=0;
  
  for (int i = 0; i <= 127 ; i++) { // deleting stored values in array 
      display_buffer[i]=0;
  }
  }

  // read Thermo Value of ambient temperature
  thermo_signal_amb = thermo.readAmbientTempC();   
  mystring = "A: "; 
  mystring += String(thermo_signal_amb);
  mystring += "°C";
  display.drawString(0,0,mystring);

  // read Thermo Value of object temperature
  thermo_signal_obj = thermo.readObjectTempC();
  mystring = "O: "; 
  mystring += String(thermo_signal_obj);
  mystring += "°C";
  display.drawString(64,0,mystring);

  // fo plotting the data the value of the object temperature is stored in an array every second
  if (millis() - lastcall > 1000){ // getting data for plotting the trend
  display_buffer[i_display_buffer]=thermo_signal_obj;  // storing the actual temperature in a ring buffer
  i_display_buffer++;
  if(i_display_buffer>=127){i_display_buffer=0;}
  lastcall=millis();  
  }
  
  for (int i = 1; i <= 128 ; i++) { // plotting the trend   "i" represents the pixel to draw
      temp = i+i_display_buffer;
      if(temp > 127){
        temp=temp-128;
      }
      if(temp == 0){  // avoiding negative indizes when plotting the line at the array startover
        display.drawLine(i , 64-display_buffer[127] , i+1 , 64-display_buffer[temp] );
      }else    // normal draw routine  
        display.drawLine(i , 64-display_buffer[temp-1] , i+1 , 64-display_buffer[temp] );
  }

}// END OF THERMO LOOP 


if (Wire.endTransmission () != 0) {
   init_thermo = true ;
   Thermo_Tool=false;
}
