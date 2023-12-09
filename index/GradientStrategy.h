#ifndef GRADIENT_STRATEGY_H
#define GRADIENT_STRATEGY_H

#include "Arduino.h"

#include "global-vars.h"
#include "StrategyInterface.h"
#include "PixelWrapper.h"
#include "Led.h"

class GradientStrategy final : public StrategyInterface {
public:
  GradientStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS]);

  bool isSetuped() override;
  void off() override;
  void setup() override;
  void loop() override;
  void generateGradientColor(float position);

  virtual ~GradientStrategy() override = default;
private:
  bool isSetupDone = false;
  float step = 0.0025;
  PixelWrapper& pixelWrapper;
  Led* leds[NUMPIXELS];
  int rd = 0;
  int gr = 0;
  int bl = 0;
};

#endif