void refresh(bool FullUpdate){
  //CREATE MENU SCREEN
  //tftbuttondisplay(int x, int y, int wid, int hei, char text[], int textSize, bool pressed, textSpacex, textSpacey, color)
  // int starttime = millis(); debug time
  
      if (screen == 0){ //startup
        //Top bar
        if (FullUpdate == HIGH){
        tft.fillScreen(LightBlue);
        tft.setCursor(10, 40); tft.setTextSize(2); tft.println("Paddle Monitor"); tft.setTextColor(Black);
        tft.setCursor (50, 110); tft.setTextSize(1); tft.fillRect(30, 70, (tft.width()-90)/3, 15, Orange);tft.fillRect(30, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white);  tft.println("Just");tft.setCursor (50, 140); tft.println("Paddle");
        tft.setCursor(202, 120); tft.fillRect(180, 70, (tft.width()-90)/3, 15, Blue);tft.fillRect(180, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Session");
        tft.setCursor(365, 120); tft.fillRect(330, 70, (tft.width()-90)/3, 15, Green);tft.fillRect(330, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Race");
        tft.setCursor(50, 245); tft.fillRect(30, 190, (tft.width()-90)/3, 15, Red);tft.fillRect(30, 205, (tft.width()-90)/3, (tft.height()-60)/3-15, white);tft.println("Settings");
        tft.setTextColor(white);
        }
        //Selected
        if (UseEncoder){
          switch (Selected){
            case 0: ThickRect(30, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 1: ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(30, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 2: ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(30, 190, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 3: ThickRect(30, 190, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
          }
        }
      }
      else if (screen == 1){ //run session
        if (FullUpdate == HIGH){
          tft.fillScreen(Blue);
          ThickHLine(0, tft.height()/3-2, tft.width(), LightBlue, 4);
          ThickHLine(0, 2*tft.height()/3-2, tft.width(), LightBlue, 4);
          ThickHLine(0, 5*tft.height()/6-2, tft.width(), LightBlue, 4);
          ThickVLine(tft.width()/2-2, 0, tft.height(), LightBlue, 4);
          tft.fillRect(tft.width()/4-2, 2*tft.height()/3+2, tft.width()/2, tft.height()/3-2, LightBlue);
          //Print nonChanging words
          tft.setTextSize(1);tft.setTextColor(white);
          tft.setCursor(0+155, 0+60); tft.print("W"); tft.setCursor(tft.width()/2+165, 0+60); tft.print("Km/H");
          tft.setCursor(0+155, tft.height()/3+60); tft.print("Km");tft.setCursor(tft.width()/2+155, tft.height()/3+60); tft.print("Str/min");
          tft.setCursor(0+60, 2*tft.height()/3+33); tft.print("m/Str"); tft.setCursor(3*tft.width()/4+2+60, 2*tft.height()/3+33); tft.print("Cal");
          tft.fillRoundRect(405,280, 8, 25, 2, Red);
          tft.fillRoundRect(420,280, 8, 25, 2, Red);
        }
        // Update values
        tft.setTextSize(1); tft.setFont(&FreeSans24pt7b); tft.setTextColor(white);
        tft.fillRect(40, 28,105, 34, Blue);
        tft.setCursor(40,60); tft.print(round(StrokePeak));
        tft.fillRect(280, 28,115, 34, Blue);
        tft.setCursor(280,60); tft.print(Speed, 2);
        tft.fillRect(40, 133,115, 34, Blue);
        tft.setCursor(40,165); tft.print(distance, 2);
        tft.fillRect(280, 133,90, 34, Blue);
        tft.setCursor(280,165); tft.print(round(StrokeRate));
        tft.setFont(&FreeSans12pt7b);
        tft.fillRect(10, 230, 45, 18, Blue);
        tft.setCursor(10,247); tft.print(DistancePerStroke, 2);
        tft.fillRect(375, 230, 45, 18, Blue);
        tft.setCursor(375,247); tft.print(round(calorie));
        tft.fillRect(10, 283, 90, 18, Blue);
        tft.setCursor(10,300); if(hour() < 10){tft.print("0");tft.print(hour());}else{tft.print(hour());}tft.print(":");
        if(minute() < 10){tft.print("0");tft.print(minute());}else{tft.print(minute());}tft.print(":");
        if(second() < 10){tft.print("0");tft.print(second());}else{tft.print(second());}
        
        //In event of session running
        if (RunningSession){
          if (SessionChangeValues){
            tft.fillRect(tft.width()/4+10, 2*tft.height()/3+2,120, 40, LightBlue);
            tft.fillRect(tft.width()/4+10, 2*tft.height()/3+31,80, 44, LightBlue);
            // AREA tft.width()/2 tft.height()/3 at tft.width()/4 2*tft.height()/3
            //Length
            tft.setFont(&FreeSans18pt7b); tft.setCursor(tft.width()/4+10, 2*tft.height()/3+30); tft.setTextColor(white);
            tft.print(lengthtoCover);tft.setFont(&FreeSans12pt7b); if(currentUnit == LOW){tft.print("M");}else{tft.print("Sec");};
            //Go / easy
            tft.setCursor(tft.width()/4+10, 2*tft.height()/3+65);tft.setFont(&FreeSans18pt7b);
            if(currentEffort){tft.setTextColor(Green); tft.print("GO!");}else{tft.setTextColor(Red); tft.print("Easy");}
            
            
            SessionChangeValues = LOW;
          }
          if(!currentEffort and currentUnit){
            tft.setFont(&FreeSans18pt7b); tft.setCursor(tft.width()/4+60, 2*tft.height()/3+65);
            switch (lengthtoCover-round(((millis()-innitLengthCovered)/1000)+0.5)){
              case 3:tft.fillRect(tft.width()/4+10, 2*tft.height()/3+31,80, 44, LightBlue);tft.setTextColor(Red); tft.print("3");break;
              case 2:tft.fillRect(tft.width()/4+10, 2*tft.height()/3+31,80, 44, LightBlue);tft.setTextColor(Orange); tft.print("2");break;
              case 1:tft.fillRect(tft.width()/4+10, 2*tft.height()/3+31,80, 44, LightBlue);tft.setTextColor(Green); tft.print("1");break;
              default:break;
                
            }
          }
          //Remaining Update more often
          tft.fillRect(tft.width()/4+130, 2*tft.height()/3+2,105, 40, LightBlue);
          tft.setFont(&FreeSans18pt7b); tft.setCursor(tft.width()/4+130, 2*tft.height()/3+30); tft.setTextColor(white);
          tft.print(lengthtoCover-round(((millis()-innitLengthCovered)/1000)+0.5));tft.setFont(&FreeSans12pt7b); if(currentUnit == LOW){tft.print("M");}else{tft.print("Sec");};
          
          
        }


      
      }
      else if (screen == 2 ){ //pause session
        if (FullUpdate == HIGH){
          tftbuttondisplay(0,0, tft.width(), tft.height()/6, "Paused", 1, LOW, 195, 30, Orange);
          tftbuttondisplay(0,tft.height()/6, tft.width(), 3*tft.height()/6, "", 1, LOW, 0,0, LightBlue);
          tft.fillTriangle(220, 90, 270, 130, 220, 170, Green);
          tftbuttondisplay(0, 4*tft.height()/6, tft.width(), tft.height()/3, "Done/Save", 1, LOW, 180, 50, LightBlue);
        }
        if(UseEncoder){
          switch(Selected){
            case 0:ThickRect(0, tft.height()/6, tft.width(), 3*tft.height()/6, Blue,4); ThickRect(0, 4*tft.height()/6, tft.width(), tft.height()/3, LightBlue,4); break;
            case 1:ThickRect(0, tft.height()/6, tft.width(), 3*tft.height()/6, LightBlue,4); ThickRect(0, 4*tft.height()/6, tft.width(), tft.height()/3, Blue,4); break;
          }
        }
      }
      else if(screen == 3){ //settings
        if (FullUpdate == HIGH){
          tft.fillScreen(LightBlue); 
          tft.setCursor(10, 40); tft.setTextSize(2); tft.println("Settings"); tft.setTextColor(Black);
          tft.setCursor (60, 120); tft.setTextSize(1);tft.fillRect(30, 70, (tft.width()-90)/3, 15, Orange);tft.fillRect(30, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Timer");
          tft.setCursor(195, 120); tft.setTextSize(1);tft.fillRect(180, 70, (tft.width()-90)/3, 15, Blue);tft.fillRect(180, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Bluetooth");
          tft.setCursor(340, 120); tft.setTextSize(1);tft.fillRect(330, 70, (tft.width()-90)/3, 15, Green);tft.fillRect(330, 85, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Advanced");
          tft.setCursor(60, 240); tft.setTextSize(1);tft.fillRect(30, 190, (tft.width()-90)/3, 15, Red);tft.fillRect(30, 205, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Reset");
          tft.setCursor(195, 240); tft.setTextSize(1);tft.fillRect(180, 190, (tft.width()-90)/3, 15, Orange);tft.fillRect(180, 205, (tft.width()-90)/3, (tft.height()-60)/3-15, white); tft.println("Date/Time");
          
          tft.setCursor(360, 300); tft.println("Back <--");
        }
        if (UseEncoder){
          switch (Selected){
            case 0: ThickRect(30, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 1: ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(30, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 2: ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(180, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(30, 190, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); break;
            case 3: ThickRect(30, 190, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(330, 70, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(180, 190, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4);  break;
            case 4: ThickRect(180, 190, (tft.width()-90)/3, (tft.height()-60)/3, Blue, 4); ThickRect(30, 190, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4); ThickRect(350, 276, 120, 40, LightBlue, 4); break;
            case 5: ThickRect(350, 276, 120, 40, Blue, 4); ThickRect(180, 190, (tft.width()-90)/3, (tft.height()-60)/3, LightBlue, 4);  break;
          }
        }
        tft.setTextColor(white);
        
      }else if(screen == 4){ // timer adjust
        if (FullUpdate){
          tft.fillScreen(white);
          tft.fillRect(0,0, tft.width(), tft.height()/6, LightBlue); tft.fillRect(0,5*tft.height()/6, tft.width(), tft.height()/6, LightBlue); 
          tft.setCursor(10, 40); tft.setTextSize(2); tft.println("Timer"); tft.setTextColor(Black);
          tft.setCursor(15, 100); tft.setTextSize(1); tft.print("Time:    "); 
          tft.setCursor(15, 140); tft.setTextSize(1); tft.print("On/Off:    "); 
          tft.setCursor(360, 300);tft.setTextColor(white); tft.println("Back <--");
        }
        if(UseEncoder){
          switch(Selected){
            case 0: ThickHLine(15,105, 100, Orange, 4); ThickHLine(15,145, 150, white, 4);break;
            case 1: ThickHLine(15,145, 100, Orange, 4); ThickHLine(15,105, 120, white, 4); ThickRect(350, 276, 120, 40, LightBlue, 4);break;
            case 2: ThickRect(350, 276, 120, 40, Blue, 4); ThickHLine(15,145, 150, white, 4); break;
          }
        }
        //always update
        tft.fillRect(115, 80, 80, 80, white); tft.setTextColor(Black);
        tft.setCursor(115,100);tft.print(round(timer_time));
        tft.setCursor(115,140);if(timer){tft.print("On");}else{tft.print("Off");};
      
      }else if (screen == 5){ // Advanced // same as timer UI
        if (FullUpdate){
          tft.fillRect(0,0,tft.width(), tft.height()/6, LightBlue);tft.fillRect(0,tft.height()/6,tft.width(), 2*tft.height()/3, white);tft.fillRect(0,5*tft.height()/6,tft.width(), tft.height()/6, LightBlue); //SetBackground
          tft.setFont(&FreeSans24pt7b); tft.setCursor(10, 40);tft.setTextColor(white); tft.println("Advanced");
          tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); 
          tft.setCursor(40, 100); tft.print("Drag Factor:");
          tft.setCursor(40, 140); tft.print("Speed Factor:");
          tft.setCursor(40, 180); tft.print("FlyWheel Inertia:");
          tft.setCursor(40, 220); tft.print("Record Frequency (/second):");
          
          tft.setCursor(360, 300);tft.setTextColor(white); tft.println("Back <--");
        }
        uint16_t col = 0x0000;
        if(inMenu){col = Orange;}else{ col = Green;};
        if(UseEncoder){
            switch(Selected){
              case 0: Arrow(5, 100, col); Arrow(5, 140, white);break;
              case 1: Arrow(5, 140, col); Arrow(5, 100, white);Arrow(5, 180, white);break;
              case 2: Arrow(5, 180, col); Arrow(5, 140, white);Arrow(5, 220, white);break;
              case 3: Arrow(5, 220, col); Arrow(5, 180, white);ThickRect(350, 276, 120, 40, LightBlue, 4);break;
              case 4: ThickRect(350, 276, 120, 40, Blue, 4); Arrow(5, 220, white); break;
            }
        }
        tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); 
        tft.setCursor(200, 100);tft.fillRect(200, 83, 90, 18, white); tft.print(k, 2);
        tft.setCursor(220, 140);tft.fillRect(220, 123, 90, 18, white); tft.print(c, 2);
        tft.setCursor(240, 180);tft.fillRect(240, 163, 90, 18, white); tft.print(I, DEC);
        tft.setCursor(360, 220);tft.fillRect(360, 203, 90, 18, white); tft.print(recordFreq);

        
      }else if (screen == 6){// bluetooth // Similar to timer UI
        
      }else if (screen == 7){// Reset confirm // Similar to pause UI
        if (FullUpdate){
          tft.fillScreen(white);tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); tft.setCursor(0,40);
          tft.print("Reset, a tone will play and then the computer will reset the screen may stay on for a couple secconds ");
          tft.setCursor(40, 120); tft.print("Back");
          tft.setCursor(40, 160); tft.print("RESET");
        }
        if (UseEncoder){
          switch (Selected){
            case 0: Arrow(5, 120, Orange); Arrow(5, 160, white); break;
            case 1: Arrow(5, 120, white); Arrow(5, 160, Orange); break;
          }
        }

        
        
      }else if (screen == 8){// setDate time // similar to timer UI
        if (FullUpdate){
          tft.fillRect(0,0,tft.width(), tft.height()/6, LightBlue);tft.fillRect(0,tft.height()/6,tft.width(), 2*tft.height()/3, white);tft.fillRect(0,5*tft.height()/6,tft.width(), tft.height()/6, LightBlue); //SetBackground
          tft.setFont(&FreeSans24pt7b); tft.setCursor(10, 40);tft.setTextColor(white); tft.println("Set Time & Date");
          tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); tft.setCursor(40, 100); tft.print("Year:  Month:  Day:  Hour:    Min:    Sec:");
          tft.setCursor(360, 300);tft.setTextColor(white); tft.println("Set <--");
        }
        if(UseEncoder){
          switch(Selected){
            case 0: ThickHLine(40,105, 60, Orange, 4); ThickHLine(110,105, 150, white, 4);break;
            case 1: ThickHLine(110,105, 60, Orange, 4); ThickHLine(40,105, 60, white, 4); ThickHLine(190,105, 50, white, 4); break;
            case 2: ThickHLine(190,105, 50, Orange, 4); ThickHLine(110,105, 60, white, 4); ThickHLine(250,105, 60, white, 4); break;
            case 3: ThickHLine(250,105, 60, Orange, 4); ThickHLine(190,105, 50, white, 4); ThickHLine(320,105, 60, white, 4);break;
            case 4: ThickHLine(320,105, 60, Orange, 4); ThickHLine(250,105, 60, white, 4); ThickHLine(390,105, 60, white, 4);break;
            case 5: ThickHLine(390,105, 60, Orange, 4); ThickHLine(320,105, 60, white, 4); ThickRect(350, 276, 120, 40, LightBlue, 4);break;
            case 6: ThickRect(350, 276, 120, 40, Blue, 4); ThickHLine(390,105, 100, white, 4); break;
          }
        }
        tft.setFont(&FreeSans12pt7b); tft.setTextColor(Black); tft.setCursor(40, 140); 
        tft.fillRect(40, 123, 400, 18, white);
        tft.print(year());tft.setCursor(140, 140);
        tft.print(month());tft.setCursor(200, 140);
        tft.print(day());tft.setCursor(260,140);
        if(hour() < 10){tft.print("0");tft.print(hour());}else{tft.print(hour());}tft.setCursor(335,140);
        if(minute() < 10){tft.print("0");tft.print(minute());}else{tft.print(minute());}tft.setCursor(405, 140);
        if(second() < 10){tft.print("0");tft.print(second());}else{tft.print(second());}
      }



      else if(screen == 16){ // PICK SESSION
        if(FullUpdate){
          tft.fillRect(0,0,tft.width(), tft.height()/6, LightBlue);tft.fillRect(0,tft.height()/6,tft.width(), 5*tft.height()/6, white); //SetBackground
          tft.setFont(&FreeSans24pt7b); tft.setCursor(10, 40);tft.setTextColor(white); tft.println("Sessions");
          tft.setCursor(360, 26);tft.setTextColor(white);tft.setFont(&FreeSans12pt7b); tft.println("Back <--"); //back needs to be at the top because of the scrolling
          for(int i = 93; i < 360; i += 38){
            ThickHLine(5, i, tft.width()-10, Blue, 2);
          }
          
          tft.setTextColor(Black); tft.setFont(&FreeSans12pt7b);
          tft.setCursor(40, 92); tft.print("Paddle & Record");
          tft.setCursor(40, 130); tft.print("Create Session");
          sessionREAD(255); PageMax = TotalSessions+2;
          for (int i = 0; i < TotalSessions ; i++){
            tft.setCursor(40, i*38+168); 
            switch(i){
              case 0: tft.print(SessionName1); break;case 1: tft.print(SessionName2); break;case 2: tft.print(SessionName3); break;case 3: tft.print(SessionName4); break;case 4: tft.print(SessionName5); break;
            }
            tft.print(":-   "); 
            if (SessionUnits[i] == 1){
              tft.print(round(SessionLengths[i]/60));
              tft.print("Minutes");
            }else if(SessionUnits[i] == 0){
              tft.print(SessionLengths[i]/1000,2);
              tft.print("KM");
            }
          }
        }
        if(UseEncoder){
          switch (Selected) {
              case 0:ThickRect(350, 2, 120, 40, Blue, 4);Arrow(5,92, white);break;
              case 1:Arrow(5,92, Orange);Arrow(5, 130, white); ThickRect(350, 2, 120, 40, LightBlue, 4); break;
              case 2:Arrow(5, 130, Orange);Arrow(5,92, white);Arrow(5, 168, white); break;
              case 3:Arrow(5, 168, Orange);Arrow(5,130, white);Arrow(5, 206, white); break;
              case 4:Arrow(5, 206, Orange);Arrow(5,168, white);Arrow(5, 242, white); break;
              case 5:Arrow(5, 242, Orange);Arrow(5,206, white);Arrow(5, 280, white); break;
              case 6:Arrow(5, 280, Orange);Arrow(5,242, white); break;
          }
        }
        

      }

      
      
    
  
  // Serial.println(millis()-starttime); Debug time
}



void menuInteract(){
/*
 * this will contain all Button's interactions and will decide when to refresh depending on that
 * this program should be short and depend on the current screen
 * screen is global so no pass through
 */
 if (!UseEncoder){
  //GET TOUCH SCREEN
  TSPoint p = ts.getPoint();
  if(p.z > MINPRESSURE and p.z < MAXPRESSURE){
    // Scale from ~0->1000 to tft.width using the calibration #'s so you can go by pixel
    
    Serial.print(p.x); Serial.print(","); Serial.println(p.y);
    int tempx = p.x;
    p.x = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = tft.height()-map(tempx, TS_MINY, TS_MAXY, 0, tft.height());
  }
  switch (screen){
    case 0:// startup
    break;

    case 1: //run screen
        if(tftbutton(3*tft.width()/4+2,5*tft.height()/6+2,tft.width()/4-2, tft.height()/6-2, p.x, p.y)){
          screen = 3; //pause screen
          refresh(HIGH);
        }
    break;

    case 2: //pause screen
        
    
    break;
  }

 }else{
  // USE ENCODER TRUE
  EncoderPos = round(Selecter.read()/4);
  bool EncoderSw = !digitalRead(EncoderSwitch);
  bool NeedRefresh = HIGH;
  if (EncoderSw){
    switch (screen){
      case 0:// startup
        switch(Selected){
          case 0:
            screen = 1; Record = LOW; Selected = 0; PageMax = 0; ptime = millis();
          break;
          case 1:
            screen = 16; Selected = 0; PageMax = 0; ptime = millis(); //session
          break;
          case 2:
            screen = 13; Selected = 0; PageMax = 10; // race
          break;
          case 3:
            screen = 3; Selected = 0; PageMax = 5; // settings
          break;
        }
      break;
  
      case 1: //run screen
        screen = 2; Selected = 0; PageMax = 1; 
        if (Record){RecordPause = HIGH;Record = LOW;};
      break;
  
      case 2: //pause screen
        switch(Selected){
          case 0: 
            screen = 1; PageMax = 0; Selected = 0;
            if (RecordPause == HIGH){
              Record = HIGH; RecordPause == LOW; 
            }else{Record = LOW;} // not needed but useful for return to main screen
          break;
          case 1:
            screen = 0; Record = LOW; recordDataFinish(); PageMax = 3; Selected = 0; ptime = -1;
          break;
        }
      break;
      case 3: // Settings :D
        switch(Selected){
          case 0:
            screen = 4; PageMax = 2; Selected = 0;// Timer adjust
          break;
          case 1:
            screen = 6; PageMax = 6; Selected = 0; // Bluetooth unknown...
          break;
          case 2:
            screen = 5; PageMax = 4; Selected = 0; //Advanced 
          break;
          case 3:
            screen = 7; PageMax = 1; Selected = 0; //Reset
          break;
          case 4:
            screen = 8; PageMax = 6; Selected = 0; //SetTime
          break;
          case 5:
            screen = 0; PageMax = 3; Selected = 0;
          break;
        }
      break;
      case 4:// Timer
        switch(Selected){
          case 0:
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){timer_time += (EncoderPos- PrevEncoderPos); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 1:
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); // wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){timer = !timer; refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH;delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 2:
            screen = 3; PageMax = 5; Selected = 0;
          break;
        }
      break;
      case 5: // Advanced
        switch(Selected){
          case 0: // Drag
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){k += (EncoderPos- PrevEncoderPos)*0.01; refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 1: // Speed
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){c += (EncoderPos- PrevEncoderPos)*0.01; refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 2: // Inertia
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){I += (EncoderPos- PrevEncoderPos)*10; refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 3: // RecordFreq
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){recordFreq += (EncoderPos- PrevEncoderPos); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 4: // back
            screen = 3; PageMax = 5; Selected = 0; EEPromMem ConstMem;
            if(!(ConstMem.dragConst == k and ConstMem.SpeedConst == c and ConstMem.inertia == I)){
              ConstMem = {k, c, I};
              EEPROM.put(0, ConstMem); Serial.println("Writen to EEPROM");
            }
          break;
        }
      break;

      case 7: // RESET
        switch(Selected){
          case 0://back
            screen = 3; PageMax = 5; Selected = 0;
          break;
          case 1: // RESET
            tone(BUZZER, 1000); delay(400);
            _reboot_Teensyduino_();
          break;
        }
      break;



      case 8:
        switch(Selected){
          case 0://year
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){setTime(hour(), minute(), second(), day(), month(), year() + (EncoderPos- PrevEncoderPos)); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 1://month
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){setTime(hour(), minute(), second(), day(), month() + (EncoderPos- PrevEncoderPos), year()); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 2://day
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){setTime(hour(), minute(), second(), day() + (EncoderPos- PrevEncoderPos), month(), year()); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 3:// hour
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){setTime(hour() + (EncoderPos- PrevEncoderPos), minute(), second(), day(), month(), year()); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 4://min
            inMenu = LOW; EncoderPos = round(Selecter.read()/4); PrevEncoderPos = EncoderPos;delay(300); //wait for button to be released
            while(inMenu == LOW){ //stop other code (except interupts)
              EncoderPos = round(Selecter.read()/4); bool EncoderSw = !digitalRead(EncoderSwitch); //Get Encoder info
              if (EncoderPos != PrevEncoderPos){setTime(hour(), minute() + (EncoderPos- PrevEncoderPos), second(), day(), month(), year()); refresh(LOW); PrevEncoderPos = EncoderPos;};
              if (EncoderSw){inMenu = HIGH; delay(300);};
            }
            NeedRefresh = LOW; refresh(LOW);
          break;
          case 5:
            NeedRefresh = LOW; refresh(LOW);
            setTime(hour(), minute(), 0, day(), month(), year());
          break;
          case 6:
            screen = 3; PageMax = 5; Selected = 0; Teensy3Clock.set(now());
          break;
        }
      break;

      case 16: // Session Select
        switch(Selected){
          case 0:screen = 0; PageMax = 5; Selected = 0; break; // back
          case 1: screen = 1; recordDataStart(); Record = HIGH; ptime = millis(); PageMax = 1; Selected = 0; break;
          case 2: break; // CREATE SESSION
          case 3: screen = 1; recordDataStart(); Record = HIGH; ptime = millis(); PageMax = 1; RunningSessionNum = Selected - 3; RunningSession = HIGH; break;
        }
      break;

        
    }// END SWITCH
    if(NeedRefresh == HIGH){
      refresh(HIGH);// A full refresh is needed when the button is pressed;
      graphs(HIGH);
      NeedRefresh = LOW;
    }
    delay(300); // avoid double tap
  }// END if (EncoderSw){}
  
  // SET SELECTED
  if (EncoderPos != PrevEncoderPos and inMenu == HIGH){
    if (EncoderPos > PrevEncoderPos and Selected < PageMax and !(screen == 1)){ //CHECK IF NOT HIT  MAX
      Selected += (EncoderPos-PrevEncoderPos);
      refresh(LOW);
    }else if(EncoderPos < PrevEncoderPos and Selected > 0 and !(screen == 1)){ // CHECK IF NOT HIT MIN
      Selected += (EncoderPos-PrevEncoderPos);
      refresh(LOW);
    }
    PrevEncoderPos = EncoderPos; //Always update position incase you hit max.
  }
 
 }// END ENCODER


  
}// END SCREENS
/*Screens
  0 - startup, select what to do
  1 - run session
  2 - pause screen
  3 - settings
  4 - timer adjust
  5 - advanced
  6 - bluetooth
  7 - confirmReset
  8 - SetDateTime
  13 - race setup
  14 - race connect
  15 - race

  16 - select session
  17 - create session
  18 - select and adjust create

*/
