#include <TFT_ST7735.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_ST7735 tft = TFT_ST7735();

#define TFT_W 160
#define TFT_H 128

#define btnPin 0   // Analog input 0 used for Keyboard

#define btnFEL     2
#define btnLE   3
#define btnBAL   1
#define btnENTER  4
#define btnNONE   -1

/*---( declare Variables )----*/

int buttonpressed;
int getButton()
{
  int i, v, button;
  int sum = 0;

  for (i = 0; i < 4; i++) {
    sum += analogRead(btnPin);
  }
  v = sum / 4;
  if (v > 1000) button = 0;
  else if (v >= 0  && v < 20)  button = 1; //LEFT
  else if (v > 135 && v < 155) button = 2; //UP
  else if (v > 315 && v < 335) button = 3; //DOWN
  else if (v > 495 && v < 515) button = 4; //RIGHT
  else button = 0;
 
  return button;
}// END getButton

/*-------------------( Debounce keystrokes, translate to buttons )-------------------*/
int old_button = 0;
int read_keyboard()
{
  int button, button2, pressed_button;
  button = getButton();         // Above
  if (button != old_button)     // A new button pressed
  {
    delay(50);                // debounce
    button2 = getButton();
    if (button == button2)
    {
      old_button = button;
      pressed_button = button;
      if (button != 0)
      {
        //Serial.println(button);
        if (button == 1) return btnBAL;
        if (button == 2) return btnFEL;
        if (button == 3) return btnLE;
        if (button == 4) return btnENTER;
      }
    }
  }
  else
  {
    return btnNONE;
  }
}// End read_keyboard


void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
}

void loop() {
  buttonpressed = read_keyboard();
  
  if (buttonpressed != btnNONE) 
  {
  Serial.print(" Lenyomva = ");
  Serial.println(buttonpressed);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_RED);
  tft.drawString("*Hello World", 0, 0, 2);
  tft.drawString(buttonpressed, 0, 12, 2);
  }
}
