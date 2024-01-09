#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte BUTTON=2,HEIGHT=2;
bool right;
byte x,width,leftX,rightX,y;
void setup(){
  pinMode(BUTTON,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
}
void loop(){
  display.clearDisplay();
  right=1;
  x=0;
  width=32;
  display.fillRect(0,SCREEN_HEIGHT-HEIGHT,width,HEIGHT,1);
  display.display();
  while(!digitalRead(BUTTON)){
    if(right){
      display.drawLine(x,SCREEN_HEIGHT,x,SCREEN_HEIGHT-HEIGHT,0);
      display.drawLine(x+width,SCREEN_HEIGHT,x+width,SCREEN_HEIGHT-HEIGHT,1);
      display.display();
    }
    else{
      display.drawLine(x+width,SCREEN_HEIGHT,x+width,SCREEN_HEIGHT-HEIGHT,0);
      display.drawLine(x,SCREEN_HEIGHT,x,SCREEN_HEIGHT-HEIGHT,1);
      display.display();
    }
    if(right)x++;
    else x--;
    if(x+width>=SCREEN_WIDTH)right=0;
    if(x<=0)right=1;
  }
  leftX=x;
  rightX=x+width;
  y=SCREEN_HEIGHT-(HEIGHT<<1);
  right=1;
  x=random(0,SCREEN_WIDTH-width);
  while(digitalRead(BUTTON));
  do{
    x=random(0,SCREEN_WIDTH-width);
    display.fillRect(x,y,width,HEIGHT,1);
    display.display();
    while(!digitalRead(BUTTON)){
      if(right){
        display.drawLine(x,y+HEIGHT-1,x,y,0);
        display.drawLine(x+width,y+HEIGHT-1,x+width,y,1);
        display.display();
      }
      else{
        display.drawLine(x+width,y+HEIGHT-1,x+width,y+HEIGHT-2,0);
        display.drawLine(x,y+HEIGHT-1,x,y+HEIGHT-2,1);
        display.display();
      }
      if(right)x++;
      else x--;
      if(x+width>=SCREEN_WIDTH)right=0;
      if(x<=0)right=1;
    }
    while(digitalRead(BUTTON));
    leftX=max(leftX,x);
    rightX=min(rightX,x+width);
    width=rightX-leftX;
    display.drawRect(0,y,leftX,HEIGHT,0);
    display.drawRect(rightX,y,SCREEN_WIDTH-rightX,HEIGHT,0);
    y-=HEIGHT;
  }while((x>=leftX&&x<=rightX)||(x+width>=leftX&&x+width<=rightX));
  while(!digitalRead(BUTTON));
  while(digitalRead(BUTTON));
}
