void updateSaves(){
  drawSavesBarSlotText();
  String filename=String(saveSlot)+".txt";
  if(SD.exists(filename)){
    File file=SD.open(filename);
    String r;
    String g;
    String b;
    if(file){
      int cur=0;
      while(file.available()){
        char c=(char)file.read();
        if(c==',' && cur<2){
          cur++;
        }
        else{
          if(cur==0){
            r=r+c;
          }else if(cur==1){
            g=g+c;
          }else if(cur==2){
            b=b+c;
          }
        }
      }
      file.close();
    }
    String values="("+String(r)+", "+String(g)+", "+String(b)+")         ";
    drawSavesBarColorText(values);
    drawSavesBarColorView(r.toInt(),g.toInt(),b.toInt());
    updateSavedStickColors(r.toInt(),g.toInt(),b.toInt());
  }else{
    drawSavesBarColorText("                    ");
    drawSavesBarColorView(0,0,0);
  }
}

void saveColor(int r,int g,int b){
  String filename=(String)saveSlot+".txt";
  String text=String(r)+","+String(g)+","+String(b);
  if(SD.exists(filename)){
    SD.remove(filename);
  }
  File file=SD.open(filename, FILE_WRITE);
  if(file){
    text.trim();
    file.print(text);
    file.close();
  }
}

void updateCurrentStickColors(int r, int g, int b){
  for(int i=0;i<4;i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

void updateSavedStickColors(int r, int g, int b){
  for(int i=4;i<8;i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

uint16_t createRGB(int r, int g, int b)
{   
    return ((r& 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}
