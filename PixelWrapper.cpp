#include "PixelWrapper.h"

PixelWrapper::PixelWrapper(Adafruit_NeoPixel& adafruit_NeoPixel) : lib(adafruit_NeoPixel) {}

void PixelWrapper::setPixelColor(int index, int r, int g, int b) {
  this->lib.setPixelColor(index, this->lib.Color(r, g, b));
}

void PixelWrapper::show() {
  this->lib.show();
}

void PixelWrapper::off(int ledNumber) {
  this->lib.setPixelColor(ledNumber, 0, 0, 0);
}

void PixelWrapper::begin() {
  this->lib.begin();
}