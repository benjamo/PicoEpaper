/**
 * @project: RaspberryPi pico w with eInk display
 * 
 * @author: Benjamin Malbrich <benjamin.malbrich@gmail.com>
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <tusb.h>
#include "lib/ePaper/epdspi.h"
#include "lib/ePaper/gdey027t91.h"
#include "logo.h"

int main(void) {

	stdio_init_all();

	uint32_t t0 = time_us_32();
    while (!tud_cdc_connected()) { 
		sleep_ms(100);  
	}
    uint32_t t1 = time_us_32();
    printf("\n%ldus\n", t1 - t0);

	EpdSpi IO;
	Gdey027T91 display(IO);
	display.init();
	display.DrawBitmap(logo);
	display.update();

    return 0;
}
