#include "Led.h"
#include "Arduino.h"

Led::Led(int ledNumber, long executeAt, RGB color, PixelWrapper& pixelLib)
    : ledNumber(ledNumber), executeAt(executeAt), color(color), pixelLib(pixelLib) {}

void Led::setColor(bool needToShow) {
  pixelLib.setPixelColor(ledNumber, color.getRed(), color.getGreen(), color.getBlue());
  if (needToShow) show();
}

void Led::update(int r, int g, int b, long time) {
  color = RGB(r, g, b);
  executeAt = time;
}

long Led::getTime() {
  return executeAt;
}

void Led::show() {
  pixelLib.show();
}

bool Led::isOff() {
  return color.getRed() == 0 && color.getGreen() == 0 && color.getBlue() == 0;
}

RGB Led::getColor() {
  return color;
}

bool Led::checkTime(long now) {
  return now >= executeAt;
}
