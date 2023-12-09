// #include <Adafruit_NeoPixel.h>
// #include <Bounce2.h>

// #include "PixelWrapper.h"
// #include "RainbowStrategy.h"
// #include "StrategyInterface.h"

// #define PIN 9  // input pin Neopixel is attached to
// #define NUMPIXELS 60           // number of neopixels in Ring
// #define RAINBOWDELAY 50        // delay before next led will execute
// #define BUTTONPIN 3            // button pin
// #define GRADIENTDELAY 100 //delay before change gradient color


// volatile bool buttonPressed = false;
// Adafruit_NeoPixel adafruit_NeoPixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Bounce debouncer = Bounce();
// int gr = 0;
// int bl = 0;
// int rd = 0;
// int previousButMode = 0;
// int butMode = 0;
// int modeCount = 3;

// void generateGradientColor(float position) {
//   const uint8_t gradient[][3] = {
//     { 255, 0, 0 },    // Red
//     { 255, 255, 0 },  // Yellow
//     { 0, 255, 0 },    // Green
//     { 0, 0, 255 },    // Blue
//     { 255, 0, 255 },  // Magenta
//     { 255, 0, 0 }
//   };
//   int numColors = sizeof(gradient) / sizeof(gradient[0]);
//   if (position < 0.0) {
//     position = 0.0;
//   } else if (position > 1.0) {
//     position = 1.0;
//   }
//   float index = position * (numColors - 1);
//   int lowerIndex = floor(index);
//   int upperIndex = ceil(index);
//   float interpolation = index - lowerIndex;

//   uint8_t lowerR = gradient[lowerIndex][0];
//   uint8_t lowerG = gradient[lowerIndex][1];
//   uint8_t lowerB = gradient[lowerIndex][2];

//   uint8_t upperR = gradient[upperIndex][0];
//   uint8_t upperG = gradient[upperIndex][1];
//   uint8_t upperB = gradient[upperIndex][2];

//   rd = lowerR + interpolation * (upperR - lowerR);
//   gr = lowerG + interpolation * (upperG - lowerG);
//   bl = lowerB + interpolation * (upperB - lowerB);
// }

// void generateColor(int ledNumber) {
//   // Створення кольорового градієнту від червоного до синього
//   if (ledNumber < 10) {
//     rd = 255;
//     gr = map(ledNumber, 0, 10, 0, 255);
//     bl = 0;
//   } else if (ledNumber < 20) {
//     rd = map(ledNumber, 10, 20, 255, 0);
//     gr = 255;
//     bl = 0;
//   } else if (ledNumber < 30) {
//     rd = 0;
//     gr = 255;
//     bl = map(ledNumber, 20, 30, 0, 255);
//   } else if (ledNumber < 40) {
//     rd = 0;
//     gr = map(ledNumber, 30, 40, 255, 0);
//     bl = 255;
//   } else if (ledNumber < 50) {
//     rd = map(ledNumber, 40, 50, 0, 255);
//     gr = 0;
//     bl = 255;
//   } else {
//     rd = 255;
//     gr = 0;
//     bl = map(ledNumber, 50, 60, 255, 0);
//   }
// }

// // **********************************
// class RGB {
// public:
//   RGB(int red, int green, int blue)
//     : red(red), green(green), blue(blue) {}

//   int getRed() {
//     return red;
//   }
//   int getGreen() {
//     return green;
//   }
//   int getBlue() {
//     return blue;
//   }
// private:
//   int red;
//   int green;
//   int blue;
// };
// // **********************************
// class PixelWrapper {
// public:
//   PixelWrapper(): lib(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800) {}

//   void setPixelColor(int index, int r, int g, int b) {
//       lib.setPixelColor(index, lib.Color(r, g, b));
//   }

//   void show() {
//       lib.show();
//   }

//   void off(int ledNumber) {
//       setPixelColor(ledNumber, 0, 0, 0);
//   }

//   void begin() {
//       lib.begin();
//   }

// private:
//   Adafruit_NeoPixel lib;
// };
// class Led {
// public:
//   Led(int ledNumber, long executeAt, RGB color, PixelWrapper& pixelLib)
//     : ledNumber(ledNumber), executeAt(executeAt), color(color), pixelLib(pixelLib) {}

