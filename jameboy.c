#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *lcddisp;
static SDL_Renderer *dispRend;
static SDL_Palette *lcdPalette;

static unsigned char randomPixel() {
	long int ri;
	unsigned char rpixel;
	ri = random();
	rpixel = (unsigned char)ri;
	rpixel = rpixel & 3;
	return rpixel;
}

void create_display(int scale) {
	SDL_Color pixelColors[4];
	lcddisp = SDL_CreateWindow(
			"JameBoy",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			160 * scale,
			144 * scale,
			SDL_WINDOW_OPENGL
			);
	dispRend = SDL_CreateRenderer(lcddisp, -1, SDL_RENDERER_ACCELERATED);
	pixelColors[0] = (SDL_Color){ 255, 255, 255, 255 };
	pixelColors[1] = (SDL_Color){ 170, 170, 170, 255 };
	pixelColors[2] = (SDL_Color){ 85, 85, 85, 255 };
	pixelColors[3] = (SDL_Color){ 0, 0, 0, 255 };
	lcdPalette = SDL_AllocPalette(4);
	SDL_SetPaletteColors(lcdPalette, pixelColors, 0, 4);
}

static void updateScreen(unsigned char pixels[]) {
	SDL_Surface *lcdSurface;
	SDL_Texture *lcdTexture;
	lcdSurface = SDL_CreateRGBSurfaceWithFormatFrom(
			pixels,
			160,
			144,
			8,
			160,
			SDL_PIXELFORMAT_INDEX8);
	SDL_SetSurfacePalette(lcdSurface, lcdPalette);
	lcdTexture = SDL_CreateTextureFromSurface(
			dispRend,
			lcdSurface);
	SDL_FreeSurface(lcdSurface);
	SDL_RenderCopy(dispRend, lcdTexture, NULL, NULL);
	SDL_DestroyTexture(lcdTexture);
	SDL_RenderPresent(dispRend);
}

int sendPixel(unsigned char pixel) {
	static unsigned char pixels[160 * 144];
	static int pixelIndex = 0;
	pixels[pixelIndex] = pixel;
	if (++pixelIndex == (160 * 144)) {
		updateScreen(pixels);
		pixelIndex = 0;
		return 1;
	} else {
		return 0;
	}
}

int main() {
	int scale;
	int time;
	int framesRendered;
	scale = 4;
	framesRendered = 0;
	SDL_Init(SDL_INIT_VIDEO);
	create_display(scale);
	time = SDL_GetTicks();
	while (framesRendered < 600) {
		if (sendPixel(randomPixel()))
			framesRendered++;
	}
	time = SDL_GetTicks() - time;
	printf("%d frames rendered in %d ms.\n", framesRendered, time);
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

