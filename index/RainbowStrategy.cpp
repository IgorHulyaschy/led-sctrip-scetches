#include "RainbowStrategy.h"
#include "Arduino.h"

RainbowStrategy::RainbowStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS])
    : pixelWrapper(pixelWrapper) {
      for (int i = 0; i < NUMPIXELS; ++i) {
        this->leds[i] = leds[i];
      }
    }

bool RainbowStrategy::isSetuped() {
  return isSetupDone;
}

void RainbowStrategy::off() {
  if (isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i]->update(0, 0, 0, 0);
      leds[i]->setColor(false);
    }
    pixelWrapper.show();
    isSetupDone = false;
  }
}

void RainbowStrategy::setup() {
  int delay = RAINBOWDELAY;
  long now = millis();
  for (int i = 0; i < NUMPIXELS; i++) {
    generateColor(i);
    leds[i]->update(rd, gr, bl, now + delay);
    delay += RAINBOWDELAY;
  }
  isOff = false;
  isSetupDone = true;
}

void RainbowStrategy::loop() {
  if (!isSetuped()) {
    setup();
  }
  int now = millis();
  for (int i = 0; i < NUMPIXELS; i++) {
    bool needToChangeColor = leds[i]->checkTime(now);
    if (needToChangeColor) {
      leds[i]->setColor(true);
      if (leds[i]->isOff()) {
        generateColor(i);
        leds[i]->update(rd, gr, bl, leds[i]->getTime() + RAINBOWDELAY * (NUMPIXELS - 1));
      } else {
        leds[i]->update(0, 0, 0, leds[i]->getTime() + RAINBOWDELAY * (NUMPIXELS - 1));
      }
    }
  }
}
void RainbowStrategy::generateColor(int ledNumber) {
  // Створення кольорового градієнту від червоного до синього
  if (ledNumber < 10) {
    rd = 255;
    gr = map(ledNumber, 0, 10, 0, 255);
    bl = 0;
  } else if (ledNumber < 20) {
    rd = map(ledNumber, 10, 20, 255, 0);
    gr = 255;
    bl = 0;
  } else if (ledNumber < 30) {
    rd = 0;
    gr = 255;
    bl = map(ledNumber, 20, 30, 0, 255);
  } else if (ledNumber < 40) {
    rd = 0;
    gr = map(ledNumber, 30, 40, 255, 0);
    bl = 255;
  } else if (ledNumber < 50) {
    rd = map(ledNumber, 40, 50, 0, 255);
    gr = 0;
    bl = 255;
  } else {
    rd = 255;
    gr = 0;
    bl = map(ledNumber, 50, 60, 255, 0);
  }
}
