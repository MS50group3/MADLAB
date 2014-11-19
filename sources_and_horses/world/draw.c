#include "draw.h"

extern void drawMap(void);

void draw()
{
	/* Draw the map */
	
	drawMap();

	/* Swap the buffers */

	SDL_Flip(screen);
	
	/* Sleep briefly */
	
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
