// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include "Button2.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>

#define SPI_DC 6
#define SPI_BUSY 11
#define SPI_CS_1 SS
#define SPI_CS_2 5
#define SPI_CS_3 4

#define BTN_1 18
#define BTN_2 19
#define BTN_3 8
#define BTN_4 9

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

// 2.13'' EPD Module
GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display1(GxEPD2_213_BN(SPI_CS_1, SPI_DC, -1, SPI_BUSY));
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display2(GxEPD2_213_BN(SPI_CS_2, SPI_DC, -1, SPI_BUSY));
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display3(GxEPD2_213_BN(SPI_CS_3, SPI_DC, -1, SPI_BUSY));

Button2 button1;
Button2 button2;
Button2 button3;
Button2 button4;

void fontDemo();
void drawPage();

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
  u8g2Fonts.begin(display1); // connect u8g2 procedures to Adafruit GFX
  // display2.init(115200, true, 50, false);
  // display3.init(115200, true, 50, false);

  fontDemo();

  display1.hibernate();
}

void fontDemo()
{
  display1.setFullWindow();
  display1.setRotation(1);
  u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);              // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_profont22_mf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  display1.firstPage();
  do
  {
    drawPage();
  }
  while (display1.nextPage());
}

void drawPage()
{
  display1.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(0, 0);
  u8g2Fonts.println();
  u8g2Fonts.println(" !\"#$%&'()*+,-./<=>?@");
  u8g2Fonts.println("0123456789:;[\\]^_`{|}");
  u8g2Fonts.println("ABCDEFGHIJKLMNOPQRSTU");
  u8g2Fonts.println("VWXYZabcdefghijklmnop");
  u8g2Fonts.println("qrstuvwxyz~");
  u8g2Fonts.println("Umlaute: ÄÖÜäéöü");
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

