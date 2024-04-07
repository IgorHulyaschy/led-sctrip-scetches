#ifndef RGB_H
#define RGB_H

class RGB {
public:
  RGB(int red, int green, int blue);

  int getRed();
  int getGreen();
  int getBlue();

private:
  int red;
  int green;
  int blue;
};
#endif