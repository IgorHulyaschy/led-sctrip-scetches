#include "RGB.h"
#include "Arduino.h"

RGB::RGB(int red, int green, int blue): red(red), green(green), blue(blue) {}

int RGB::getRed() {
  return red;
}
int RGB::getGreen() {
  return green;
}
int RGB::getBlue() {
  return blue;
}
