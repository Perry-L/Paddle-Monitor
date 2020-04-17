bool tftbutton(int x, int y, int wid, int hei, int touchx, int touchy){
  bool Pressed = LOW;
  
  //Serial.print(p.x); Serial.print(", "); Serial.println(p.y);
  if (touchx > x and touchx < x+wid and touchy > y and touchy < y+hei){
    Pressed = HIGH;
  }

  return Pressed;

}
void tftbuttondisplay(int x, int y, int wid, int hei, char text[], int textSize, bool pressed, int xBound, int yBound, uint16_t colour ){
  if (!pressed){
    tft.fillRect(x, y, wid, hei, colour);
    tft.setCursor(x+xBound, y+yBound); tft.setTextSize(textSize);
    tft.print(text);
  }else{
    tft.fillRect(x, y, wid, hei, 0x1111);
    tft.setCursor(x+xBound, y+yBound); tft.setTextSize(textSize);
    tft.print(text);
  }
}

void ThickRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour, uint8_t thickness ){
  for (uint8_t i = 0; i < thickness; i++){
    tft.drawRect(x+i,y+i,w-(2*i),h-(2*i), colour);
  }
}
void ThickHLine (uint16_t x, uint16_t y, uint16_t l, uint16_t colour, uint8_t thickness ){
  for (uint8_t i = 0; i < thickness; i++){
    tft.drawFastHLine(x,y+i,l, colour);
  }
}
void ThickVLine (uint16_t x, uint16_t y, uint16_t l, uint16_t colour, uint8_t thickness ){
  for (uint8_t i = 0; i < thickness; i++){
    tft.drawFastVLine(x+i,y,l, colour);
  }
}

void Arrow(uint16_t x, uint16_t y, uint16_t Colour){
  // x,y is the bottom corner same as with text.
  ThickHLine(x, y-10, 10, Colour, 4);
  tft.fillTriangle(x+10, y, x+10, y-16, x+25, y-8, Colour);
}
