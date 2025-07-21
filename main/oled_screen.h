#include <SPI.h>
#ifndef OledScreen_h
#define OledScreen_h


class OledScreen {
  
  public:
    String txt_one;
    String txt_two;
    OledScreen();
    ~OledScreen();
  
  void setupOledScreen();

  void printSimpleText(String txt_one, String txt_two);
  void centerText(String txt_one, String txt_two);
  void centerTextRegistry(String txt_one, String txt_two, String txt_three);

  void printOledIconWiFiConfig();
  void printOledIconWiFiConfigDone();
  void printOledIconFingerValid();
  void printOledIconFingerFail();
  void printOledIconNoFingerDetected();
};
#endif