Wire.beginTransmission (0x68);

if (Wire.endTransmission () == 0) {

  if(init_imu == true){                 // initialize tof after first response
  IMU.begin();
     
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 30, "9DOF connected");
  display.display(); 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1000);
  init_imu = false ;
  IMU_Tool = true ;
    
  }

  IMU.readSensor();

  Serial.println(IMU.getTemperature_C(),6);
  delay(100);
 
  mystring = "AccX: "; 
  mystring += String(IMU.getAccelX_mss());
  //mystring += "mss";
  display.drawString(0,0,mystring);

  mystring = "AccY: "; 
  mystring += String(IMU.getAccelY_mss());
  //mystring += "mss";
  display.drawString(0,10,mystring);

  mystring = "AccZ: "; 
  mystring += String(IMU.getAccelZ_mss());
  //mystring += "mss";
  display.drawString(0,20,mystring);



  mystring = "GyrX: "; 
  mystring += String(IMU.getGyroX_rads());
  //mystring += "rads";
  display.drawString(64,0,mystring);

  mystring = "GyrY: "; 
  mystring += String(IMU.getGyroY_rads());
  //mystring += "rads";
  display.drawString(64,10,mystring);

  mystring = "GyrZ: "; 
  mystring += String(IMU.getGyroZ_rads());
  //mystring += "rads";
  display.drawString(64,20,mystring);



  mystring = "MagX: "; 
  mystring += String(IMU.getMagX_uT());
  //mystring += "uT";
  display.drawString(0,34,mystring);

  mystring = "MagY: "; 
  mystring += String(IMU.getMagY_uT());
  //mystring += "uT";
  display.drawString(0,44,mystring);

  mystring = "MagZ: "; 
  mystring += String(IMU.getMagZ_uT());
  //mystring += "uT";
  display.drawString(0,54,mystring);



  //mystring = "Temp: "; 
  mystring 
  = String(IMU.getTemperature_C());
  mystring += "°C";
  display.drawString(80,54,mystring);
  

  
  
  }// END OF IMU LOOP 


if (Wire.endTransmission () != 0) {
   init_imu = true ;
   IMU_Tool=false;
}
