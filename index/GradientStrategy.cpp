#include "GradientStrategy.h"
#include "Arduino.h"

GradientStrategy::GradientStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS])
    : pixelWrapper(pixelWrapper) {
      for (int i = 0; i < NUMPIXELS; ++i) {
        this->leds[i] = leds[i];
      }
    }

bool GradientStrategy::isSetuped() {
  return isSetupDone;
}

void GradientStrategy::off() {
  if (isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i]->update(0, 0, 0, 0);
      leds[i]->setColor(false);
    }
    pixelWrapper.show();
    isSetupDone = false;
  }
}

void GradientStrategy::setup() {
  long now = millis();
  generateGradientColor(step);
  for (int i = 0; i < NUMPIXELS; i++) {
    leds[i]->update(rd, gr, bl, now);  // 255 230 150
  }
  isSetupDone = true;
}

void GradientStrategy::loop() {
  if (!isSetuped()) {
    setup();
  }
  int now = millis();
  generateGradientColor(step);
  bool needToChangeColor = leds[0]->checkTime(now);
  if (needToChangeColor) {
    // Setting timerange only for the first one
    leds[0]->update(rd, gr, bl, now + GRADIENTDELAY);
    leds[0]->setColor(false);
    for (int i = 1; i < NUMPIXELS; i++) {
      leds[i]->update(rd, gr, bl, 0);
      leds[i]->setColor(false);
    }
    step += 0.0025;
    if (step >= 1.00) step = 0.0025;
    pixelWrapper.show();
  }
}

void GradientStrategy::generateGradientColor(float position) {
  const uint8_t gradient[][3] = {
    { 255, 0, 0 },    // Red
    { 255, 255, 0 },  // Yellow
    { 0, 255, 0 },    // Green
    { 0, 0, 255 },    // Blue
    { 255, 0, 255 },  // Magenta
    { 255, 0, 0 }
  };
  int numColors = sizeof(gradient) / sizeof(gradient[0]);
  if (position < 0.0) {
    position = 0.0;
  } else if (position > 1.0) {
    position = 1.0;
  }
  float index = position * (numColors - 1);
  int lowerIndex = floor(index);
  int upperIndex = ceil(index);
  float interpolation = index - lowerIndex;

  uint8_t lowerR = gradient[lowerIndex][0];
  uint8_t lowerG = gradient[lowerIndex][1];
  uint8_t lowerB = gradient[lowerIndex][2];

  uint8_t upperR = gradient[upperIndex][0];
  uint8_t upperG = gradient[upperIndex][1];
  uint8_t upperB = gradient[upperIndex][2];

  rd = lowerR + interpolation * (upperR - lowerR);
  gr = lowerG + interpolation * (upperG - lowerG);
  bl = lowerB + interpolation * (upperB - lowerB);
}