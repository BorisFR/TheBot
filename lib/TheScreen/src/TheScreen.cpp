#include "TheScreen.hpp"

#ifdef SCREEN_SSD1306
TheScreen::TheScreen() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
#else
TheScreen::TheScreen()
#endif
{
    Serial.println("TheScreen()");
    screenReady = false;
}

void TheScreen::setup()
{
    Serial.println("TheScreen setup");
#ifdef SCREEN_SSD1306
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    else
    {
        screenReady = true;
        clear();
        // color = SSD1306_WHITE;
    }
#endif
}

void TheScreen::loop()
{
    if (!screenReady)
        return;
}

void TheScreen::clear()
{
    if (!screenReady)
        return;
#ifdef SCREEN_SSD1306
    display.clearDisplay();
#endif
}

void TheScreen::draw()
{
    if (!screenReady)
        return;
#ifdef SCREEN_SSD1306
    display.display();
#endif
}

void TheScreen::drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, uint16_t color)
{
#ifdef SCREEN_SSD1306
    display.drawFastHLine(x, y, w, color);
#endif
}

/*void TheScreen::setDrawColor(uint8_t color_index)
{
#ifdef SCREEN_SSD1306
    color = color_index;
#endif
}*/

void TheScreen::drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, uint16_t color)
{
#ifdef SCREEN_SSD1306
    display.fillRect(x, y, w, h, color);
#endif
}

void TheScreen::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
#ifdef SCREEN_SSD1306
    display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
#endif
}