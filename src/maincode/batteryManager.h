#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include <Arduino.h>

class BatteryManager {
public:
  void begin();

  int  batteryLevel();                 // 0–100 %
  bool batteryChargingStatus();         // true = charging

  void startCharging();
  void stopCharging();

  void startProtectionMode();
  void stopProtectionMode();

  void updateBatteryStatusOnCloud();

private:
  int  _batteryPercent;
  bool _isCharging;
  bool _protectionEnabled;

  int  readBatteryADC();
};

#endif
