#include "button.h"

static bool     s_rawLast   = false;   // last raw reading
static bool     s_down      = false;   // debounced state (true = pressed)
static uint32_t s_lastEdge  = 0;       // time of the last raw change
static uint32_t s_pressTime = 0;       // time the debounced press started
static bool     s_longFired = false;   // long press already reported for this hold

static inline bool readPressed() {
  return digitalRead(BUTTON_PIN) == BUTTON_ACTIVE_LEVEL;
}

void Button_init() {
  pinMode(BUTTON_PIN, BUTTON_USE_PULLUP ? INPUT_PULLUP : INPUT);
  s_rawLast   = readPressed();
  s_down      = s_rawLast;
  s_lastEdge  = millis();
  s_pressTime = s_lastEdge;
  s_longFired = s_down;                // held at boot: don't fire a press for it
}

ButtonEvent Button_update() {
  const uint32_t now = millis();
  const bool raw = readPressed();

  if (raw != s_rawLast) {              // raw level changed: restart debounce timer
    s_rawLast  = raw;
    s_lastEdge = now;
  }

  // Raw level stable long enough -> accept it as the real state
  if ((now - s_lastEdge) >= BUTTON_DEBOUNCE_MS && raw != s_down) {
    s_down = raw;
    if (s_down) {                      // pressed
      s_pressTime = now;
      s_longFired = false;
    } else if (!s_longFired) {         // released before the long-press time
      return BTN_SHORT;
    }
  }

  // Still held past the long-press time -> report once
  if (s_down && !s_longFired && (now - s_pressTime) >= BUTTON_LONG_PRESS_MS) {
    s_longFired = true;
    return BTN_LONG;
  }

  return BTN_NONE;
}

bool Button_isDown() {
  return s_down;
}