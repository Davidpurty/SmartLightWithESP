#include "batteryManager.h"
//#include "gpioManager.h"
void BatteryManager::begin() {
  _batteryPercent = 0;
  _isCharging = false;
  _protectionEnabled = false;
  //BMSpins.pinInit();
}
//we will work on battery management right now
int BatteryManager::readBatteryADC() {
  // Example: ESP8266 ADC read
  return analogRead(A0);
}

int BatteryManager::batteryLevel() {
  int adc = readBatteryADC();
  _batteryPercent = map(adc, 0, 1023, 0, 100);
  return _batteryPercent;
}

bool BatteryManager::batteryChargingStatus() {
  return _isCharging;
}

void BatteryManager::startCharging() {
  _isCharging = true;
  // GPIO HIGH to enable charger
}

void BatteryManager::stopCharging() {
  _isCharging = false;
  // GPIO LOW to disable charger
}

void BatteryManager::startProtectionMode() {
  _protectionEnabled = true;
  // Cut load / reduce power
}

void BatteryManager::stopProtectionMode() {
  _protectionEnabled = false;
}

void BatteryManager::updateBatteryStatusOnCloud() {
  // Send data via MQTT / HTTP
}
