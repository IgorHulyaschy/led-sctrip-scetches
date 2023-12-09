#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

#include "global-vars.h"

#include "Timer.h"
#include "StrategyInterface.h"
#include "WhiteColorStrategy.h"
#include "GradientStrategy.h"
// #include "RainbowStrategy.h"
#include "PixelWrapper.h"
#include "RGB.h"
#include "Led.h"

Led* leds[NUMPIXELS];
Bounce debouncer = Bounce();
Adafruit_NeoPixel adafruit_NeoPixel = Adafruit_NeoPixel(NUMPIXELS, PIN);
PixelWrapper pixelWrapper = PixelWrapper(adafruit_NeoPixel);
WhiteColorStrategy* whiteColorStrategy = new WhiteColorStrategy(pixelWrapper);
// RainbowStrategy* rainbowStrategy = new RainbowStrategy(pixelWrapper);
GradientStrategy* gradientStrategy = new GradientStrategy(pixelWrapper);

StrategyInterface* strategies[2] = { 
  // rainbowStrategy,
  whiteColorStrategy,
  gradientStrategy
};

volatile bool buttonPressed = false;
int previousButMode = 0;
int butMode = 0;
int modeCount = 2;

void setup() {
  Serial.begin(9600);
  pinMode(9, INPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  debouncer.attach(BUTTONPIN);
  debouncer.interval(50);
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), buttonInterrupt, FALLING);

  // Initializing of LEDS
  for (int i = 0; i < NUMPIXELS; i++) {
    RGB rgb = RGB(0, 0, 0);
    leds[i] = new Led(i, 0, rgb, pixelWrapper);
  }
  // Setting to Strategies leds
  for (int i = 0; i < modeCount; i++) {
    strategies[i]->setLeds(leds);
  }
  initiateTimer();
  pixelWrapper.begin();
}

void loop() {
  unix now = getTime();
  debouncer.update();
  if (buttonPressed && debouncer.fell()) {
    previousButMode = butMode;
    butMode = (butMode + 1) % (modeCount + 1);
    buttonPressed = false;
  }
  if (previousButMode != butMode) {
    previousButMode = butMode;
    for (int i = 0; i < modeCount; i++) {
      strategies[i]->off();
    }
  }
  switch (butMode) {
    case 0:
      for (int i = 0; i < modeCount; i++) {
        strategies[i]->off();
      }

      break;
    case 1:
      if(!strategies[0]->isSetuped()) {
        strategies[0]->setup();
      }
      strategies[0]->loop();
      break;
    case 2:
      if(!strategies[1]->isSetuped()) {
        strategies[1]->setup();
      }
      strategies[1]->loop();
      break;
    // case 3:
    //   if(!strategies[2]->isSetuped()) {
    //     strategies[2]->setup();
    //   }
    //   strategies[2]->loop();
    //   break;
    default: break;
  }
}

void buttonInterrupt() {
  buttonPressed = true;
}
