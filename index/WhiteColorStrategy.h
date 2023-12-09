#ifndef WHITE_COLOR_STRATEGY_H
#define WHITE_COLOR_STRATEGY_H

#include "global-vars.h"
#include "PixelWrapper.h"
#include "StrategyInterface.h"
#include "Led.h"
#include "Arduino.h"

class WhiteColorStrategy final : public StrategyInterface {
public:
  WhiteColorStrategy(PixelWrapper& pixelWrapper, Led* leds[NUMPIXELS]);

  bool isSetuped() override;
  void off() override;
  void setup() override;
  void loop() override;

  virtual ~WhiteColorStrategy() override = default;
private:
  bool isSetupDone = false;
  bool isOn = false;
  Led* leds[NUMPIXELS];
  PixelWrapper& pixelWrapper;
};

#endif