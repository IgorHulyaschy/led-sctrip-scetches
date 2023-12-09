#include "Timer.h"

void initiateTimer() {
  setTime(1637656800);
}

unix getTime() {
  return (now() * 1000) + (millis() % 1000);
}