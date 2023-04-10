/**
 * GOODISPLAY product https://www.good-display.com/product/432.html
 * Controller: SSD1680 (Solomon)
 * 
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <string>

#include "epdspi.h"

#define GDEY027T91_WIDTH 176
#define GDEY027T91_HEIGHT 264
#define GDEY027T91_BUFFER_SIZE (uint32_t(GDEY027T91_WIDTH) * uint32_t(GDEY027T91_HEIGHT) / 8)

// 1 byte of this color in the buffer
#define GDEY027T91_8PIX_BLACK 0xFF
#define GDEY027T91_8PIX_WHITE 0x00

#define EPD_BLACK     0x0000
#define EPD_DARKGREY  0x7BEF      /* 128, 128, 128 */
#define EPD_LIGHTGREY 0xC618      /* 192, 192, 192 */
#define EPD_WHITE     0xFFFF
    
// Shared struct(s) for different models
typedef struct {
    uint8_t cmd;
    uint8_t data[159];
    uint8_t databytes;
} epd_lut_159;

typedef struct {
    uint8_t cmd;
    uint8_t data[3];
    uint8_t databytes;
} epd_init_3;

class Gdey027T91 {
    public:
        Gdey027T91(EpdSpi& IO);
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void init(bool debug = false);
        void initFullUpdate();
        void initPartialUpdate();
        void setMonoMode(bool mode);
        void fillScreen(uint16_t color);
        void update();
        // Partial update of rectangle from buffer to screen, does not power off
        void updateWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool using_rotation = true);
        void DrawBitmap(const unsigned char *Image);

    private:
        const uint8_t colors_supported = 1;
        const uint8_t partial_supported = 1;
        bool spi_optimized = true;
        bool m_using_partial_mode;
        bool debug_enabled;
        bool color = false;
        bool m_initial = true;
        bool m_debug_buffer = false;
        bool m_mono_mode = false;
        
        uint8_t m_mono_buffer[GDEY027T91_BUFFER_SIZE];
        uint8_t m_buffer1[GDEY027T91_BUFFER_SIZE];
        uint8_t m_buffer2[GDEY027T91_BUFFER_SIZE];
        
        // Command & data structs
        static const epd_lut_159 lut_4_grays;
        static const epd_init_3 GDOControl;

        EpdSpi& IO;

        uint16_t gx_uint16_min(uint16_t a, uint16_t b);
        uint16_t gx_uint16_max(uint16_t a, uint16_t b);

        void m_setRamDataEntryMode(uint8_t em);
        void m_SetRamArea(uint8_t Xstart, uint8_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);
        void m_SetRamPointer(uint8_t addrX, uint8_t addrY, uint8_t addrY1);
        
        void m_wakeUp4Gray();
        void m_wakeUp(uint8_t em);
        
        void m_PowerOn();
        void m_sleep();
        void m_waitBusy(const char* message, uint16_t busy_time);
        void m_waitBusy(const char* message);
        void m_rotate(uint16_t& x, uint16_t& y, uint16_t& w, uint16_t& h);
};