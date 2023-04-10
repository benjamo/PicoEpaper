#include "epdspi.h"
#include <string.h>

void EpdSpi::init(uint8_t frequency=4, bool debug=false) {
    
    debug_enabled = debug;

    // Enable SPI at given frequency (1 MHz)
    spi_init(EPD_SPI_PORT, frequency * 1000 * 1000);

    gpio_set_function(EPD_PIN_DC, GPIO_FUNC_SPI);
    gpio_set_function(EPD_PIN_CS, GPIO_FUNC_SPI);
    gpio_set_function(EPD_PIN_CLK, GPIO_FUNC_SPI);
    gpio_set_function(EPD_PIN_DIN, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(EPD_PIN_DC);
    gpio_init(EPD_PIN_CS);
    gpio_init(EPD_PIN_RST);

    // Set also clock and data pin to high level
    gpio_set_dir(EPD_PIN_DC, GPIO_OUT);
    gpio_set_dir(EPD_PIN_CS, GPIO_OUT);
    gpio_set_dir(EPD_PIN_DIN, GPIO_OUT);
    gpio_set_dir(EPD_PIN_RST, GPIO_OUT);
    gpio_set_dir(EPD_PIN_BUSY, GPIO_IN);

    gpio_put(EPD_PIN_CS, 1);
    
    if (debug_enabled) {

        printf("init() Debug enabled. SPI master at frequency:%d  MOSI:%d CLK:%d CS:%d DC:%d RST:%d BUSY:%d \n",
        frequency*1000*1000, "mosi", EPD_PIN_CLK, EPD_PIN_CS, EPD_PIN_DC, EPD_PIN_RST, EPD_PIN_BUSY);

    } else {
        printf("started at frequency: %d000", frequency * 1000);
    }
}

/**
 * Send a command to the LCD. Uses spi_device_polling_transmit, which waits
 * until the transfer is complete.
 *
 * Since command transactions are usually small, they are handled in polling
 * mode for higher speed. The overhead of interrupt transactions is more than
 * just waiting for the transaction to complete.
 */
void EpdSpi::cmd(const uint8_t cmd) {

    if (debug_enabled) {
        printf("C %x", cmd);
    } 

    gpio_put(EPD_PIN_DC, 0);
    gpio_put(EPD_PIN_CS, 0);
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(EPD_PIN_CS, 1);
    
}

/**
 * Send data commands
 * 
 * @param uint8_t data
 * 
 * @return void
*/
void EpdSpi::data(uint8_t data) {

    if (debug_enabled) {
        printf("D %x", data);
    }

    gpio_put(EPD_PIN_DC, 1);
    gpio_put(EPD_PIN_CS, 0);
    spi_write_blocking(spi0, &data, 1);
    gpio_put(EPD_PIN_CS, 1);

}

/**
 * data buffer
 * 
 * @param uint8_t data
 * 
 * @return void
*/
void EpdSpi::dataBuffer(uint8_t data) {

    /*
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&data;
    spi_device_polling_transmit(spi, &t);
    */
}

/**
 * Send data to the SPI. Uses spi_device_polling_transmit, which waits until the
 * transfer is complete.
 *
 * Since data transactions are usually small, they are handled in polling
 * mode for higher speed. The overhead of interrupt transactions is more than
 * just waiting for the transaction to complete.
 */
void EpdSpi::data(const uint8_t *data, int len) {

    if (len == 0) {
        return;
    } 

    if (debug_enabled) {
        printf("D");
        for (int i = 0; i < len; i++)  {
            printf("%x ", data[i]);
        }
    }
    
    gpio_put(EPD_PIN_DC, 1);
    gpio_put(EPD_PIN_CS, 0);
    spi_write_blocking(spi0, data, len);
    gpio_put(EPD_PIN_CS, 1);
    
}

/**
 * reset
 * 
 * @param uint8_t millis
 * 
 * @return void
*/
void EpdSpi::reset(uint8_t millis = 20) {

    gpio_put(EPD_PIN_RST, 1);
    sleep_ms(millis);
    gpio_put(EPD_PIN_RST, 0);
    sleep_ms(millis);
    gpio_put(EPD_PIN_RST, 1);
    sleep_ms(millis);

}
