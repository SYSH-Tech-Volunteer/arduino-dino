#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON,HIGHT,WIDTH;
const boolean 
  DINO[HIGHT][WIDTH]={
    {},{}
  },
  TREE[][]={
    {},{}
  };
byte i,j;
void dino(byte x,byte y){
  for(i=0;i<HIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(DINO[i][j])display.drawPixel(x,y,SSD1306_WHITE);
      else ssd.draw(0,SCREEN_HEIGHT-HIGHT,SSD1306_INVERSE);
    }
  }
}
void setup(){
  pinMode(BUTTON,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
}
void loop(){
  dino(0,0);
  if(!digitalRead(BUTTON))dino(0,SCREEN_HEIGHT-HIGHT);
}
