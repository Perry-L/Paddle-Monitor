void sessionREAD(byte findSession) {
  File dataFile = SD.open("sessions.txt", FILE_READ);
  Serial.println("\nREADING SESSIONS\n");
  TotalSessions = 0;
  int counter = 0;
  while (dataFile.available()) {
    String buf = dataFile.readStringUntil('\n');

    uint16_t CommaPos[3];
    CommaPos[0] = buf.indexOf(',');
    CommaPos[1] = buf.indexOf(',', CommaPos[0] + 1);
    CommaPos[2] = buf.indexOf(',', CommaPos[1] + 1);
    CommaPos[3] = buf.indexOf(',', CommaPos[2] + 1);
    bool effort = 0; uint16_t Effortlen = 0; String Sessionname; bool beginOrEnd = 0; bool unit = 0;

    if (buf.charAt(0) == '0') {
      effort = LOW;
    } else if (buf.charAt(0) == '1') {
      effort = HIGH;
    }

    String lengths; // length
    for (int i = CommaPos[0] + 1; i < CommaPos[1]; i++) {
      lengths += buf.charAt(i);
    }
    Effortlen = lengths.toInt();
    for (int i = CommaPos[1] + 1; i < CommaPos[2]; i++) { // name
      Sessionname += buf.charAt(i); //Serial.println(i);
    }
    if (buf.charAt(CommaPos[2] + 1) == '0') {
      beginOrEnd = LOW;
    } else if (buf.charAt(CommaPos[2] + 1) == '1') {
      beginOrEnd = HIGH;
    }

    if (buf.charAt(CommaPos[3] + 1) == '0') {
      unit = LOW;
    } else if (buf.charAt(CommaPos[3] + 1) == '1') {
      unit = HIGH;
    }

    //Serial.print(effort); Serial.print(", "); Serial.print(Effortlen);
    //Serial.print(", "); Serial.print(Sessionname);Serial.print(", "); Serial.print(beginOrEnd);Serial.print(", "); Serial.println(unit);
    //Serial.print(CommaPos[0]);Serial.print(", ");Serial.print(CommaPos[1]);Serial.print(", ");Serial.print(CommaPos[2]);Serial.print(", ");Serial.println(CommaPos[3]);

    //======================
    //Session Start Detect
    //======================
    
    if (effort == 1 and beginOrEnd == 1 and TotalSessions <= MAX_SESSIONS) { //We have found the beggining of a session
      switch (TotalSessions){
        case 0: Sessionname.toCharArray(SessionName1, 16); break;// IF YOU WANT MORE SESSION CREATE MORE OF THESE WITH INCREASING NUMBERS AND CHANGE MAX_SESSIONS
        case 1: Sessionname.toCharArray(SessionName2, 16); break;
        case 2: Sessionname.toCharArray(SessionName3, 16); break;
        case 3: Sessionname.toCharArray(SessionName4, 16); break;
        case 4: Sessionname.toCharArray(SessionName5, 16); break;
      }
      SessionLengths[TotalSessions] = Effortlen;//STORE OTHER DATA
      SessionUnits[TotalSessions] = unit;
      
      if (findSession != 255){
        if (TotalSessions = findSession){
          RunningSessionLine = counter;
        }
      }
      TotalSessions++;
    }//END Beggining finder
  counter++;
  }//end while data.available() loop
  dataFile.close();

}//END VOID

void sessionWrite() {

}

void sessionRun(byte SessionNum) {
  if (!setupSession){//SETUP CODE
    sessionREAD(SessionNum);// WE HAVE NOW FOUND AND STORED THE LINE NUMBER
    w = 1; variables();
    for (int i = 0; i <= 10; i++){
      distancelarge = 0; calorie = 0; //clear accumulating variables
      w = 0; variables(); //ClearVariables
      //Serial.println("w set to zero");
    }
    Serial.println("Session Setup");
    setupSession = HIGH;
    
  }else{//RUN CODE
    if ((currentUnit == LOW and distance - innitLengthCovered  >= lengthtoCover/1000) or (currentUnit == HIGH and millis() - innitLengthCovered  >= lengthtoCover*1000)){ //last effor finished.
      RunningSessionLine++;//Go To Next Line
      PlayTone = HIGH;
      SessionChangeValues = HIGH;
      
      //Serial.println(millis()-innitLengthCovered);
      //Serial.print("effort compleat SD Opended = ");
      File dataFile = SD.open("sessions.txt", FILE_READ);// so read the next
      //Serial.println(dataFile);
      uint16_t counter = 0;
      while(dataFile.available()){
        String buf = dataFile.readStringUntil('\n');//READ LINE
        if (counter == RunningSessionLine){//Correct line found read data
          uint16_t CommaPos[3];
          CommaPos[0] = buf.indexOf(',');
          CommaPos[1] = buf.indexOf(',', CommaPos[0] + 1);
          CommaPos[2] = buf.indexOf(',', CommaPos[1] + 1);
          CommaPos[3] = buf.indexOf(',', CommaPos[2] + 1);
          bool effort = 0;  bool beginOrEnd = 0;  //We don't need the name but other data is useful
          if (buf.charAt(0) == '0') {
            currentEffort = LOW;
          } else if (buf.charAt(0) == '1') {
            currentEffort = HIGH;
          }
          String lengths; // length
          for (int i = CommaPos[0] + 1; i < CommaPos[1]; i++) {
            lengths += buf.charAt(i);
          }
          lengthtoCover = lengths.toInt();
          
          if (buf.charAt(CommaPos[2] + 1) == '0') {
            beginOrEnd = LOW;
          } else if (buf.charAt(CommaPos[2] + 1) == '1') {
            beginOrEnd = HIGH;
          }
          if (buf.charAt(CommaPos[3] + 1) == '0') {
            currentUnit = LOW;
          } else if (buf.charAt(CommaPos[3] + 1) == '1') {
            currentUnit = HIGH;
          }
          if (currentEffort == LOW and beginOrEnd == HIGH){
            //EndFound
          }
          //Serial.print("Effort Found: ");
          //Serial.print(lengthtoCover); Serial.print(", "); Serial.println(currentUnit);
        }
        counter++;
      }
      dataFile.close();
      //Serial.print("Setting innitLengthCovered = ");
      if(!currentUnit){//m
        innitLengthCovered = distance;
      }else{ // sec
        innitLengthCovered = millis();
      }
      //Serial.println(innitLengthCovered);

  }
    
    


    
  }

}
