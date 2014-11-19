#include "draw.h"

extern void drawRoom(void);

void draw()
{	
	drawRoom();

	SDL_RenderPresent(screen);
		
	SDL_Delay(1);
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}
