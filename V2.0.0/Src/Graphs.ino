void graphs(bool FullUpdate){
  
  switch (screen){
    case 1:
      if(RunningSession){
        /*if (FullUpdate){
          ThickRect(tft.width()/4+10, 2*tft.height()/3+75, tft.width()/2-20, 30, Blue, 4); tft.fillRect(tft.width()/4+12,2*tft.height()/3+77, 88, 26, DarkRed); 
          tft.fillRect(tft.width()/4+98,2*tft.height()/3+77, 88, 26, DarkOrange);  tft.fillRect(tft.width()/4+186,2*tft.height()/3+77, 42, 26, DarkGreen);
        }else if(SessionChangeValues){
          refresh(LOW);
          ThickRect(tft.width()/4+10, 2*tft.height()/3+75, tft.width()/2-20, 30, Blue, 4); tft.fillRect(tft.width()/4+12,2*tft.height()/3+77, 88, 26, DarkRed); 
          tft.fillRect(tft.width()/4+98,2*tft.height()/3+77, 88, 26, DarkOrange);  tft.fillRect(tft.width()/4+186,2*tft.height()/3+77, 42, 26, DarkGreen);
        }
        byte GraphCovered = map(millis()-innitLengthCovered,0, lengthtoCover*1000, 0, 216);
        if (GraphCovered <= 87){
          ThickVLine(tft.width()/4+10+GraphCovered, 2*tft.height()/3+77, 26, Red,2);
        }else if (GraphCovered <= 175){
          ThickVLine(tft.width()/4+10+GraphCovered, 2*tft.height()/3+77, 26, Orange,2);
        }else if (GraphCovered <= 263){
          ThickVLine(tft.width()/4+10+GraphCovered, 2*tft.height()/3+77, 26, Green,2);
        }
        ThickVLine(tft.width()/4+12+GraphCovered,2*tft.height()/3+77, 26, Blue, 4);*/
      }else{
        switch (displayGraph){
          case 1: 
            if(FullUpdate){
              
              tft.fillRect(tft.width()/4+9, 2*tft.height()/3+5, tft.width()/2-14, tft.height()/3-14, white);
              ThickVLine(tft.width()/4+5, 2*tft.height()/3+5, tft.height()/3-10, Black, 4);
              ThickHLine(tft.width()/4+5, tft.height()-10, tft.width()/2-10, Black, 4);
            }
            uint16_t maxValue = 0; uint16_t minValue = 4000;
            for (int i = 0; i <= GraphFPS*GraphTime; i++){// Find Min Max for mapping
              if (graphData[i] > maxValue){maxValue = graphData[i]+1;};
              if (graphData[i] < minValue){minValue = graphData[i];};
            }
            //Serial.print("MAX: "); Serial.print(maxValue);
            //Serial.print("   MIN: "); Serial.println(minValue);
            float iMultiply = (tft.width()/2-14)/(GraphFPS*GraphTime);
            if(maxValue > 0 and minValue != (maxValue-1)){
              for (int i = 0; i < GraphFPS*GraphTime; i++){
                tft.drawLine(i*iMultiply+tft.width()/4+9, tft.height()-map(graphData[i], minValue, maxValue, 0, 88)-12, (i+1)*iMultiply+tft.width()/4+9,tft.height()-map(graphData[i+1], minValue, maxValue, 0, 88)-12 , white);
              }
            }
            for (int i = 0; i < GraphFPS*GraphTime; i++){
              graphData[i] = graphData[i+1];
            }
            graphData[GraphFPS*GraphTime] = power;
            maxValue = 0; minValue = 4000;
            for (int i = 0; i <= GraphFPS*GraphTime; i++){// Find Min Max for mapping
              if (graphData[i] > maxValue){maxValue = graphData[i] +1;};
              if (graphData[i] < minValue){minValue = graphData[i];};
            }
            if(maxValue > 0 and minValue != (maxValue-1)){
              for (int i = 0; i < GraphFPS*GraphTime; i++){
                tft.drawLine(i*iMultiply+tft.width()/4+9, tft.height()-map(graphData[i], minValue, maxValue, 0, 88)-12, (i+1)*iMultiply+tft.width()/4+9,tft.height()-map(graphData[i+1], minValue, maxValue, 0, 88)-12 , Black);
              }
            }
          break;
          case 2:
            
          break;
          default: break;
        }
      }

      break;
    case 15:

      break;
    default: break; // will not run, left so ensure it doesn't bug out
  }
}
