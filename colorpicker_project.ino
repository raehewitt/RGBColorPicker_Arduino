#include <SPI.h>
#include <SD.h>
#include "TFT_22_ILI9225.h";
#include <Adafruit_NeoPixel.h>

TFT_22_ILI9225 tft=TFT_22_ILI9225(8,9,10,7,200); //RST, RS, CS, LED, BRIGHTNESS
Adafruit_NeoPixel strip(8,0); //number of leds, pin number

const int pot_red=0;
const int pot_green=1;
const int pot_blue=2;
const int pot_div=4; //number to divide the pot inputs by

const int modeButton=2;
const int selectLED=5;
const int detectLED=3;

int mode=0; //0 for select, 1 for detect

const int prevButton=6;
const int nextButton=17;
const int writeButton=18;
int saveSlot=1;

bool MEMORY; //determine whether we are using SD card or not

void setup()
{
  //Serial.begin(9600);
  
  tft.begin();
  tft.setOrientation(2);
  tft.clear();
  tft.setFont(Terminal6x8);

  drawSavesBar();
  drawInfoBar();
  
  if(!SD.begin(4)){
    MEMORY=false;
    drawSavesBarError();
  }else{
    MEMORY=true;
    drawSavesBarSlotText();
    updateSaves();
  }

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  
  pinMode(modeButton,INPUT);
  pinMode(selectLED, OUTPUT);
  pinMode(detectLED, OUTPUT);
  digitalWrite(selectLED,HIGH);
  digitalWrite(detectLED,LOW);

  pinMode(prevButton,INPUT);
  pinMode(nextButton,INPUT);
  pinMode(writeButton,INPUT);
}

void loop()
{
  int modeButtonState=digitalRead(modeButton);
  if(modeButtonState==HIGH){
    if(mode==0){
      mode=1;
      digitalWrite(selectLED,LOW);
      digitalWrite(detectLED,HIGH);
      drawSavesBar();
      drawInfoBar();
    }else{
      mode=0;
      digitalWrite(selectLED,HIGH);
      digitalWrite(detectLED,LOW);
      drawSavesBar();
      drawInfoBar();
    }
    if(MEMORY){
      updateSaves();
    }
    delay(500);
  }

  int prevButtonState=digitalRead(prevButton);
  if(prevButtonState==HIGH && MEMORY){
    if(saveSlot>1){
      saveSlot--;
      updateSaves();
    }
    delay(500);
  }

  int nextButtonState=digitalRead(nextButton);
  if(nextButtonState==HIGH && MEMORY){
    saveSlot++;
    updateSaves();
    delay(500);
  }

  int writeButtonState=digitalRead(writeButton);
  if(writeButtonState==HIGH && MEMORY){
    saveColor(analogRead(pot_red)/pot_div,analogRead(pot_green)/pot_div,analogRead(pot_blue)/pot_div);
    updateSaves();
    delay(500);
  }
  
  if(mode==0){//if we're in select mode
    int r=analogRead(pot_red)/pot_div;
    int g=analogRead(pot_green)/pot_div;
    int b=analogRead(pot_blue)/pot_div;
    
    drawColorView(r,g,b);
    String values="("+String(r)+", "+String(g)+", "+String(b)+")                     ";
    drawInfoBarText(values);

    updateCurrentStickColors(r,g,b);
  }
  else{//otherwise we must be in detect mode
    drawColorView(255,255,255);
    drawInfoBarText("No RGB Detector attached"); //i aint got one yet ;)
  }
}
