#pragma once
// ======================================================================
// Button : debounced single-button logic (non-blocking)
//
//   BTN_SHORT : button pressed and released before the long-press time
//   BTN_LONG  : button held for BUTTON_LONG_PRESS_MS (fires once, while still held)
//
// Pin + timing come from config.h (BUTTON_PIN, BUTTON_ACTIVE_LEVEL, ...).
// Call Button_update() on every pass of loop(); it returns each event once.
// ======================================================================
#include <Arduino.h>
#include "config.h"

// Fallbacks so the module also works without the button section in config.h
#ifndef BUTTON_PIN
  #define BUTTON_PIN             21
#endif
#ifndef BUTTON_ACTIVE_LEVEL
  #define BUTTON_ACTIVE_LEVEL    LOW
#endif
#ifndef BUTTON_USE_PULLUP
  #define BUTTON_USE_PULLUP      true
#endif
#ifndef BUTTON_DEBOUNCE_MS
  #define BUTTON_DEBOUNCE_MS     30
#endif
#ifndef BUTTON_LONG_PRESS_MS
  #define BUTTON_LONG_PRESS_MS   1000
#endif

enum ButtonEvent : uint8_t {
  BTN_NONE = 0,    // nothing happened
  BTN_SHORT,       // one short press (reported on release)
  BTN_LONG         // long press (reported as soon as the hold time is reached)
};

// Set the pin mode. Call once in setup().
void Button_init();

// Poll the button. Call every loop(). Returns BTN_NONE / BTN_SHORT / BTN_LONG.
ButtonEvent Button_update();

// True while the button is physically held down (debounced).
bool Button_isDown();