#include "init.h"

void init(char *title)
{
	/* Initialise SDL Video and Audio */
	
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		
		exit(1);
	}
	
	/* Open a 640 x 480 screen */
	
	screen = SDL_SetVideoMode(640, 480, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);
	
	if (screen == NULL)
	{
		printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());

		exit(1);
	}
	
	/* Set the screen title */
	
	SDL_WM_SetCaption(title, NULL);
	
	/* Hide the mouse cursor */
	
	SDL_ShowCursor(SDL_DISABLE);
}

void cleanup()
{
	/* Free the brick image */
	
	if (brickImage != NULL)
	{
		SDL_FreeSurface(brickImage);
	}
	
	/* Free the brick image */
	
	if (backgroundImage != NULL)
	{
		SDL_FreeSurface(backgroundImage);
	}
	
	/* Shut down SDL */
	
	SDL_Quit();
}
