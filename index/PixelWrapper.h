#ifndef PIXEL_WRAPPER_H
#define PIXEL_WRAPPER_H

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class PixelWrapper {
public:
  PixelWrapper(Adafruit_NeoPixel& adafruit_NeoPixel);

  void setPixelColor(int index, int r, int g, int b);

  void show();

  void off(int ledNumber);

  void begin();

private:
  Adafruit_NeoPixel& lib;
};

#endif