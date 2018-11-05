Wire.beginTransmission (0x29);

if (Wire.endTransmission () == 0) {

  if(init_tof == true){                 // initialize tof after first response
  tof.init();
  tof.setTimeout(500);

  if (tof_rangeMode == 1){// LongRange // lower the return signal rate limit (default is 0.25 MCPS)
  tof.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  tof.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  tof.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  }

  if (tof_rangeMode == 2){// HighSpeed // reduce timing budget to 20 ms (default is about 33 ms)
  tof.setMeasurementTimingBudget(20000);
  }
  if (tof_rangeMode == 3){// HighAccuracy // increase timing budget to 200 ms
  tof.setMeasurementTimingBudget(200000);
  }
   
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 30, "TOF connected");
  display.display(); 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1000);
  init_tof = false ;
  TOF_Tool = true ;
  i_display_buffer=0;

  for (int i = 0; i <= 127 ; i++) { // deleting stored values in array 
      display_buffer[i]=0;
  }
  
  }



  tof_distance = tof.readRangeSingleMillimeters()+tof_offset;  
  
  mystring = "Distance: "; 
  mystring += String(tof_distance);
  mystring += "mm";
  display.drawString(20,54,mystring);

  display_buffer[i_display_buffer]=tof_distance;  // storing the actual temperature in a ring buffer
  i_display_buffer++;
  if(i_display_buffer>127){i_display_buffer=0;}
  
  for (int i = 1; i <= 128 ; i++) { // plotting the trend   "i" represents the pixel to draw
      temp = i+i_display_buffer;
      if(temp > 127){
        temp=temp-128;
      }
      if(temp == 0){
        display.drawLine(i , 50-(display_buffer[127]-min_display)/scale_display , i+1 , 50-(display_buffer[temp]-min_display)/scale_display );
      }else      
        display.drawLine(i , 50-(display_buffer[temp-1]-min_display)/scale_display , i+1 , 50-(display_buffer[temp]-min_display)/scale_display );
  }


  plotWebsite = "<svg height='300' width='512'><polyline points='";
    for (int i = 1; i <= 128 ; i++){ //draw the lines of the FFT on the webpage
      temp = i+i_display_buffer;
      if(temp > 127){
        temp=temp-128;
      }      
      plotWebsite += i*4;
      plotWebsite += ",";
      if(temp == 0){
        plotWebsite += 256-(display_buffer[temp]-min_display)/(scale_display/4);
      }else
        plotWebsite += 256-(display_buffer[temp-1]-min_display)/(scale_display/4);
      plotWebsite += " ";
    }
    plotWebsite += "' style='fill:none;stroke:black;stroke-width:1' />  Sorry, your browser does not support inline SVG.";
    plotWebsite += "<text x='05' y='15' fill='blue'>current reading: ";
    plotWebsite += tof_distance;
    plotWebsite += " mm </text>";
    
    plotWebsite += "</svg> ";   
    
    if(datalog){//logging of the data
    mystring="";
    mystring=datafile+="\0";
    File dataFile = SD.open(mystring+=".csv", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.print((int)millis()-lastmillis);
      dataFile.print(",");
      dataFile.print((float)tof_distance);
      dataFile.print(";");
      dataFile.println("");
      dataFile.close();
      display.drawString(120, 20, "#");
    }else{display.drawString(20, 20, "filename corrupt");}
    }





  
  
  }// END OF TOF LOOP 


if (Wire.endTransmission () != 0) {
   init_tof = true ;
   TOF_Tool=false;
}
