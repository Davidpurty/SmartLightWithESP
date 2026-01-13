#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <Arduino.h>

#define MAX_ROOMS 16   // adjust as needed

class LightingManager {
public:
  void begin();

  // Basic control
  void turnOnLight(uint8_t roomId);
  void turnOffLight(uint8_t roomId);
  void turnOffAllLight();

  // Brightness (0–100%)
  void setBrightness(uint8_t roomId, uint8_t level);

  // Timers
  void setLightingTimer(uint8_t roomId, unsigned long timestamp);
  void cancelLightingTimer(uint8_t roomId);

  // State query (VERY useful)
  bool isLightOn(uint8_t roomId);
  uint8_t getBrightness(uint8_t roomId);

  // Periodic update (non-blocking)
  void update();

private:
  // State
  bool _lightState[MAX_ROOMS];
  uint8_t _brightness[MAX_ROOMS];

  // Timer handling
  unsigned long _offTimestamp[MAX_ROOMS];
  bool _timerActive[MAX_ROOMS];

  // Hardware abstraction
  void applyLight(uint8_t roomId);
};

#endif
