#pragma once
#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

#include "Led.h"

class StrategyInterface {
public:
  virtual void loop() = 0;
  virtual void setup() = 0;
  virtual bool isSetuped() = 0;
  virtual void off() = 0;
  virtual void setLeds(Led* ledsArr[NUMPIXELS]) = 0;
  virtual ~StrategyInterface() = default;
};

#endif