//   void setColor(bool needToShow) {
//     pixelLib.setPixelColor(ledNumber, color.getRed(), color.getGreen(), color.getBlue());
//     if (needToShow) show();
//   }

//   void update(int r, int g, int b, long time) {
//     color = RGB(r, g, b);
//     executeAt = time;
//   }

//   long getTime() {
//     return executeAt;
//   }

//   void show() {
//     pixelLib.show();
//   }

//   bool isOff() {
//     return color.getRed() == 0 && color.getGreen() == 0 && color.getBlue() == 0;
//   }

//   RGB getColor() {
//     return color;
//   }

//   bool checkTime(long now) {
//     return now >= executeAt;
//   }

// private:
//   RGB color;
//   PixelWrapper& pixelLib;
//   int ledNumber;
//   long executeAt;
// };

// Led* leds[NUMPIXELS];
// // **********************************
// class StrategyInterface {
// public:
//   virtual void loop() = 0;
//   virtual void setup() = 0;
//   virtual bool isSetuped() = 0;
//   virtual void off() = 0;
//   virtual ~StrategyInterface() = default;
// };
// // **********************************
// class RainbowStrategy final : public StrategyInterface {
// public:
//   RainbowStrategy(PixelWrapper& pixelWrapper)
//     : pixelWrapper(pixelWrapper) {}

//   bool isSetuped() override {
//     return isSetupDone;
//   }

//   void off() override {
//     if (isSetupDone) {
//       Serial.println("here1");
//       for (int i = 0; i < NUMPIXELS; i++) {
//         leds[i]->update(0, 0, 0, 0);
//         leds[i]->setColor(false);
//       }
//       pixelWrapper.show();
//       isSetupDone = false;
//     }
//   }

//   void setup() override {
//     int delay = RAINBOWDELAY;
//     long now = millis();
//     for (int i = 0; i < NUMPIXELS; i++) {
//       generateColor(i);
//       leds[i]->update(rd, gr, bl, now + delay);
//       delay += RAINBOWDELAY;
//     }
//     isOff = false;
//     isSetupDone = true;
//   }

//   void loop() override {
//     if (!isSetuped()) {
//       setup();
//     }
//     int now = millis();
//     for (int i = 0; i < NUMPIXELS; i++) {
//       bool needToChangeColor = leds[i]->checkTime(now);
//       if (needToChangeColor) {
//         leds[i]->setColor(true);
//         if(leds[i]->isOff()) {
//           generateColor(i);
//           leds[i]->update(rd, gr, bl, leds[i]->getTime() + RAINBOWDELAY * (NUMPIXELS-1));
//         } else {
//           leds[i]->update(0, 0, 0, leds[i]->getTime() + RAINBOWDELAY * (NUMPIXELS-1));
//         }
//       }
//     }
//   }
//   virtual ~RainbowStrategy() override = default;
// private:
//   bool isSetupDone = false;
//   bool isOff = false;
//   PixelWrapper& pixelWrapper;
// };

// // **********************************
// class WhiteColorStrategy final : public StrategyInterface {
// public:
//   WhiteColorStrategy(PixelWrapper& pixelWrapper)
//     : pixelWrapper(pixelWrapper) {}
//   bool isSetuped() override {
//     return isSetupDone;
//   }

//   void off() override {
//     if (isSetupDone) {
//       for (int i = 0; i < NUMPIXELS; i++) {
//         leds[i]->update(0, 0, 0, 0);
//         leds[i]->setColor(false);
//       }
//       pixelWrapper.show();
//       isSetupDone = false;
//       isOn = false;
//     }
//   }

//   void setup() override {
//     long now = millis();
//     for (int i = 0; i < NUMPIXELS; i++) {
//       leds[i]->update(255, 230, 150, now);  // 255 230 150
//     }
//     isSetupDone = true;
//   }

//   void loop() override {
//     if (!isSetuped()) {
//       setup();
//     }

