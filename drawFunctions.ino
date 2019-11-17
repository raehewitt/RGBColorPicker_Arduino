void drawSavesBar(){
  tft.fillRectangle(0,0,tft.maxX(),50,COLOR_BLACK);
}

void drawSavesBarError(){
  tft.drawText(0,10,"SD FAIL",COLOR_RED);
}

void drawSavesBarSlotText(){
  tft.drawText(0,10," Slot: "+String(saveSlot)+"       ",COLOR_WHITE);
}

void drawSavesBarColorText(String values){
  tft.drawText(0,30,values,COLOR_WHITE);
}

void drawSavesBarColorView(int r, int g, int b){
  tft.fillRectangle(100,0,tft.maxX(),49,createRGB(r,g,b));
}

void drawColorView(int r, int g, int b){
  tft.fillRectangle(0,50,tft.maxX(),tft.maxY()-20,createRGB(r,g,b));
}

void drawInfoBar(){
  tft.fillRectangle(0,tft.maxY()-20,tft.maxX(),tft.maxY(),COLOR_BLACK);
}

void drawInfoBarText(String info){
  tft.drawText(0,tft.maxY()-10,info,COLOR_WHITE);
}
