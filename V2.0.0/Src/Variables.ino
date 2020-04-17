void variables(){
  // VARIABLES CALCULATION
  
  // calculate current power and speed
  power = (k * pow(w, 3)) / 10000;
  Speed = pow((power / c), 0.3333333333333333) * 3.6;
  
  //Catch for slow speeds
  if (power <= 1) {
    Speed = 0;
  }
  
  // Calculate Distance with the speed variable and time
  distancelarge += Speed * ((millis() - runtime) / 3.6);
  distance = (distancelarge / 1000000);
  
  
  
  if(w != wPrev){ // w has changed
    //if the second diriviative is positive we are slowing down.
    //if the gradient then becomes positive shows we are the the beginning of a stroke.
    for (int i = 0; i < 3; i++){
      StrokeData[i] = StrokeData[i+1];
    }
    StrokeData[3] = w;
    
    float gradOne = (StrokeData[0]-StrokeData[1]);
    float gradtwo = (StrokeData[1]-StrokeData[2]);
    float gradthree = (StrokeData[2]-StrokeData[3]);
    if (gradOne > 0 and gradtwo > 0 and gradthree < 0){
      // Stroke detected
      StrokeRate = (6e4/(millis()-Stroketime));
      DistancePerStroke = (distance - StrokePrevDist)*1000;

      Stroketime = millis();
      StrokePrevDist = distance;
      StrokeBeginFound = HIGH;
    }
    if (StrokeBeginFound){
      // Try To find Peak;
      if (StrokeData[2] > StrokeData[3]){
        StrokePrevPeak = StrokePeak;
        StrokePeak = (k * pow(StrokeData[2], 3)) / 10000;
        StrokeBeginFound = LOW;
      }
    }
    //tft.fillRect(160, 115, 80, 60, Orange);
    //tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); tft.setCursor(160, 140);
    //tft.println(StrokePeak);
    //tft.setCursor(160, 165); tft.print(power);

    //Serial.print(gradOne,6);Serial.print(", "); Serial.print(gradtwo,6); Serial.print(", ");Serial.println(gradthree,6);
    wPrev = w;
    
  }
  
  //Calorie equation
  calorie += (4*(power * ((millis() - runtime) /1000)) + 0.35*((millis() - runtime)/1000) )/4.2;
  
  runtime = millis();
  //END VARIABLES CALCULATION
}
