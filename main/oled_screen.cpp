#include "oled_screen.h"
#include "icons.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <Adafruit_I2CDevice.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OledScreen::OledScreen(){}
OledScreen::~OledScreen(){}

void OledScreen::setupOledScreen(){
    
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
}

void OledScreen::printSimpleText( String txt_one, String txt_two ){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 2:2 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(1,0);             // Start at top-left corner
  display.print(txt_one);
  display.setCursor(0,20);
  display.print(txt_two);
  display.display();      
}

void OledScreen::centerText( String txt_one, String txt_two ){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 2:2 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(10,16);             // Start at top-left corner
  display.print(txt_one);
  display.setCursor(10,36);
  display.print(txt_two);
  display.display();      
}

void OledScreen::centerTextRegistry( String txt_one, String txt_two , String txt_three){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 2:2 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(10,0);             // Start at top-left corner
  display.print(txt_one);
  display.setCursor(10,16);
  display.print(txt_two);
  display.setCursor(10,36);
  display.print(txt_three);
  display.display();      
}

void OledScreen::printOledIconWiFiConfig(){
  this->setupOledScreen();
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(8, 0);             // Start at top-left corner
    display.print(F("Conectando  \n"));
    display.drawBitmap( 33, 15, Wifi_connected_bits, Wifi_connected_width, Wifi_connected_height, WHITE);
    display.display();
}

void OledScreen::printOledIconWiFiConfigDone(){
  this->setupOledScreen();
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(8, 0);             // Start at top-left corner
    display.print(F("Conectado \n"));
    display.drawBitmap( 33, 15, Wifi_connected_bits, Wifi_connected_width, Wifi_connected_height, WHITE);
    display.display();
}

void OledScreen::printOledIconFingerValid(){
  this->setupOledScreen();
  display.clearDisplay();
  display.drawBitmap( 34, 0, FinPr_valid_bits, FinPr_valid_width, FinPr_valid_height, WHITE);
  display.display();
}

void OledScreen::printOledIconFingerFail(){
  this->setupOledScreen();
  display.clearDisplay();
  display.drawBitmap( 32, 0, FinPr_failed_bits, FinPr_failed_width, FinPr_failed_height, WHITE);
  display.display();
}

void OledScreen::printOledIconNoFingerDetected(){
  this->setupOledScreen();
  display.clearDisplay();
  display.drawBitmap( 32, 0, FinPr_start_bits, FinPr_start_width, FinPr_start_height, WHITE);
  display.display();
}