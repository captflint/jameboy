#include "lcd.c"

int main() {
	int scale = 4;
	int time = 0;
	int framesRendered = 0;
	SDL_Init(SDL_INIT_VIDEO);
	create_display(scale);
	time = SDL_GetTicks();
	while (framesRendered < 600) {
		if (sendPixel(randomPixel()))
			framesRendered++;
	}
	time = SDL_GetTicks() - time;
	printf("%d frames rendered in %d ms.\n", framesRendered, time);
	for (int r = 0; r < 500; r++) {
		sendPixel(3);
	}
	lcdReset();
	SDL_Delay(2000);
	while (1) {
		for (unsigned char p = 0; p < 4; p++) {
			for (int r = 0; r < 8; r++) {
				if (sendPixel(p))
					goto DONE;
			}
		}
	}
DONE: SDL_Delay(10000);
	SDL_Quit();
	return 0;
}

