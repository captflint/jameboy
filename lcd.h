#ifndef LCD_H
#define LCD_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char randomPixel();
void create_display(int scale);
int sendPixel(unsigned char pixel);
void lcdReset(void);

#endif
