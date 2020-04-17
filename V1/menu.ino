void menu(){
  /*if (digitalRead(Encoder_button) == LOW and inMenu == LOW){
    inMenu = HIGH;
    pos, ppos = 0, 0;
    Cmain.write(0);
    screen = 0;
    refresh(0);
    lcd.setCursor(0, Selected);
    lcd.write(0);
  }*/
  
  pos = round(Cmain.read()/4);
  
  if (pos == ppos+1 and inMenu == HIGH){
    if (Selected < LCD_HEIGHT -1){
      //lcd.setCursor(0, Selected);
      //lcd.write(blank);
      refresh(0);
      
      Selected++;
      lcd.setCursor(0, Selected);
      lcd.write(0);
    }else{
      scroll++;
      refresh(1);
      lcd.setCursor(0, Selected);
      lcd.write(0);
    }
    ppos = pos;
    Serial.println("Scrolled");
  }else if(pos == ppos - 1 and inMenu == HIGH){
    if (Selected > 0){
      //lcd.setCursor(0, Selected);
      //lcd.write(blank);
      refresh(0);
      Selected--;
      lcd.setCursor(0, Selected);
      lcd.write(0);
    }else if(scroll > 0){
      scroll--;
      refresh(-1);
      lcd.setCursor(0, Selected);
      lcd.write(0);
    }
    ppos = pos;
    Serial.println("Scrolled");
  }

  //allow Selection on screens
  
  bool button_press = !digitalRead(Encoder_button);
  if (button_press == HIGH){
    Serial.println("Pressed");
    switch (screen){
      case 0://Options, swap screen to approp
        inMenu = HIGH;
        switch(Selected){
          case 0:
            screen = 2;//back
            inMenu = LOW;
          break;
          case 1:
            screen = 1; //gotoTimer
            inMenu = HIGH;
            Selected = 0;
            Serial.println("Swaped to timer");
          break;
          case 2:
            screen = 3;// gotoAdvanced
            Selected = 0;
            inMenu = HIGH;
          break;
          case 3:
            distance = 0;
            distancelarge = 0;
            Speed = 0;
            power = 0;
            w = 0;
            screen = 2;
          break;
        }
      break;
      
      case 1: //TIMER
        if (Selected == 0){
          screen = 0; Serial.print("Back");
        }else if(Selected == 1){
          bool confirm = HIGH;
          inMenu = LOW; 
          pos = round(Cmain.read()/4);
          pos = ppos;
          delay(300);
          Serial.println("startLoop");
          while(confirm == HIGH){
            pos = round(Cmain.read()/4);
            if (pos != ppos){
              timer_time += (pos - ppos);
              refresh(0);
              ppos = pos;
            }
            delay(10);
            confirm = digitalRead(Encoder_button);
            Serial.println(confirm);
          }
          inMenu = HIGH;
          delay(300);
          ptime = millis();
        }else if(Selected == 2){
          bool confirm = HIGH;
          inMenu = LOW; 
          pos = round(Cmain.read()/4);
          pos = ppos;
          delay(300);
          Serial.println("startLoop");
          while(confirm == HIGH){
            pos = round(Cmain.read()/4);
            if (pos != ppos){
              timer = !timer;
              refresh(0);
              ppos = pos;
            }
            delay(10);
            confirm = digitalRead(Encoder_button);
            Serial.println(confirm);
          }
          inMenu = HIGH;
          delay(300);
          ptime=millis();
        }
      break;
      
      case 2: //DataScreens
        screen = 0;
        inMenu = HIGH;
        Selected = 0;
        lcd.setCursor(0, Selected);
        lcd.write(0);
      break;
      
      case 3: //Advanced
        Serial.print("Advanced");
        if (Selected == 0){
          screen = 0;
        }else if (Selected == 1){
          //change k
          bool confirm = HIGH;
          inMenu = LOW; 
          pos = round(Cmain.read()/4);
          pos = ppos;
          delay(300);
          Serial.println("startLoop");
          while(confirm == HIGH){
            pos = round(Cmain.read()/4);
            if (pos != ppos){
              k += (pos-ppos)*0.05;
              refresh(0);
              ppos = pos;
            }
            delay(10);
            confirm = digitalRead(Encoder_button);
            Serial.println(confirm);
          }
          inMenu = HIGH;
          delay(300);
        }else if (Selected == 2){
          //change c
          bool confirm = HIGH;
          inMenu = LOW; 
          pos = round(Cmain.read()/4);
          pos = ppos;
          delay(300);
          Serial.println("startLoop");
          while(confirm == HIGH){
            pos = round(Cmain.read()/4);
            if (pos != ppos){
              c += (pos-ppos)*0.05;
              refresh(0);
              ppos = pos;
            }
            delay(10);
            confirm = digitalRead(Encoder_button);
            Serial.println(confirm);
          }
          inMenu = HIGH;
          delay(300);
        }
        
      break;
    }
    refresh(0);
    delay(300);
  }
  
}

void refresh(byte ScrollPositive){
  lcd.clear();
  char* memory[] = {"", "", "", ""};

  
  //Currently no scroll needed should be included to code if needed but isn't implemented at the moment
  scroll = 0;

  
  switch(screen){
    case 0: // OPTIONS MENU
      memory[0] = "Back", memory[1] = Options[0], memory[2] = Options[1], memory[3] = Options[2];
      break;
    case 1: //TIMER
      memory[0] = "Back", memory[1] = Timer[0], memory[2] = Timer[1];
      
      lcd.setCursor(12, 1);
      char timer_str[2];
      dtostrf(timer_time, 3, 0, timer_str);
      lcd.print(timer_str);
      
      if (timer == LOW){
        lcd.setCursor(12, 2);
        lcd.print("OFF");
      }else{
        lcd.setCursor(13,2);
        lcd.print("ON");
      }
      break;
    case 2:
      memory[0] = DataScreens[0], memory[1] = DataScreens[1], memory[2] = DataScreens[2], memory[3] = DataScreens[3];
      inMenu = LOW;
      
      lcd.setCursor(12, 0);
      char PowerStr[5];
      dtostrf(power, 5, 0, PowerStr);
      lcd.print(PowerStr);
      lcd.setCursor(17, 0);
      lcd.print("W");

      lcd.setCursor(12, 1);
      char SpeedStr[5];
      dtostrf(Speed, 3, 2, SpeedStr);
      lcd.print(SpeedStr);
      lcd.setCursor(17, 1);
      lcd.print("KmH");
      
      lcd.setCursor(12, 2);
      char DistStr[5];
      dtostrf(distance, 4, 2, DistStr);
      lcd.print(DistStr);
      lcd.setCursor(17, 2);
      lcd.print("Km");
      
      lcd.setCursor(12, 3);
      char StrokeStr[5];
      dtostrf(StrokeRate, 4, 0, StrokeStr);
      lcd.print(StrokeStr);

      
      break;
    case 3:
      memory[0] = "Back", memory [1] = Advanced[0], memory[2] = Advanced[1];
      lcd.setCursor(12, 1);
      char k_str[3];
      dtostrf(k, 3, 2, k_str);
      lcd.print(k_str);

      lcd.setCursor(12, 2);
      char c_str[3];
      dtostrf(c, 3, 2, c_str);
      lcd.print(c_str);

      
      break;
  }


  // Display Memory
  for (byte i = 0; i < 4; i++){
    lcd.setCursor(1, i);
    lcd.print(memory[i]);
  }


}
