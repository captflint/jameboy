#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window *lcddisp;
SDL_Renderer *dispRend;

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
	char pixels[160 * 144];
	int pixelIndex;
	char curPixel;
	int reps;
	SDL_Surface *origScreen;
	SDL_Surface *scaledScreen;
	SDL_Texture *screenTexture;
	SDL_Palette *lcdPalette;
	SDL_Color pixelColors[4];
	pixelIndex = 0;
	curPixel = 0;
	reps = 1;
	scale = 4;
	pixelColors[0] = (SDL_Color){ 255, 255, 255, 255 };
	pixelColors[1] = (SDL_Color){ 170, 170, 170, 255 };
	pixelColors[2] = (SDL_Color){ 85, 85, 85, 255 };
	pixelColors[3] = (SDL_Color){ 0, 0, 0, 255 };
	lcdPalette = SDL_AllocPalette(4);
	SDL_SetPaletteColors(lcdPalette, pixelColors, 0, 4);
	SDL_Init(SDL_INIT_VIDEO);
	create_display(scale);
	while (pixelIndex++ < (160 * 144)) {
		pixels[pixelIndex] = curPixel;
		if (++reps == 8) {
			reps = 0;
			if (++curPixel == 4)
				curPixel = 0;
		}
	}
	pixelIndex = 0;
	scaledScreen = SDL_CreateRGBSurfaceWithFormat(
			0,
			160 * scale,
			144 * scale,
			8,
			SDL_PIXELFORMAT_INDEX8);
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
	SDL_RenderCopy(dispRend, screenTexture, NULL, NULL);
	//SDL_SetRenderDrawColor(dispRend, 255, 0, 0, 255);
	//SDL_RenderClear(dispRend);
	SDL_RenderPresent(dispRend);
	time = SDL_GetTicks();
	SDL_Delay(3000);
	time = SDL_GetTicks() - time;
	SDL_Quit();
	printf("%d\n", time);
}

