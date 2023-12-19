#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON,DINO_HIGHT,DINO_WIDTH,TREE_HIGHT,TREE_WIDTH,PLAY_HIGHT,PLAY_WIDTH,JUMP_MOVE;
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
bool jump,pressed;
byte i,j,x,jumpMove;
void dino(){
  for(i=0;i<HIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(DINO[i][j])display.drawPixel(x+i,y+j,SSD1306_WHITE);
      else ssd.draw(0,SCREEN_HEIGHT-DINO_HIGHT,SSD1306_INVERSE);
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
  for(i=0;i<HIGHT;i++){
    for(j=0;j<WIDTH;j++){
      display.drawPixel(x+j,SCREEN_HIGHT-TREE_HIGHT+i,(TREE[i][j]?SSD1306_WHITE:SSD1306_INVERSE));
    }
  }
  jump=0;
  pressed=0;
  x=SCREEN_WIDTH-TREE_WIDTH;
  jumpMove=0;
  while(jump||x>DINO_WIDTH){
    for(i=0;i<HIGHT;i++){
      for(j=0;j<WIDTH;j++){
        display.drawPixel(x+j,SCREEN_HIGHT-TREE_HIGHT+i,(TREE[i][j]?SSD1306_WHITE:SSD1306_INVERSE));
      }
    }
    if(!digitalRead(BUTTON)&&!jump&&!pressed){
      jump=pressed=1;
      display.fillRect(0,SCREEN_HIGHT-DINO_HIGHT,DINO_WIDTH,DINO_HIGHT,SSD1306_INVERSE);
      dino();
      display.display();
    }
    if(jumpMove>=JUMP_MOVE){
      jump=0;
      jumpMove=0;
      display.fillRect(0,SCREEN_HIGHT-DINO_HIGHT-TREE_HIGHT,DINO_WIDTH,DINO_HIGHT,SSD1306_INVERSE);
      dino();
      display.display();
    }
    if(digitalRead(BUTTON))pressed=0;
    display.fillRect(x,SCREEN_HIGHT-TREE_HIGHT,TREE_WIDTH,TREE_HIGHT,SSD1306_INVERSE);
    display.display();
    x--;
    if(jump)jumpMove++;
  }
}
