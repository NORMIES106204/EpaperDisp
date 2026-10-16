#pragma once
// ======================================================================
// ePaper_BW : 2.9" black/white e-paper module (GxEPD2_290_T94)
//
// Bitmaps live in bitmaps.h as plain arrays (qr_bidv, qr_mb, ...) with the
// size in QR_CARD_W / QR_CARD_H. Use them by name:
//
//   ePaper_BW_init();            // panel ready, screen white
//   ePaper_BW_store(qr_bidv);    // put the bitmap into RAM (screen unchanged)
//   ePaper_BW_flash();           // flash it onto the screen
//
// or both at once:  ePaper_BW_show(qr_bidv);
//
// NOTE: include "bitmaps.h" in the .cpp that calls store/show (normally
// main.cpp), AFTER or BEFORE this header, so the data is stored once in flash.
// ======================================================================
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include "config.h"

// Display type (full frame buffer in RAM)
using EpdDisplay = GxEPD2_BW<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT>;

// Global display object: use it for extra drawing (text, lines, shapes)
extern EpdDisplay display;

// ----------------------------------------------------------------------
// Setup
// ----------------------------------------------------------------------
// Start SPI, init the panel, set rotation, flash the whole screen white.
void ePaper_BW_init();

// Change rotation at run time (0/2 = portrait 128x296, 1/3 = landscape 296x128).
void ePaper_BW_setRotation(uint8_t rotation);

// ----------------------------------------------------------------------
// Store a bitmap into the RAM buffer (screen does not change yet)
// ----------------------------------------------------------------------
// By name, size taken from bitmaps.h (QR_CARD_W x QR_CARD_H), drawn at (0,0).
// Replaces whatever was in the buffer.
#define ePaper_BW_store(bmp)   ePaper_BW_storeBitmap((bmp), QR_CARD_W, QR_CARD_H)

// ----------------------------------------------------------------------
// Self-describing bitmaps (recommended): size travels with the bitmap and the
// rotation is chosen automatically (wider than tall = landscape, else portrait).
//
//   in bitmaps.h:   #define kali_W 296   #define kali_H 128
//                   static const EpdBitmap BMP_KALI = EPD_BITMAP(kali);
//   in main.cpp:    ePaper_BW_storeImage(BMP_KALI);  ePaper_BW_flash();
//              or:  ePaper_BW_showImage(BMP_KALI);
// ----------------------------------------------------------------------
struct EpdBitmap {
  const unsigned char *data;
  int16_t w;
  int16_t h;
};
#define EPD_BITMAP(name)  { name, name##_W, name##_H }

// Set rotation from the bitmap shape, wipe the buffer white, draw it at (0,0).
void ePaper_BW_storeImage(const EpdBitmap &bmp);

// store + flash in one call.
#define ePaper_BW_showImage(bmp)  do { ePaper_BW_storeImage(bmp); ePaper_BW_flash(); } while (0)

// Explicit size / position, for bitmaps of another size.
//   clearFirst = true  -> buffer is wiped white first (replace)
//   clearFirst = false -> drawn on top of the buffer (combine bitmaps)
void ePaper_BW_storeBitmap(const unsigned char *bmp, int16_t w, int16_t h,
                           int16_t x = 0, int16_t y = 0, bool clearFirst = true);

// ----------------------------------------------------------------------
// Flash to the screen
// ----------------------------------------------------------------------
// Push the RAM buffer to the screen.
//   fast = false -> full refresh (flashes, clean)
//   fast = true  -> partial refresh (no flash, may ghost)
void ePaper_BW_flash(bool fast = false);

// store + flash in one call, by name.
#define ePaper_BW_show(bmp)    do { ePaper_BW_store(bmp); ePaper_BW_flash(); } while (0)

// Clear the screen to white (full refresh, flashes once).
void ePaper_BW_clear();

// ----------------------------------------------------------------------
// Power
// ----------------------------------------------------------------------
// Low-power sleep. The image stays on the screen. Call ePaper_BW_init() to wake.
void ePaper_BW_sleep();