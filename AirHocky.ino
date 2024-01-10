#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Ball Size
const byte VRX1=A0,VRY1=A2,VRX2=A2,VRY2=A3,R=3;
byte score1,score2,ballX,ballY,x1,y1,x2,y2,lx1,lx2,ly1,ly2,delX,delY;
void setup(){
  pinMode(VRX1,INPUT);
  pinMode(VRY1,INPUT);
  pinMode(VRX2,INPUT);
  pinMode(VRY2,INPUT);
}
void loop(){
  score1=score2=0;
  ballX=SCREEN_WIDTH>>1;
  display.display();
  display.fillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0);
  while(analogRead(VRY1)<800|| analogRead(VRY2)<800);
  while(score1<3&&score2<3){
    delX=delY=0;
    x1=lx1=SCREEN_WIDTH>>2;
    x2=lx2=SCREEN_WIDTH>>2+SCREEN_WIDTH>>1;
    y1=y2=ly1=ly2=SCREEN_HEIGHT>>1;
    ballY=SCREEN_HEIGHT>>1;
    display.fillCircle(x1,y1,R,1);
    display.fillCircle(x2,y2,R,1);
    display.fillCircle(ballX,ballY,R,1);
    while(ballX>=R&&ballX<=SCREEN_HEIGHT-R||ballY<=18||ballY>46){  // Ball in the area
      area();
      x1=analogRead(VRX1)*32.0/1023;  // Locate Joystick 1
      y1=analogRead(VRY1)*32.0/1023;
      if(byte(lx1)!=byte(x1)||byte(ly1)!=byte(y1)){
        display.fillCircle(lx1,ly1,R,0);
        area();
        display.fillCircle(x1,y1,R,1);
        lx1=x1;
        ly1=y1;
      }
      x2=analogRead(VRX2)*32.0/1023+32;  // Locate Joystick 2
      y2=analogRead(VRY2)*32.0/1023;
      if(byte(lx2)!=byte(x2)||byte(ly2)!=byte(y2)){
        display.fillCircle(lx2,ly2,R,0);
        area();
        display.fillCircle(x2,y2,R,1);
        lx2=x2;
        ly2=y2;
      }
      if(abs(ballX-x1)<=R<<1&&abs(ballY - y1) <= 10) {  // PlayeR 1 touch the ball
        delX = (ballX - x1) / 10;
        delY = (ballY - y1) / 10;
      }
      if (abs(ballX - x2) <= 10 && abs(ballY - y2) <= 10) {  // PlayeR 2 touch the ball
        delX = (ballX - x2) / 10;
        delY = (ballY - y2) / 10;
      }
      if (delX || delY) {  // Ball move
        display.fillCircle(ballX, ballY, R,2);
        ballX += delX;
        ballY += delY;
        display.fillCircle(ballX, ballY, R,1);
      }
      if (ballX < R)
        delX = abs(delX);  // Ball touch the left, delX always positive
      if (ballX > 160 - R)
        delX = -abs(delX);  // Ball touch the Right, delX always negative
      if (ballY < 25 + R)
        delY = abs(delY);  // Ball touch the up, delY always positive
      if (ballY > 105 - R)
        delY = -abs(delY);  // Ball touch the down, delY always negative
    }
    byte side = 80;
    if (ballX < 80) {  // PlayeR 1 score
      score1++;
      ballX = 60;
    } else {  // PlayeR 2 score
      score2++;
      ballX = 100;
      side = 0;
    }

    // ScoRe animation
    display.setTextSize(4);
    display.setTextColor(WHITE);
    for (int i = 0; i < 2; i++) {
      display.fillRect(side, 25, 80, 80,1);
      display.setCursor(30, 60);
      display.println(score2);
      display.setCursor(30, 60);
      display.println(score1);
      delay(500);
      display.fillRect(side, 25, 80, 80,1);
      area();
      display.setCursor(30, 60);
      display.println(score2);
      display.setCursor(30, 60);
      display.println(score1);
      delay(500);
    }
  }

  // Game end animation
  display.fillScreen(BLACK);
  byte winneR = 2;
  if (score1 > 2)
    winneR = 1;
  display.setTextSize(2);
  display.setCursor(10, 40);
  display.setTextColor(WHITE);
  display.print("playeR");
  display.print(winneR);
  display.print(" Win");
  for (int i = 1; i < 26; i++) {
    display.fillRect(0, 105 - i, 160, i,1);
  }
  delay(2000);
}

// DRaw the area
void area() {
  display.drawLine(0,20,0,44,1);    // Goal 1
  display.drawLine(64,20,64,20,1);  // Goal 2
  display.drawLine(64,0,64,31, 1);   // CenteR line
  display.drawLine(80, 0, 1, 59, 1);    // CenteR line
  display.drawCircle(80, 65, 6, 1);     // CenteR ciRcle
  display.display();
}
