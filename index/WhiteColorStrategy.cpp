#include "WhiteColorStrategy.h"
#include "Arduino.h"

WhiteColorStrategy::WhiteColorStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS])
    : pixelWrapper(pixelWrapper) {
      for (int i = 0; i < NUMPIXELS; ++i) {
        this->leds[i] = leds[i];
      }
    }

bool WhiteColorStrategy::isSetuped() {
    return isSetupDone;
  }

void WhiteColorStrategy::off() {
  if (isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i]->update(0, 0, 0, 0);
      leds[i]->setColor(false);
    }
    pixelWrapper.show();
    isSetupDone = false;
    isOn = false;
  }
}

void WhiteColorStrategy::setup() {
  long now = millis();
  for (int i = 0; i < NUMPIXELS; i++) {
    leds[i]->update(255, 230, 150, now);  // 255 230 150
  }
  isSetupDone = true;
}

void WhiteColorStrategy::loop() {
  if (!isSetuped()) {
    setup();
  }
  if (!isOn) {
    int now = millis();
    for (int i = 0; i < NUMPIXELS; i++) {
      bool needToChangeColor = leds[i]->checkTime(now);
      if (needToChangeColor) {
        leds[i]->setColor(false);
      }
    }
    pixelWrapper.show();
    isOn = true;
  }
}
