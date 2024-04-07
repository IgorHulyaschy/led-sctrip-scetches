#pragma once
#ifndef WHITE_COLOR_STRATEGY_H
#define WHITE_COLOR_STRATEGY_H

#include <Arduino.h>
#include "global-vars.h"

#include "Led.h"
#include "PixelWrapper.h"
#include "StrategyInterface.h"
#include "Timer.h"

class WhiteColorStrategy final : public StrategyInterface {
public:
  WhiteColorStrategy(PixelWrapper& pixelWrapper);

  bool isSetuped() override;
  void off() override;
  void setup() override;
  void loop() override;
  void setLeds(Led* ledsArr[NUMPIXELS]) override;

  virtual ~WhiteColorStrategy() override = default;
private:
  bool isSetupDone = false;
  Led* leds[NUMPIXELS];
  PixelWrapper& pixelWrapper;
};

#endif