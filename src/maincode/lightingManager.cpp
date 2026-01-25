#include "lightingManager.h"
#include "gpioManager.h"
pinManager LEDpins;

void LightingManager::begin() {
  for (uint8_t i = 0; i < MAX_ROOMS; i++) {
    _lightState[i] = false;
    _brightness[i] = 0;
    _timerActive[i] = false;
    _offTimestamp[i] = 0;
  }
  LEDpins.pinInit(MAX_ROOMS);
}

void LightingManager::turnOnLight(uint8_t roomId) {
  if (roomId >= MAX_ROOMS) return;

  _lightState[roomId] = true;
  //if (_brightness[roomId] == 0) _brightness[roomId] = 100;
  LEDpins.setPinState(roomId,_lightState[roomId]);
  //applyLight(roomId);
}

void LightingManager::turnOffLight(uint8_t roomId) {
  if (roomId >= MAX_ROOMS) return;

  _lightState[roomId] = false;
  _brightness[roomId] = 0;
  _timerActive[roomId] = false;
  LEDpins.setPinState(roomId,_lightState[roomId]);
  //applyLight(roomId);
}

void LightingManager::turnOffAllLight() {
  for (uint8_t i = 0; i < MAX_ROOMS; i++) {
    turnOffLight(i);
  }
}

void LightingManager::setBrightness(uint8_t roomId, uint8_t level) {
  if (roomId >= MAX_ROOMS) return;

  level = constrain(level, 0, 255);
  _brightness[roomId] = level;
  _lightState[roomId] = (level > 0);
  LEDpins.setPinState(roomId,_brightness[roomId]);
  //applyLight(roomId);
}

void LightingManager::setLightingTimer(uint8_t roomId, unsigned long timestamp) {
  if (roomId >= MAX_ROOMS) return;

  _offTimestamp[roomId] = timestamp;
  _timerActive[roomId] = true;
}

void LightingManager::cancelLightingTimer(uint8_t roomId) {
  if (roomId >= MAX_ROOMS) return;

  _timerActive[roomId] = false;
}

bool LightingManager::isLightOn(uint8_t roomId) {
  if (roomId >= MAX_ROOMS) return false;
  return _lightState[roomId];
}

uint8_t LightingManager::getBrightness(uint8_t roomId) {
  if (roomId >= MAX_ROOMS) return 0;
  return _brightness[roomId];
}

void LightingManager::update() {
  unsigned long now = millis();

  for (uint8_t i = 0; i < MAX_ROOMS; i++) {
    if (_timerActive[i] && now >= _offTimestamp[i]) {
      turnOffLight(i);
      _timerActive[i] = false;
    }
  }
}

void LightingManager::applyLight(uint8_t roomId) {
  // === HARDWARE CONTROL GOES HERE ===
  // Example:
  // PWM output, relay, PCA9685, etc.
  //LEDpins.setPinState(roomId,_lightState[roomId],_brightness[roomId]);
  
  // pwm.setPWM(roomId, 0, map(_brightness[roomId], 0, 100, 0, 4095));
}
