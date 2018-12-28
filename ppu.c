#include "lcd.h"
#include "memmap.h"

static unsigned char fifoFirst; //first fifo byte
static unsigned char fifoSecond; //second fifo byte
static int fifo1ppop; //first fifo byte pixel population
static int fifo2ppop; //second fifo byte pixel population

static void pushPixels(unsigned char byte) {
	unsigned char out = 0;
	for (int i = 0; i < 4; i++) {
		out = byte & 0300;
		out = out >> 6;
		sendPixel(out);
		byte = byte << 2;
	}
}

void ppuTestFunc() {
	int pixelsLeft = 160 * 144;
	int tileData = 0x8000;
	int pixelData;
	int line = 0;
	while (pixelsLeft) {
		for (int i = 160; i; i -= 8) {
			pixelData = memmapRead(tileData + line * 2);
			pushPixels(pixelData);
			pixelData = memmapRead(tileData + line * 2 + 1);
			pushPixels(pixelData);
			pixelsLeft -= 8;
		}
		if (++line == 8)
			line = 0;
	}
}

void ppuTick() {
	static int tickCount = 0;
	unsigned char mode;
	mode = memmapRead(0xff41); //ff41 is STAT register
	mode = mode & 3;
	if (mode == 2) {
		if (tickCount == 19) {
			mode = memmapRead(0xff41);
			mode = mode & 252;
			mode = mode | 3;
		}
	}
	if (++tickCount == 114)
		tickCount = 0;
}

