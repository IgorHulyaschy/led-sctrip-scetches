#pragma once
#ifndef RAINBOW_STRATEGY_H
#define RAINBOW_STRATEGY_H

#include <Arduino.h>

#include "global-vars.h"
#include "Timer.h"
#include "Led.h"
#include "PixelWrapper.h"
#include "StrategyInterface.h"

class RainbowStrategy final : public StrategyInterface {
public:
  RainbowStrategy(PixelWrapper& pixelWrapper);

  bool isSetuped() override;
  void off() override;
  void setup() override;
  void loop() override;
  void setLeds(Led* ledsArr[NUMPIXELS]) override;
  void generateColor(int ledNumber);

  virtual ~RainbowStrategy() override = default;
private:
  bool isOn = false;
  PixelWrapper& pixelWrapper;
  Led* leds[NUMPIXELS];
  int rd = 0;
  int bl = 0;
  int gr = 0;
};

#endif