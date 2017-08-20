#include <TFT_ST7735.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_ST7735 tft = TFT_ST7735();

#define TFT_W 160
#define TFT_H 128

void setup() {
  tft.init();
  tft.setRotation(1);
}

void loop() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_RED);
  tft.drawCentreString("*Hello World", TFT_W/2, TFT_H/2, 2);
 delay(500);
}
