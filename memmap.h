#ifndef MEMMAP_H
#define MEMMAP_H

unsigned char memmapRead(unsigned int addr);
void memmapWrite(unsigned int addr, unsigned char byte);

#endif
