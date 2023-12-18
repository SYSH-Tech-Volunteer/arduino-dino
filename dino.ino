#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON,DINO_HIGHT,DINO_WIDTH,TREE_HIGHT,TREE_WIDTH,JUMP_MOVE;
const bool 
  DINO[HIGHT][WIDTH]={
    {},{}
  },
  TREE[][]={
    {},{}
  },
  PLAY[][]={
    {},{}
  };
bool jump,jumpped;
byte i,j,x,y,treeMove,treeX;
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
  jumpped=0;
  treeX=SCREEN_WIDTH-TREE_WIDTH;
  treeY=SCREEN_HIGHT-TREE_HIGHT;
  while(jump||x>DINO_WIDTH){
    tree();
    if(!digitalRead(BUTTON)&&!jump&&!jumpped){
      jump=1;
      treeMove=0;
      display.fillRect(0,SCREEN_HIGHT-DINO_HIGHT,DINO_WIDTH,DINO_HIGHT,SSD1306_INVERSE);
      dino();
      display.display();
    }
    if(treeMove>=JUMP_MOVE){
      jumpped=0;
      jump=0;
      display.fillRect(0,SCREEN_HIGHT-DINO_HIGHT-TREE_HIGHT,DINO_WIDTH,DINO_HIGHT,SSD1306_INVERSE);
      dino();
      display.display();
    }
    display.fillRect(treeX,SCREEN_HIGHT-TREE_HIGHT,TREE_WIDTH,TREE_HIGHT,SSD1306_INVERSE);
    display.display();
    treeMove++;
  }
}
