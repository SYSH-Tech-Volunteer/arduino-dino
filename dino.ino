#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON=2,DINO_HEIGHT=2,DINO_WIDTH=2,TREE_HEIGHT=2,TREE_WIDTH=2,PLAY_HEIGHT=2,PLAY_WIDTH=2,JUMP_MOVE=2;
bool DINO[2][2]={
    {1,1},
    {1,1}
  };
bool  TREE[2][2]={
    {1,1},
    {1,1}
  };
bool  PLAY[2][2]={
    {1,1},
    {1,1}
  };
bool jump,pressed;
byte i,j,x,y,treeX,jumpMove;
void dino(){
  for(i=0;i<DINO_HEIGHT;i++){
    for(j=0;j<DINO_WIDTH;j++){
      display.drawPixel(x+j,y+i,(DINO[i][j]?SSD1306_WHITE:SSD1306_INVERSE));
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
  x=(SCREEN_WIDTH-PLAY_WIDTH)/+2;
  y=(SCREEN_HEIGHT-PLAY_HEIGHT)/+2;
  for(i=0;i<PLAY_HEIGHT;i++){
    for(j=0;j<PLAY_WIDTH;j++){
      display.drawPixel(x+j,y+i,(PLAY[i][j]?SSD1306_WHITE:SSD1306_INVERSE));
    }
  }
  jump=0;
  pressed=0;
  treeX=SCREEN_WIDTH-TREE_WIDTH;
  jumpMove=0;
  while(digitalRead(BUTTON));
  x=(SCREEN_WIDTH-PLAY_WIDTH)/+2;
  y=(SCREEN_HEIGHT-PLAY_HEIGHT)/+2;
  display.fillRect(x,y,PLAY_WIDTH,PLAY_HEIGHT,SSD1306_INVERSE);
  x=0;
  y=SCREEN_HEIGHT-DINO_HEIGHT;
  dino();
  display.display();
  while(jump||treeX>DINO_WIDTH){
    for(i=0;i<TREE_HEIGHT;i++){
      for(j=0;j<TREE_WIDTH;j++){
        display.drawPixel(treeX+j,SCREEN_HEIGHT-TREE_HEIGHT+i,(TREE[i][j]?SSD1306_WHITE:SSD1306_INVERSE));
      }
    }
    if(!digitalRead(BUTTON)&&!jump&&!pressed){
      jump=pressed=1;
      display.fillRect(0,SCREEN_HEIGHT-DINO_HEIGHT,DINO_WIDTH,DINO_HEIGHT,SSD1306_INVERSE);
      y=SCREEN_HEIGHT-DINO_HEIGHT-TREE_HEIGHT;
      dino();
      display.display();
    }
    if(jumpMove>=JUMP_MOVE){
      jump=0;
      jumpMove=0;
      display.fillRect(0,SCREEN_HEIGHT-DINO_HEIGHT-TREE_HEIGHT,DINO_WIDTH,DINO_HEIGHT,SSD1306_INVERSE);
      y=SCREEN_HEIGHT-DINO_HEIGHT;
      dino();
      display.display();
    }
    if(digitalRead(BUTTON))pressed=0;
    display.fillRect(treeX,SCREEN_HEIGHT-TREE_HEIGHT,TREE_WIDTH,TREE_HEIGHT,SSD1306_INVERSE);
    display.display();
    if(treeX)treeX--;
    else treeX=SCREEN_WIDTH-TREE_WIDTH;
    if(jump)jumpMove++;
  }
}
