#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const byte JOYSTICK=2,HEIGHT=2;
bool right;
byte x,width,leftX,rightX,y,lv;
void setup(){
  pinMode(JOYSTICK,INPUT_PULLUP);
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
  lv=1;
  display.fillRect(0,SCREEN_HEIGHT-HEIGHT,width,HEIGHT,1);//畫長方形
  display.display();
  while(analogRead(JOYSTICK)>300){//偵測搖桿
    if(right){
      display.drawLine(x,SCREEN_HEIGHT,x,SCREEN_HEIGHT-HEIGHT,0);
      display.drawLine(x+width,SCREEN_HEIGHT,x+width,SCREEN_HEIGHT-HEIGHT,1);
      display.display();
    }//往右移動
    else{
      display.drawLine(x+width,SCREEN_HEIGHT,x+width,SCREEN_HEIGHT-HEIGHT,0);
      display.drawLine(x,SCREEN_HEIGHT,x,SCREEN_HEIGHT-HEIGHT,1);
      display.display();
    }//往左移動
    if(right)x++;//座標右移
    else x--;//座標左移
    if(x+width>=SCREEN_WIDTH)right=0;
    if(x<=0)right=1;//碰到邊緣就反彈
  }//第二層開始
  leftX=x;//座標變成左邊的邊
  rightX=x+width;//座標變成右邊的邊
  y=SCREEN_HEIGHT-(HEIGHT<<1);//往上一層
  right=1;
  //第二層鬆餅
  while(analogRead(JOYSTICK)<300);
  do{
    x=random(0,SCREEN_WIDTH-width);
    display.fillRect(x,y,width,HEIGHT,1);
    display.display();
    while(analogRead(JOYSTICK)>300){
      if(right){//第二層移動
        display.drawRect(x,y,lv,HEIGHT,0);
        display.drawRect(x+width,y,lv,HEIGHT,1);
        display.display();
      }
      else{
        display.drawRect(x+width,y,lv,HEIGHT,0);
        display.drawRect(x,y,lv,HEIGHT,1);
        display.display();
      }
      if(right)x++;
      else x--;
      if(x+width>=SCREEN_WIDTH)right=0;
      if(x<=0)right=1;
    }
    while(analogRead(JOYSTICK)<300);//切鬆餅
    leftX=max(leftX,x);
    rightX=min(rightX,x+width);
    width=rightX-leftX;
    display.drawRect(0,y,leftX,HEIGHT,0);//切過的鬆餅左邊
    display.drawRect(rightX,y,SCREEN_WIDTH-rightX,HEIGHT,0);//切過的鬆餅右邊
    y-=HEIGHT;
    lv+=2;
  }while(!(x>=rightX||x+width<=leftX));
  while(analogRead(JOYSTICK)>300);
  while(analogRead(JOYSTICK)<300);
}
