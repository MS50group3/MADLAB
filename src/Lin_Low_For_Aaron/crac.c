/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include <stdbool.h>

/* definitions */
#define SCREEN_WIDTH  440
#define SCREEN_HEIGHT 418
#define SPRITE_SIZE    32

//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void draw(SDL_Renderer *renderer, SDL_Rect rcSprite, SDL_Rect rcSrc, SDL_Window *window);
void run();

int main(int argc, char **argv)
{
	run();
}

void run()
{
	SDL_Window *window = NULL;
	SDL_Rect rcSprite, rcSrc;
	//SDL_Surface* screenSurface = NULL;

	//JUST CREATE A WINDOW
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "\nUnable to initialise SDL:  %s\n",
						SDL_GetError());
		exit(1);
	}
	else
	{
		window = SDL_CreateWindow ("MADLAB Fuck Yeah!",         //window name
								 SDL_WINDOWPOS_UNDEFINED,       //x-axis on the screen coordinate
								 SDL_WINDOWPOS_UNDEFINED,       //y-axis screen coordinate
								 SCREEN_WIDTH, SCREEN_HEIGHT,   //size of the window
								 SDL_WINDOW_RESIZABLE);         //make the window resizeable       

		if (window == NULL) 
		{
			printf("Could not create window: %s\n", SDL_GetError());
			exit(1);
		}
	}

	// Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// DRAW SOMETHING
	draw(renderer, rcSprite, rcSrc, window);
	
	//atexit(SDL_Quit);
	SDL_Quit();
}


void draw(SDL_Renderer *renderer, SDL_Rect rcSprite, SDL_Rect rcSrc, SDL_Window *window)
{
	SDL_Surface *background, *sprite;
	SDL_Texture *backtex, *spritetex;
	bool gameRunning = true;
	// int colorkey;

	/* making dat dere background */
	background = SDL_LoadBMP("../../gfx/pokemonlab.bmp");
	backtex   = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface (background);

	/* I have created life itself yo */                                                        
	sprite     = SDL_LoadBMP("../../gfx/prof2.bmp");
	spritetex   = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_FreeSurface (sprite);

	/* set sprite "source" position - as called by RenderCopy, choose which to be */
	rcSprite.x = 32;
	rcSprite.y = 0;
	rcSprite.w = SPRITE_SIZE;
	rcSprite.h = SPRITE_SIZE; 

	/* set sprite "destination" position - as called by RenderCopy, choose which to be */
	rcSrc.x = 32;
	rcSrc.y = 0;
	rcSrc.w = SPRITE_SIZE;
	rcSrc.h = SPRITE_SIZE;

	while (gameRunning)
	{
    	SDL_Event event; //call SDL_Event

		if (SDL_PollEvent(&event))  //If there is an event
		{
			//HandleEvent(event, rcSrc, rcSprite); //Run the HandleEvent function
			switch (event.type) 
				{	case SDL_QUIT:
						SDL_Quit();

					case SDL_KEYDOWN:
					switch (event.key.keysym.sym)     
					{
						case SDLK_q:
							gameRunning = false;
						case SDLK_LEFT:
							rcSprite.x -= 5;
							break;
						case SDLK_RIGHT:
							rcSprite.x += 5;
							break;
						case SDLK_UP:
							rcSprite.y -= 5;
							break;
						case SDLK_DOWN:
							rcSprite.y += 5;
							break;
			    	}
			    	break;
				}
		}		

			/* collide with edges of screen */
			if (rcSprite.x <= 0)
				rcSprite.x = 0;
			if (rcSprite.x >= SCREEN_WIDTH - SPRITE_SIZE) 
				rcSprite.x = SCREEN_WIDTH - SPRITE_SIZE;

			if (rcSprite.y <= 0)
				rcSprite.y = 0;
			if (rcSprite.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
				rcSprite.y = SCREEN_HEIGHT - SPRITE_SIZE;

	/* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backtex, NULL, NULL);
	SDL_RenderCopy(renderer, spritetex, &rcSrc, &rcSprite);
	SDL_RenderPresent(renderer);
	}

	//SDL_Delay(5000);
	SDL_DestroyTexture(backtex);
	SDL_DestroyTexture(spritetex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//atexit(SDL_Quit);
}


