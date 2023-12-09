#include "RainbowStrategy.h"

RainbowStrategy::RainbowStrategy(PixelWrapper& pixelWrapper): pixelWrapper(pixelWrapper) {}

bool RainbowStrategy::isSetuped() {
  return this->isOn;
}

void RainbowStrategy::off() {
  if (this->isOn) {
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->update(0, 0, 0, 0);
      this->leds[i]->setColor(false);
    }
    this->pixelWrapper.show();
    this->isOn = false;
  }
}

void RainbowStrategy::setup() {
  if(!this->isOn) {
    unix delay = RAINBOWDELAY;
    unix now = getTime();
    for (int i = 0; i < NUMPIXELS; i++) {
      this->generateColor(i);
      this->leds[i]->update(this->rd, this->gr, this->bl, now + delay);
      delay += RAINBOWDELAY;
    }
    this->isOn = true;
  }
}

void RainbowStrategy::loop() {
  if(this->isOn) {
    unix now = getTime();
    for (int i = 0; i < NUMPIXELS; i++) {
      bool needToChangeColor = this->leds[i]->checkTime(now);
      if (needToChangeColor) {
        this->leds[i]->setColor(true);
        if (this->leds[i]->isOff()) {
          this->generateColor(i);
          this->leds[i]->update(this->rd, this->gr, this->bl, now + RAINBOWDELAY * (NUMPIXELS - 1));
        } else {
          this->leds[i]->update(0, 0, 0, now + RAINBOWDELAY * (NUMPIXELS - 1));
        }
      }
    }
  }
}
void RainbowStrategy::generateColor(int ledNumber) {
  // Створення кольорового градієнту від червоного до синього
  if (ledNumber < 10) {
    this->rd = 255;
    this->gr = map(ledNumber, 0, 10, 0, 255);
    this->bl = 0;
  } else if (ledNumber < 20) {
    this->rd = map(ledNumber, 10, 20, 255, 0);
    this->gr = 255;
    this->bl = 0;
  } else if (ledNumber < 30) {
    this->rd = 0;
    this->gr = 255;
    this->bl = map(ledNumber, 20, 30, 0, 255);
  } else if (ledNumber < 40) {
    this->rd = 0;
    this->gr = map(ledNumber, 30, 40, 255, 0);
    this->bl = 255;
  } else if (ledNumber < 50) {
    this->rd = map(ledNumber, 40, 50, 0, 255);
    this->gr = 0;
    this->bl = 255;
  } else {
    this->rd = 255;
    this->gr = 0;
    this->bl = map(ledNumber, 50, 60, 255, 0);
  }
}


void RainbowStrategy::setLeds(Led* ledsArr[NUMPIXELS]) {
  for (int i = 0; i < NUMPIXELS; i++) {
    this->leds[i] = ledsArr[i];
  }
}
