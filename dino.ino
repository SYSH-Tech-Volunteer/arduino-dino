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
      if(DINO[i][j])ssd.draw(1);
      else ssd.draw(0);
    }
  }
}
void setup(){
  pinMode(BUTTON,INPUT_PULLUP);
}
void loop(){
  dino(0,0);
  if(!digitalRead(BUTTON))dino
}
