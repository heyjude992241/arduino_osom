#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "Bitmap.h"
#include "RockScissorPaper.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ANALOG_PIN A3
#define BTN_PIN 8
#define MAX_SELECT 3

int analog_read;
int uno_weapon;
uint8_t mapped_read;
unsigned char screen_type;
RockScissorPaper your_weapon;

RockScissorPaper rsp[] = {
  //RockScissorPaper(uint8_t x, uint8_t y, uint8_t order)
  RockScissorPaper(10, 15, 0),
  RockScissorPaper(49, 15, 1),
  RockScissorPaper(88, 15, 2)
};

char titles[][8] = {"Rock", "Scissor", "Paper"};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    while(true){}
  }
  pinMode(BTN_PIN, INPUT);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  //drawSelectWeaponText();
  randomSeed(analogRead(0));
  screen_type = 'm';
  display.clearDisplay();
  display.drawBitmap(0, 18, wannaikedo, 128, 26, WHITE);
  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();
  // put your main code here, to run repeatedly:
  analog_read = analogRead(ANALOG_PIN);
  mapped_read = map(analog_read, 0, 1010, 0, 10);
  mapped_read = mapped_read <= (MAX_SELECT-1) ? mapped_read : (MAX_SELECT-1);

  your_weapon = rsp[mapped_read];
  switch(screen_type){
    case 'm':
      drawSelectWeaponScreen();
      break;

    case 's':
      drawRockScissorPaperScreen();
      drawBattleScreen();
      drawBattleResult();
      delay(2000);
      break;
  }
  
}

void splashScreen(){
  display.drawBitmap(0, 18, wannaikedo, 128, 26, WHITE);
}

void drawSelectWeaponScreen(){
  display.setTextSize(1);
  display.setCursor(13, 0);
  display.print("Select your weapon");
  for(int i=0; i<RockScissorPaper::MAX_RSP; i++){
    display.drawBitmap(rsp[i].getX(), rsp[i].getY(), bitmap_ori[i], 28, 28, WHITE);
  }

  display.drawRect(your_weapon.getX()-5, your_weapon.getY()-5, 38, 38, WHITE);
  display.setTextSize(2);
  display.setCursor(getTitleStartX(titles[mapped_read]), 50); 
  display.print(titles[mapped_read]);
  display.display(); 

  if(digitalRead(BTN_PIN) == HIGH){
    screen_type = 's';
  }
}

void drawRockScissorPaperScreen(){
  for(int i=0; i<3; i++){
    display.clearDisplay();
    display.display();
    delay(100);
    display.setCursor(getTitleStartX(titles[i])-15, 25);
    display.print(titles[i]);
    display.print("!!");
    display.display();
    delay(300);
  }  
}

void drawBattleScreen(){
  uno_weapon = random(0, 3);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(24, 10);
  display.print("You");
  display.setCursor(80, 10);
  display.print("Uno");
  //display.drawLine(63, 19, 63, 107, WHITE);
  display.drawBitmap(16, 30, bitmap_ori[your_weapon.getOrder()],28, 28, WHITE);
  display.drawBitmap(80, 30, bitmap_flip[uno_weapon], 28, 28, WHITE);
  display.display();
  delay(3000);
}

void drawBattleResult(){
  display.clearDisplay();
  display.setTextSize(2);
  switch(your_weapon.getBattleResult(uno_weapon)){
    case 0: //lose
    display.setCursor(20, 0);
    display.print(F("Uno win"));
    display.drawBitmap(48, 24, battle_face[0], 32, 32, WHITE);
    break;

    case 1: //win
    display.setCursor(15, 0);
    display.print(F("You win!!"));
    display.drawBitmap(48, 24, battle_face[1], 32, 32, WHITE);
    break;

    case 2:
    display.setCursor(44, 25);
    display.print(F("Draw"));
    break;
  }
  display.display();
  delay(2000);
  screen_type = 'm';
}

uint8_t getTitleStartX(char* title){
  uint8_t elem_length = 0;
  while(*(title+elem_length) != '\0'){
    ++elem_length;
  }
  //Serial.print("Elemen length: ");
  //Serial.println(elem_length);
  return (SCREEN_WIDTH-(elem_length*10))/2;
}

void drawSelectWeaponText(){
  for(int i=0; i<3; i++){
    display.setCursor(0, 0);
    display.clearDisplay();
    display.display();
    delay(200);
    display.print("Select your weapon");
    display.display();
    delay(800);
  }
}
