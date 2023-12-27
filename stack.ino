#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte BUTTON=2

void setup(){
  pinMode(BUTTON,INPUT_PULLUP);
display.begin(SSD1306_SWITCHCAPVCC,0x3C);display.clearDisplay();
}
void loop(){

  display.setTextSize(2);          // 設定文字大小
  display.setTextColor(1);         // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(5,0);          // 設定起始座標
  display.print("Hello OLED");     // 要顯示的字串
  display.setCursor(26,40);        // 設定起始座標
  display.print("MiroTek");        // 要顯示的字串
  display.display();               // 要有這行才會把文字顯示出來
  delay(1000);
}
