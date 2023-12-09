#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

#include "GradientStrategy.h"
#include "RainbowStrategy.h"
#include "WhiteColorStrategy.h"
#include "PixelWrapper.h"
#include "RGB.h"
#include "Led.h"
#include "StrategyInterface.h"
#include "global-vars.h"


volatile bool buttonPressed = false;


int gr = 0;
int bl = 0;
int rd = 0;
int previousButMode = 0;
int butMode = 0;
int modeCount = 3;
Led* leds[NUMPIXELS];

// **********************************
Bounce debouncer = Bounce();
Adafruit_NeoPixel adafruit_NeoPixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
PixelWrapper pixelWrapper = PixelWrapper(adafruit_NeoPixel);
RainbowStrategy rainbowStrategy = RainbowStrategy(pixelWrapper, leds);
WhiteColorStrategy whiteColorStrategy = WhiteColorStrategy(pixelWrapper, leds);
GradientStrategy gradientStrategy = GradientStrategy(pixelWrapper, leds);
StrategyInterface* strategies[3] = { &rainbowStrategy, &whiteColorStrategy, &gradientStrategy };

void setup() {
  Serial.begin(9600);
  pinMode(9, INPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  debouncer.attach(BUTTONPIN);
  debouncer.interval(5);
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), buttonInterrupt, FALLING);
  for (int i = 0; i < NUMPIXELS; i++) {
    RGB rgb = RGB(0, 0, 0);
    leds[i] = new Led(i, 0, rgb, pixelWrapper);
  }
  pixelWrapper.begin();
}

void loop() {
  long now = millis();
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
      for (int i= 0; i < modeCount; i++) {
        strategies[i]->off();
      }
      break;
    case 1:
      strategies[0]->loop();
      break;
    case 2:
      strategies[1]->loop();
      break;
    case 3:
      strategies[2]->loop();
      break;
  }
  Serial.println(millis() - now);
}

void buttonInterrupt() {
  buttonPressed = true;
  // strategies[0]->abort();
}