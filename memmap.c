static unsigned char memory[65536];

unsigned char memmapRead(int addr) {
	if (addr < 65536) {
		return memory[addr];
	} else {
		return 255;
	}
}

void memmapWrite(int addr, unsigned char byte) {
	if (addr < 65536) {
		memory[addr] = byte;
	}
}

