#include "lcd.h"
#include "memmap.h"

void ppuTestFunc() {
	for (int i = 0; i < (160 * 144); i++) {
		sendPixel(memmapRead(1337));
	}
}

