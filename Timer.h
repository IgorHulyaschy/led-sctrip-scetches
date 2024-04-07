#ifndef TIMER_H
#define TIMER_H

#include <TimeLib.h>
#include <Arduino.h>

typedef unsigned long unix;
void initiateTimer();
unix getTime();

#endif