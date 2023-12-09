#include "PixelWrapper.h"
#include "Arduino.h"

PixelWrapper::PixelWrapper(Adafruit_NeoPixel& adafruit_NeoPixel) : lib(adafruit_NeoPixel) {}

void PixelWrapper::setPixelColor(int index, int r, int g, int b) {
  lib.setPixelColor(index, lib.Color(r, g, b));
}

void PixelWrapper::show() {
  lib.show();
}

void PixelWrapper::off(int ledNumber) {
  setPixelColor(ledNumber, 0, 0, 0);
}

void PixelWrapper::begin() {
  lib.begin();
}