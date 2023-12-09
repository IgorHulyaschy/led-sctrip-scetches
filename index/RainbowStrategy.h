#ifndef RAINBOW_STRATEGY_H
#define RAINBOW_STRATEGY_H

#include "Arduino.h"
#include "PixelWrapper.h"
#include "StrategyInterface.h"
#include "Led.h"
#include "global-vars.h"

class RainbowStrategy final : public StrategyInterface {
public:
  RainbowStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS]);

  bool isSetuped() override;
  void off() override;
  void setup() override;
  void loop() override;
  void generateColor(int ledNumber);

  virtual ~RainbowStrategy() override = default;
private:
  bool isSetupDone = false;
  bool isOff = false;
  PixelWrapper& pixelWrapper;
  Led* leds[NUMPIXELS];
  int rd = 0;
  int bl = 0;
  int gr = 0;
};

#endif