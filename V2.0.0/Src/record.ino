void recordData(){
  String dataString = "";
  // as all data is calculated from w and time so other data is needed as
  dataString += String(w);
  dataString += ",";
  uint32_t low = micros64() % 0xFFFFFFFF;
  uint32_t high = (micros64()>> 32) % 0xFFFFFFFF;
  dataString += String(high);
  dataString += String(low);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  //BTStream(dataString);
  
}





void recordDataFinish(){
  // to write for end of session
  String dataString = "Finished - ";
  dataString += String(hour());
  dataString += ":";
  dataString += String(minute());
  dataString += ":" ;
  dataString += String(second());
  dataString += " ";
  dataString += String(day());
  dataString += " ";
  dataString += String(month());
  dataString += " ";
  dataString += String(year());
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void recordDataStart(){
  if (!Record){Record = HIGH;}
  String dataString = "Begun - ";
  dataString += String(hour());
  dataString += ":";
  dataString += String(minute());
  dataString += ":" ;
  dataString += String(second());
  dataString += " ";
  dataString += String(day());
  dataString += " ";
  dataString += String(month());
  dataString += " ";
  dataString += String(year());
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void recordTCXData(){
  // garmin data for exporting custom ID required for new session/effort will always be saved.
}