//     if (!isOn) {
//       int now = millis();
//       for (int i = 0; i < NUMPIXELS; i++) {
//         bool needToChangeColor = leds[i]->checkTime(now);
//         if (needToChangeColor) {
//           leds[i]->setColor(false);
//         }
//       }
//       pixelWrapper.show();
//       isOn = true;
//     }
//   }
//   virtual ~WhiteColorStrategy() override = default;
// private:
//   bool isSetupDone = false;
//   bool isOn = false;
//   PixelWrapper& pixelWrapper;
// };
// // **********************************
// class GradientStrategy final : public StrategyInterface {
// public:
//   GradientStrategy(PixelWrapper& pixelWrapper)
//     : pixelWrapper(pixelWrapper) {}

//   bool isSetuped() override {
//     return isSetupDone;
//   }

//   void off() override {
//     if (isSetupDone) {
//       for (int i = 0; i < NUMPIXELS; i++) {
//         leds[i]->update(0, 0, 0, 0);
//         leds[i]->setColor(false);
//       }
//       pixelWrapper.show();
//       Serial.println("here3");
//       isSetupDone = false;
//     }
//   }

//   void setup() override {
//     long now = millis();
//     generateGradientColor(step);
//     for (int i = 0; i < NUMPIXELS; i++) {
//       leds[i]->update(rd, gr, bl, now);  // 255 230 150
//     }
//     isSetupDone = true;
//   }

//   void loop() override {
//     if (!isSetuped()) {
//       setup();
//     }
//     int now = millis();
//     generateGradientColor(step);
//     bool needToChangeColor = leds[0]->checkTime(now);
//     if (needToChangeColor) {
//       // Setting timerange only for the first one
//       leds[0]->update(rd, gr, bl, now + GRADIENTDELAY);
//       leds[0]->setColor(false);
//       for (int i = 1; i < NUMPIXELS; i++) {
//         leds[i]->update(rd, gr, bl, 0);
//         leds[i]->setColor(false);
//       }
//       step += 0.0025;
//       if (step >= 1.00) step = 0.0025;
//       pixelWrapper.show();
//     }
//   }
//   virtual ~GradientStrategy() override = default;
// private:
//   bool isSetupDone = false;
//   float step = 0.0025;
//   PixelWrapper& pixelWrapper;
// };
// **********************************
// PixelWrapper pixelWrapper = PixelWrapper();
// RainbowStrategy rainbowStrategy = RainbowStrategy(pixelWrapper);
// WhiteColorStrategy whiteColorStrategy = WhiteColorStrategy(pixelWrapper);
// GradientStrategy gradientStrategy = GradientStrategy(pixelWrapper);
// StrategyInterface* strategies[3] = { &rainbowStrategy, &whiteColorStrategy, &gradientStrategy };

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  // pinMode(BUTTONPIN, INPUT_PULLUP);
  // debouncer.attach(BUTTONPIN);
  // debouncer.interval(5);
  // attachInterrupt(digitalPinToInterrupt(BUTTONPIN), buttonInterrupt, FALLING);
  // for (int i = 0; i < NUMPIXELS; i++) {
    // RGB rgb = RGB(0, 0, 0);
    // leds[i] = new Led(i, 0, rgb, pixelWrapper);
  // }
  // pixelWrapper.begin();
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  // long now = millis();
  // debouncer.update();
  // if (buttonPressed && debouncer.fell()) {
  //   previousButMode = butMode;
  //   butMode = (butMode + 1) % (modeCount + 1);
  //   buttonPressed = false;
  // }
  // if (previousButMode != butMode) {
  //   previousButMode = butMode;
  //   for (int i = 0; i < modeCount; i++) {
  //     strategies[i]->off();
  //   }
  // }
  // switch (butMode) {
  //   case 0:
  //     for (int i= 0; i < modeCount; i++) {
  //       strategies[i]->off();
  //     }
  //     break;
  //   case 1:
  //     strategies[0]->loop();
  //     break;
  //   case 2:
  //     strategies[1]->loop();
  //     break;
  //   case 3:
  //     strategies[2]->loop();
  //     break;
  // }
  // Serial.println("alo1");
  // Serial.print(strategies[0]->isSetuped());
  // Serial.print("alo2");
  // Serial.print(strategies[1]->isSetuped());
  // Serial.print("alo3");
  // Serial.print(strategies[2]->isSetuped());
  // Serial.println(millis() - now);
}

// void buttonInterrupt() {
  // buttonPressed = true;
  // strategies[0]->abort();
// }