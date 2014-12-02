/*
 * Interaction_Functions.c
 *
 *  Created on: 7 Nov 2014
 *      Author: James
 */

#include "Interaction_Functions.h"
#include <SDL.h>

void James_SDL_Init(SDL_Simplewin *sw)
{

  //Sets up windows and checks to make sure it's set up.
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   //Puts the finished part of the structure to zero.
   sw->finished = 0;

   //Makes the window and checks it using the #defined width and height.
   sw->win= SDL_CreateWindow("Interaction Demo",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WINDOW_WIDTH, WINDOW_HEIGHT,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   //This is added in to create a surface to push .bmp files onto.
   sw->surface = SDL_GetWindowSurface(sw->win);

   //Creates a renderable surface for any pixel drawing/ screen filling.
   sw->renderer = SDL_CreateRenderer(sw->win, -1, 0);
   if(sw->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   //Set screen to black
   James_SDL_SetDrawColour(sw, 0, 0, 0);    //Sets colour to black.
   SDL_RenderClear(sw->renderer);           //Clears the screen of all rendered objects.
   SDL_RenderPresent(sw->renderer);         //Updates the screen with the objects.

}

// Gobble all events & ignore most
void James_SDL_Events(SDL_Simplewin *sw, int *skip_checker)
{
   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
       switch (event.type){
          case SDL_QUIT:
          sw->finished = 1;
          case SDL_MOUSEBUTTONDOWN:
          case SDL_KEYDOWN:
            *skip_checker = 1;
       }
    }
}


// Trivial wrapper to avoid complexities of renderer & alpha channels
void James_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b)
{

   SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);

}

//Used to print sets of instructions to the screen.
void print_some_text(SDL_Simplewin *sw, char *instruction)
{
  int refresh_counter = 0, skip_checker = 0;
	SDL_Surface* text_one = NULL;
  SDL_Texture* image;

	//The following few lines are used to create a filename to get the .bmp to print to screen.
	char prefix[LENGTH_PREFIX] = "Instructions/";
	char extension[LENGTH_EXTENSION] = ".bmp";
	char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension));

	strcpy(filename, prefix);
	strcat(filename, instruction);
	strcat(filename, extension);

	//Loads image in and checks it.
	text_one = SDL_LoadBMP( filename );
  image = SDL_CreateTextureFromSurface(sw->renderer,text_one);

	if( text_one == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError() );
	}

	//Update the surface and apply the image.
	SDL_RenderCopy(sw->renderer, image, NULL, NULL);
  SDL_RenderPresent(sw->renderer);

	//Wait the sleep time and free the malloc for the filename.
  look_for_action(&refresh_counter, sw, &skip_checker);

	free(filename);
}

void look_for_action(int *refresh_counter, SDL_Simplewin *sw, int *skip_checker)
{
  do{
    ++(*refresh_counter);
    SDL_Delay(SLEEP_TIME);
    SDL_QuitChecker(sw, skip_checker);
  }while( *refresh_counter < NUM_REFRESHES && !*skip_checker);
}

void SDL_QuitChecker(SDL_Simplewin *sw, int *skip_checker)
{
  James_SDL_Events(sw, skip_checker);
  if(sw->finished){
    exit(1);
  }
}

//Just a list of instructions to be printed.
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS])
{
	instructions_list[0] = "MadLab";
	instructions_list[1] = "Where_am_I";
	instructions_list[2] = "looks_like";
	instructions_list[3] = "door_locked";
	instructions_list[4] = "shenanigans";
	instructions_list[5] = "neill_shenanigans";
	instructions_list[6] = "maybe_if_I";
	instructions_list[7] = "press_spacebar";
	instructions_list[8] = "find_neill";
	instructions_list[9] = "lets_go";
}
