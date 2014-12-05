/*
init_SDL.c
This handles the opening and closing of SDL
* Still needs to be tested for error cases*
 */

#include "init.h"

void init()
{
	SDL_Window *window         = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "\nUnable to initialise SDL:  %s\n", SDL_GetError());
		exit(1);
	}else{
		window = SDL_CreateWindow ("MADLAB",                      //window name
								    SDL_WINDOWPOS_UNDEFINED,      //x-axis on the screen coordinate
								    SDL_WINDOWPOS_UNDEFINED,      //y-axis screen coordinate
								    SCREEN_WIDTH, SCREEN_HEIGHT,  //size of the window
								    SDL_WINDOW_RESIZABLE);        //make the window resizeable       

		if (window == NULL){
			printf("Error creating window: %s\n", SDL_GetError());
			exit(1);
		}
	}
}

void shut_down()
{
  /*itextures must be destroyed before closing*/
  SDL_DestroyTexture(background_tex); //renames needed!
  SDL_DestroyTexture(sprite_tex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
	
  /*aaaaand...quit*/ 
  SDL_Quit();
}

