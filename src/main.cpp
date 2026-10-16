// Flash the e-paper with the bitmaps you like.
//   short press : next bitmap in the list (cycles), flash it
//   long press  : white out the screen, then flash the "opening" bitmap
// Bitmaps can be landscape (296x128) or portrait (128x296): rotation is automatic.
#include <Arduino.h>
#include "ePaper_BW.h"
#include "bitmaps.h"       // BMP_OPENING, BMP_KALI, BMP_QR_BIDV, BMP_QR_MB
#include "button.h"

const EpdBitmap bitmapList[] = { BMP_OPENING, BMP_KALI, BMP_QR_BIDV, BMP_QR_MB };
const uint8_t BITMAP_COUNT = sizeof(bitmapList) / sizeof(bitmapList[0]);

int8_t current = 0;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  Serial.println("\n=== Button + e-paper ===");

  ePaper_BW_init();                  // screen white
  Button_init();

  ePaper_BW_showImage(bitmapList[0]);   // BMP_OPENING
  current = 0;
}

void loop() {
  ButtonEvent e = Button_update();
  static uint32_t lastDbg = 0;

  if (e == BTN_SHORT) {
    current = (current + 1) % BITMAP_COUNT;           // next bitmap, wraps around
    Serial.printf("Short press -> bitmap %d\n", current);
    ePaper_BW_storeImage(bitmapList[current]);
    ePaper_BW_flash();
  }
  else if (e == BTN_LONG) {
    Serial.println("Long press -> white out + opening");
    ePaper_BW_clear();                                // white out (flash)
    ePaper_BW_showImage(bitmapList[0]);               // flash "opening"
    current = 0;                                      // back to opening; next short press -> bitmap 1
  }
}