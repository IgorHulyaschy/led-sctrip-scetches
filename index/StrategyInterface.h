#ifndef STRATEGY_INTERFACE_H
#define STRATEGY_INTERFACE_H

class StrategyInterface {
public:
  virtual void loop() = 0;
  virtual void setup() = 0;
  virtual bool isSetuped() = 0;
  virtual void off() = 0;
  virtual ~StrategyInterface() = default;
};

#endif