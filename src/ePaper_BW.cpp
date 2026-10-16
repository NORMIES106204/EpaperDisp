#include "ePaper_BW.h"
#include <SPI.h>

EpdDisplay display(GxEPD2_290_T94(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

void ePaper_BW_init() {
  SPI.begin(EPD_SCL, -1, EPD_SDA, EPD_CS);   // must run before display.init()
  display.init(EPD_SERIAL_DIAG, EPD_INIT_INITIAL, EPD_RST_PULSE_MS, EPD_PULLDOWN_RST);
  display.setRotation(EPD_ROTATION);
  ePaper_BW_clear();                         // all white, ready to flash
}

void ePaper_BW_setRotation(uint8_t rotation) {
  display.setRotation(rotation);
}

void ePaper_BW_storeBitmap(const unsigned char *bmp, int16_t w, int16_t h,
                           int16_t x, int16_t y, bool clearFirst) {
  if (clearFirst) display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(x, y, bmp, w, h, GxEPD_BLACK);   // 1 bits = black
}

void ePaper_BW_storeImage(const EpdBitmap &bmp) {
  display.setRotation(bmp.w >= bmp.h ? EPD_ROTATION_LANDSCAPE : EPD_ROTATION_PORTRAIT);
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(0, 0, bmp.data, bmp.w, bmp.h, GxEPD_BLACK);   // 1 bits = black
}

void ePaper_BW_flash(bool fast) {
  display.display(fast);
}

void ePaper_BW_clear() {
  display.fillScreen(GxEPD_WHITE);
  display.display(EPD_FULL_REFRESH);
}

void ePaper_BW_sleep() {
  display.hibernate();
}