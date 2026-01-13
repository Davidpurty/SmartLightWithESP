#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H
#include <Arduino.h>
class pinManager{
  public:
  void pinInit();
  void setPinState();
  int getPinState();

};
#endif
