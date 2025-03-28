#ifndef THE_SCREEN_hpp
#define THE_SCREEN_hpp

#include "../../../src/CONFIG.hpp"
#ifdef SCREEN_SSD1306
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Use I2C, lib "Wire" sda/scl to connect
#endif

#define u8g2_uint_t uint32_t

class TheScreen
{
public:
    TheScreen();
    void setup();
    void loop();
    void clear();
    void draw();

    void drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, uint16_t color);
    // void setDrawColor(uint8_t color_index);
    void drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

private:
    bool screenReady;
#ifdef SCREEN_SSD1306
    Adafruit_SSD1306 display;
    // uint16_t color;
#endif
};

#endif