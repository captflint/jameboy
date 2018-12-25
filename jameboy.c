#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window *lcddisp;
SDL_Renderer *dispRend;

unsigned char randomPixel() {
	long int ri;
	unsigned char rpixel;
	ri = random();
	rpixel = (unsigned char)ri;
	rpixel = rpixel & 3;
	return rpixel;
}

void create_display(int scale) {
	lcddisp = SDL_CreateWindow(
			"JameBoy",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			160 * scale,
			144 * scale,
			SDL_WINDOW_OPENGL
			);
	dispRend = SDL_CreateRenderer(lcddisp, -1, SDL_RENDERER_ACCELERATED);
}

void main() {
	int scale;
	int time;
	unsigned char pixels[160 * 144];
	int pixelIndex;
	int framesRendered;
	SDL_Surface *origScreen;
	SDL_Texture *screenTexture;
	SDL_Palette *lcdPalette;
	SDL_Color pixelColors[4];
	pixelIndex = 0;
	scale = 4;
	framesRendered = 0;
	pixelColors[0] = (SDL_Color){ 255, 255, 255, 255 };
	pixelColors[1] = (SDL_Color){ 170, 170, 170, 255 };
	pixelColors[2] = (SDL_Color){ 85, 85, 85, 255 };
	pixelColors[3] = (SDL_Color){ 0, 0, 0, 255 };
	lcdPalette = SDL_AllocPalette(4);
	SDL_SetPaletteColors(lcdPalette, pixelColors, 0, 4);
	SDL_Init(SDL_INIT_VIDEO);
	create_display(scale);
	time = SDL_GetTicks();
	while (framesRendered++ < 60000) {
		while (pixelIndex < (160 * 144)) {
			pixels[pixelIndex++] = randomPixel();
		}
		pixelIndex = 0;
		origScreen = SDL_CreateRGBSurfaceWithFormatFrom(
				pixels,
				160,
				140,
				8,
				160,
				SDL_PIXELFORMAT_INDEX8);
		SDL_SetSurfacePalette(origScreen, lcdPalette);
		screenTexture = SDL_CreateTextureFromSurface(
				dispRend,
				origScreen);
		SDL_FreeSurface(origScreen);
		SDL_RenderCopy(dispRend, screenTexture, NULL, NULL);
		SDL_DestroyTexture(screenTexture);
		SDL_RenderPresent(dispRend);
	}
	time = SDL_GetTicks() - time;
	SDL_Quit();
	printf("%d frames rendered in %d ms.\n", framesRendered - 1, time);
}

