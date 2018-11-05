void setup() {

  SD.begin();

  Wire.begin(4, 5);        // join i2c bus (address optional for master)
  Serial.begin(115200);
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically(); // Adjust to suit or remove
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "Sensor-Tool V01");
  display.drawString(64, 15, "connect WiFi to:");
  display.drawString(64, 25, ssid);
  display.drawString(64, 35, password);
  display.drawString(64, 50, "© A Höffer");
  display.display();
  delay(1000);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  
  
  Sd2Card card;
  
  if(!card.init())
    {
      //display.drawString(20, 20, "SD-Card not found");
      //display.display();
      //delay(2000);
    }else{
      display.drawString(20, 20, "SD-Card found");
      display.display();
      delay(2000);
      hasSD = true;
    }
  
  
  /// initialize Webserver ///////////////////////////////////////////////

  // setup globals
  ulReqcount = 0;

  // AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  
  dnsServer.start(DNS_PORT, "*", apIP);

  //server.onNotFound([]() {
  //  server.send(200, "text/html", responseHTML);
  //});
  
  server.begin();

  
  Serial.println("HTTP server started");

  // print start page:
  server.on("/", []() {
    server.send(200, "text/html", getContent());
  });

  // control output1:
  server.on("/output1", []() {
    if (output1_state)
    {
      //digitalWrite(output1, LOW);
      output1_state = false;
    }
    else
    {
      //digitalWrite(output1, HIGH);
      output1_state = true;
    }
    server.send(200, "text/html", getContent());
  });

  // control output2:
  server.on("/datalog", []() {
    if (datalog)
    {
      //digitalWrite(output2, LOW);
      datalog = false;
    }
    else
    {
      //digitalWrite(output2, HIGH);
      datalog = true;
      lastmillis = millis();
    }
    server.send(200, "text/html", getContent());
  });

  // control trigger reset:
  server.on("/trigger_reset", []() {
    trigger_res = true;
    server.send(200, "text/html", getContent());
  });


server.on("/specificArgs", handleSpecificArg);   //Associate the handler function to the path




// things for data server on sd card


  server.on("/list", HTTP_GET, printDirectory);
  server.on("/edit", HTTP_DELETE, handleDelete);
  server.on("/edit", HTTP_PUT, handleCreate);
  server.on("/edit", HTTP_POST, [](){ returnOK(); }, handleFileUpload);
  server.onNotFound(handleNotFound);
