/**
 * @project: RaspberryPi pico w with eInk display
 * 
 * @author: Benjamin Malbrich <benjamin.malbrich@gmail.com>
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/ePaper/epdspi.h"
#include "lib/ePaper/gdey027t91.h"
#include "logo.h"

int main(void) {

	stdio_init_all();
	EpdSpi IO;
	Gdey027T91 display(IO);
	display.init();
	display.DrawBitmap(logo);
	display.update();
	
    return 0;
}
