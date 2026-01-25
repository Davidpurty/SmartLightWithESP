#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H
#include <Arduino.h>
class pinManager{
  public:
  void pinInit(int maxRooms);
  void setPinState(int, bool);
  void setPinState(int, int);
  int getPinState();

};
#endif
