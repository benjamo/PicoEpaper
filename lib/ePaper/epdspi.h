/**
 * EPaper SPI communication
 * 
*/
#pragma once

#include <vector>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include <stdio.h>

/**
 * GPIO config
**/
#define EPD_PIN_DIN 3  // SPI MOSI
#define EPD_PIN_CLK 2  // SPI SCK
#define EPD_PIN_CS 1   // SPI chip select (Low active)
#define EPD_PIN_DC 6   // Data/Command control pin (High for data, and low for command)
#define EPD_PIN_RST 4  // External reset pin (Low for reset)
#define EPD_PIN_BUSY 7 // Busy state output pin (Low for busy)

#define EPD_SPI_PORT spi0

class EpdSpi {
    public:
        void cmd(const uint8_t cmd);
        void data(uint8_t data) ;
        void dataBuffer(uint8_t data);
        void data(const uint8_t *data, int len);
        // Deprecated
        void reset(uint8_t millis);
        void init(uint8_t frequency, bool debug);

    private:
        bool debug_enabled = true;
};
