#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON,DINO_HIGHT,DINO_WIDTH,TREE_HIGHT,TREEWIDTH;
const boolean 
  DINO[HIGHT][WIDTH]={
    {},{}
  },
  TREE[][]={
    {},{}
  },
  PLAY[][]={
    {},{}
  };
boolean jumpped;
byte i,j,x,y,treeMove;
void dino(){
  for(i=0;i<HIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(DINO[i][j])display.drawPixel(x+i,y+j,SSD1306_WHITE);
      else ssd.draw(0,SCREEN_HEIGHT-DINO_HIGHT,SSD1306_INVERSE);
    }
  }
}
void tree(byte x,byte y){
  for(i=0;i<HIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(TREE[i][j])display.drawPixel(x+i,y+j,SSD1306_WHITE);
      else ssd.draw(0,SCREEN_HEIGHT-TREWE_HIGHT,SSD1306_INVERSE);
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
  play();
  while(jumpped||){
    x=SCREEN_WIDTH-TREE_WIDTH;
    y=SCREEN_HIGHT-TREE_HIGHT;
    tree();
    if(!digitalRead(BUTTON)){
      x=0;
      y=SCREEN_HEIGHT-DINO_HIGHT;
      dino();
    }
  }
}
