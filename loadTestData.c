#include "memmap.h"

void loadPPUtestData() {
	memmapWrite(0xff47, 0344); //set bg palette

	//write a tile to tile data map
	memmapWrite(0x8000, 0377);
	memmapWrite(0x8001, 0377);
	memmapWrite(0x8002, 0352);
	memmapWrite(0x8003, 0253);
	memmapWrite(0x8004, 0345);
	memmapWrite(0x8005, 0133);
	memmapWrite(0x8006, 0344);
	memmapWrite(0x8007, 0033);
	memmapWrite(0x8008, 0344);
	memmapWrite(0x8009, 0033);
	memmapWrite(0x800a, 0345);
	memmapWrite(0x800b, 0133);
	memmapWrite(0x800c, 0352);
	memmapWrite(0x800d, 0253);
	memmapWrite(0x800e, 0377);
	memmapWrite(0x800f, 0377);

	//write bg map data
	for (int a = 0x9800; a < 0x9c00; a++) {
		memmapWrite(a, 0);
	}
}

