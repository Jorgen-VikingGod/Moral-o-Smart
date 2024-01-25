// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include "Button2.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define SPI_DC 6
#define SPI_BUSY 11
#define SPI_CS_1 SS
#define SPI_CS_2 5
#define SPI_CS_3 4

#define BTN_1 18
#define BTN_2 19
#define BTN_3 8
#define BTN_4 9

// 2.13'' EPD Module
GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display1(GxEPD2_213_BN(SPI_CS_1, SPI_DC, -1, SPI_BUSY));
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display2(GxEPD2_213_BN(SPI_CS_2, SPI_DC, -1, SPI_BUSY));
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display3(GxEPD2_213_BN(SPI_CS_3, SPI_DC, -1, SPI_BUSY));

Button2 button1;
Button2 button2;
Button2 button3;
Button2 button4;

void helloFullScreenPartialMode();

void click(Button2& btn) {
    if (btn == button1) {
      Serial.println("Button 1 clicked");
    } else if (btn == button2) {
      Serial.println("Button 2 clicked");
    } else if (btn == button3) {
      Serial.println("Button 3 clicked");
    } else if (btn == button4) {
      Serial.println("Button 4 clicked");
    }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello ESP32C3!!");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN_AUX, OUTPUT);

  button1.begin(BTN_1);
  button1.setClickHandler(click);

  button2.begin(BTN_2);
  button2.setClickHandler(click);

  button3.begin(BTN_3);
  button3.setClickHandler(click);

  button4.begin(BTN_4);
  button4.setClickHandler(click);

  display1.init(115200, true, 50, false);
  // display2.init(115200, true, 50, false);
  // display3.init(115200, true, 50, false);

  helloFullScreenPartialMode();

  display1.hibernate();
}

const char HelloWorld[] = "Hello World!";

void helloFullScreenPartialMode()
{
  Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display1.setPartialWindow(0, 0, display1.width(), display1.height());
  display1.setRotation(1);
  display1.setFont(&FreeMonoBold9pt7b);
  if (display1.epd2.WIDTH < 104)
    display1.setFont(0);
  display1.setTextColor(GxEPD_BLACK);
  const char *updatemode;
  if (display1.epd2.hasFastPartialUpdate)
  {
    updatemode = fpm;
  }
  else if (display1.epd2.hasPartialUpdate)
  {
    updatemode = spm;
  }
  else
  {
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  // center update text
  display1.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display1.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display1.height() / 4) - tbh / 2) - tby;
  // center update mode
  display1.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display1.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display1.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display1.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display1.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display1.height() - tbh) / 2) - tby;
  display1.firstPage();
  do
  {
    display1.fillScreen(GxEPD_WHITE);
    display1.setCursor(hwx, hwy);
    display1.print(HelloWorld);
    display1.setCursor(utx, uty);
    display1.print(fullscreen);
    display1.setCursor(umx, umy);
    display1.print(updatemode);
  } while (display1.nextPage());
  Serial.println("helloFullScreenPartialMode done");
}

void loop()
{
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUILTIN_AUX, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN_AUX, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  Serial.println("Loop");
}