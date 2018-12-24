#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window *lcddisp;

void create_display(int scale) {
	lcddisp = SDL_CreateWindow(
			"JameBoy",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			160 * scale,
			144 * scale,
			SDL_WINDOW_OPENGL
			);
}

void main() {
	int scale;
	int time;
	scale = 3;
	SDL_Init(SDL_INIT_VIDEO);
	create_display(scale);
	time = SDL_GetTicks();
	SDL_Delay(3000);
	time = SDL_GetTicks() - time;
	SDL_Quit();
	printf("%d\n", time);
}

