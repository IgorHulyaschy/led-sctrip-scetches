#include "GradientStrategy.h"

GradientStrategy::GradientStrategy(PixelWrapper& pixelWrapper): pixelWrapper(pixelWrapper) {}

bool GradientStrategy::isSetuped() {
  return this->isSetupDone;
}

void GradientStrategy::off() {
  if (this->isSetupDone) {
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->update(0, 0, 0, 0);
      this->leds[i]->setColor(false);
    }
    this->pixelWrapper.show();
    this->isSetupDone = false;
  }
}

void GradientStrategy::setup() {
  if(!this->isSetupDone)  {
    unix now = getTime();
    generateGradientColor(this->step);
    for (int i = 0; i < NUMPIXELS; i++) {
      this->leds[i]->update(this->rd, this->gr, this->bl, now);  // 255 230 150
    }
    this->isSetupDone = true;
  }
}

void GradientStrategy::loop() {
  if(this->isSetupDone) {
    unix now = getTime();
    generateGradientColor(this->step);
    bool needToChangeColor = this->leds[0]->checkTime(now);
    if (needToChangeColor) {
      // Setting timerange only for the first one
      this->leds[0]->update(this->rd, this->gr, this->bl, now + GRADIENTDELAY);
      this->leds[0]->setColor(false);
      for (int i = 1; i < NUMPIXELS; i++) {
        this->leds[i]->update(this->rd, this->gr, this->bl, 0);
        this->leds[i]->setColor(false);
      }
      this->step += 0.0025;
      if (this->step >= 1.00) this->step = 0.0025;
      this->pixelWrapper.show();
    }
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

  this->rd = lowerR + interpolation * (upperR - lowerR);
  this->gr = lowerG + interpolation * (upperG - lowerG);
  this->bl = lowerB + interpolation * (upperB - lowerB);
}

void GradientStrategy::setLeds(Led* ledsArr[NUMPIXELS]) {
  for (int i = 0; i < NUMPIXELS; i++) {
    this->leds[i] = ledsArr[i];
  }
}