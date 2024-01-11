#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Ball Size
const byte VRX1=A0,VRY1=A1,VRX2=A2,VRY2=A3,R=3;
byte score1,score2,ballX,ballY,x1,y1,x2,y2,lx1,lx2,ly1,ly2,delX,delY;
void setup(){
  Serial.begin(9600);
  pinMode(VRX1,INPUT);
  pinMode(VRY1,INPUT);
  pinMode(VRX2,INPUT);
  pinMode(VRY2,INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,1);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.display();
  //delay(1000);
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(1); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
}
void loop(){
  score1=score2=0;
  ballX=SCREEN_WIDTH>>1;
  display.print("move ahead");
  display.display();
  //delay(1000);
  display.clearDisplay();
  display.display();
  //while(analogRead(VRY1)<800|| analogRead(VRY2)<800);
  while(score1<3&&score2<3){
    delX=delY=0;
    x1=lx1=SCREEN_WIDTH>>2;
    x2=lx2=(SCREEN_WIDTH>>2)+(SCREEN_WIDTH>>1);
    y1=y2=ly1=ly2=SCREEN_HEIGHT>>1;
    ballY=SCREEN_HEIGHT>>1;
    display.fillCircle(x1,y1,R,1);
    display.fillCircle(x2,y2,R,1);
    display.fillCircle(ballX,ballY,R,1);
    while(ballX>=R&&ballX<=SCREEN_WIDTH-R||ballY<=18||ballY>46){  // Ball in the area
      area();
      display.display();
      x1=analogRead(VRX1)*64.0/1023;  // Locate Joystick 1
      y1=analogRead(VRY1)*64.0/1023;
      if(byte(lx1)!=byte(x1)||byte(ly1)!=byte(y1)){
        display.fillCircle(lx1,ly1,R,0);
        area();
        display.fillCircle(x1,y1,R,1);
        display.display();
        lx1=x1;
        ly1=y1;
      }
      x2=analogRead(VRX2)*64.0/1023+64;  // Locate Joystick 2
      y2=analogRead(VRY2)*64.0/1023;
      if(byte(lx2)!=byte(x2)||byte(ly2)!=byte(y2)){
        display.fillCircle(lx2,ly2,R,0);
        area();
        display.fillCircle(x2,y2,R,1);
        display.display();
        lx2=x2;
        ly2=y2;
      }
      if((ballX-x1)<=(R<<1)&&abs(ballY-y1)<=(R<<1)){  // PlayeR 1 touch the ball
        delX=(ballX-x1)/R>>1;
        delY=(ballY-y1)/R>>1;
      }
      if(abs(ballX-x2)<=(R<<1)&&abs(ballY-y2)<=(R<<1)){  // PlayeR 2 touch the ball
        delX=(ballX-x2)/R>>1;
        delY=(ballY-y2)/R>>1;
      }
      if(delX||delY){  // Ball move
        display.fillCircle(ballX,ballY,R,0);
        ballX+=delX;
        ballY+=delY;
        display.fillCircle(ballX,ballY,R,1);
      display.display();
      }
      if(ballX<R)delX=abs(delX);  // Ball touch the left, delX always positive
      if(ballX>SCREEN_WIDTH-R)delX=-abs(delX);  // Ball touch the Right, delX always negative
      if(ballY<R)delY=abs(delY);  // Ball touch the up, delY always positive
      if(ballY>SCREEN_HEIGHT-R)delY=-abs(delY);  // Ball touch the down, delY always negative
      display.display();
    }
    byte side=80;
    ballX=SCREEN_WIDTH>>1;
    if(ballX<80){  // PlayeR 1 score
      score1++;
      ballX-=SCREEN_WIDTH>>3;
    }
    else{  // PlayeR 2 score
      score2++;
      ballX+=SCREEN_WIDTH>>3;
      side=0;
    }
    // ScoRe animation
    /*for(int i=0;i<2;i++){
      //display.fillRect(side,25,80,80,1);
      display.setCursor(30,60);
      display.println(score2);
      display.setCursor(30,60);
      display.println(score1);
      delay(500);
      //display.fillRect(side,25,80,80,1);
      area();
      display.setCursor(30,60);
      display.println(score2);
      display.setCursor(30,60);
      display.println(score1);
      delay(500);
    }*/
  }

  // Game end animation
  display.fillScreen(BLACK);
  byte winneR=2;
  if(score1>2)winneR = 1;
  display.setTextSize(2);
  display.setCursor(10,40);
  display.setTextColor(1);
  display.print("playeR");
  display.print(winneR);
  display.print(" Win");
  for (int i=1;i<26;i++){
    display.fillRect(0, 105-i,160,i,1);
  }
  delay(2000);
}

// DRaw the area
void area() {
  display.drawLine(0,20,0,44,1);    // Goal 1
  display.drawLine(127,20,127,44,1);  // Goal 2
  display.drawLine(64,0,64,29,1);   // CenteR line
  display.drawLine(64,35,64,64,1);    // CenteR line
  display.drawCircle(64,32,R,1);     // CenteR ciRcle
}
