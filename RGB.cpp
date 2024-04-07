#include "RGB.h"

RGB::RGB(int red, int green, int blue): red(red), green(green), blue(blue) {}

int RGB::getRed() {
  return this->red;
}
int RGB::getGreen() {
  return this->green;
}
int RGB::getBlue() {
  return this->blue;
}
