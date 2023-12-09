#include "WhiteColorStrategy.h"

WhiteColorStrategy::WhiteColorStrategy(PixelWrapper& pixelWrapper): pixelWrapper(pixelWrapper) {}

bool WhiteColorStrategy::isSetuped() {
    return this->isSetupDone;
  }

void WhiteColorStrategy::off() {
  if (this->isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->update(0, 0, 0, 0);
      this->leds[i]->setColor(false);
    }
    this->pixelWrapper.show();
    this->isSetupDone = false;
  }
}

void WhiteColorStrategy::setup() {
  if(!this->isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->update(255, 230, 150, 0);  // 255 230 150
    }
    this->isSetupDone = true;
  }
}

void WhiteColorStrategy::loop() {
  unix now = getTime();
  bool needToChangeColor = this->leds[0]->checkTime(now);
  if(needToChangeColor) {
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->setColor(false);
    }
    this->pixelWrapper.show();
  }
}

void WhiteColorStrategy::setLeds(Led* ledsArr[NUMPIXELS]) {
  for (int i = 0; i < NUMPIXELS; i++) {
    this->leds[i] = ledsArr[i];
  }
}
