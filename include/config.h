#pragma once
// ======================================================================
// config.h : hardware + screen settings
// ESP32-C3  +  2.9" 128x296 black/white e-paper  (GxEPD2_290_T94)
// Display only: no Wi-Fi, no sensors yet
// ======================================================================
#include <Arduino.h>

// ======================================================================
// 1. PIN CONFIG (ESP32-C3)
// ======================================================================
#define EPD_DC          6     // Data / Command
#define EPD_RST         7     // Reset
#define EPD_BUSY        8     // Busy (same pin as the LED on ESP32-C3 Super Mini)
#define EPD_CS         10     // Chip select
#define EPD_SCL         4     // SPI clock (SCK)
#define EPD_SDA         5     // SPI MOSI
// (this panel has no power-switch pin)

#define BUTTON_PIN               9      
#define BUTTON_ACTIVE_LEVEL      LOW    
#define BUTTON_USE_PULLUP        true   
#define BUTTON_DEBOUNCE_MS       30     
#define BUTTON_LONG_PRESS_MS     1000   


// ======================================================================
// 2. E-PAPER PANEL  (GxEPD2_290_T94, black / white)
// ======================================================================
// Native size of the panel (portrait)
#define EPD_NATIVE_W    128
#define EPD_NATIVE_H    296

// Size after rotation. EPD_ROTATION 1 = landscape 296 x 128.

#define EPD_ROTATION    1
#define EPD_ROTATION_LANDSCAPE  1   // 296 x 128  (used for bitmaps wider than tall)
#define EPD_ROTATION_PORTRAIT   0   // 128 x 296  (used for bitmaps taller than wide)
#define EPD_WIDTH       296
#define EPD_HEIGHT      128

// Frame buffer: 1 bit per pixel
#define EPD_BUF_SIZE    (EPD_NATIVE_W * EPD_NATIVE_H / 8)   // 4736 bytes

// display.init(serial_diag_bitrate, initial, reset_duration, pulldown_rst_mode)
#define EPD_SERIAL_DIAG     115200     // GxEPD2 diagnostics baud (0 = off)
#define EPD_INIT_INITIAL    true       // first start: force full refresh
#define EPD_RST_PULSE_MS    10         // reset pulse length (ms), GxEPD2 default
#define EPD_PULLDOWN_RST    false      // true only if RST has a hardware pull-down

// Refresh modes for display.display(partial)
#define EPD_FULL_REFRESH    false      // flashes, cleanest
#define EPD_FAST_REFRESH    true       // partial, no flash, may ghost


// ======================================================================
// 4. TIMING + SERIAL
// ======================================================================
#define LOOP_DELAY_MS            500
#define SERIAL_BAUD              115200