#ifndef LED_H
#define LED_H

#include "Arduino.h"

#include "RGB.h"
#include "PixelWrapper.h"

class Led {
public:
  Led(int ledNumber, long executeAt, RGB color, PixelWrapper& pixelLib);

  void setColor(bool needToShow);
  void update(int r, int g, int b, long time);
  long getTime();
  void show();
  bool isOff();
  RGB getColor();
  bool checkTime(long now);

private:
  RGB color;
  PixelWrapper& pixelLib;
  int ledNumber;
  long executeAt;
};

#endif