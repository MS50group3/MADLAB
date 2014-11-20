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

   if( TTF_Init() != 0 ){
    fprintf(stderr, "\nUnable to initialize TTF.\n");
    SDL_Quit();
    exit(1);
   }

   //Set screen to black
   James_SDL_SetDrawColour(sw, 0, 0, 0);    //Sets colour to black.
   SDL_RenderClear(sw->renderer);           //Clears the screen of all rendered objects.
   SDL_RenderPresent(sw->renderer);         //Updates the screen with the objects.

}

// Trivial wrapper to avoid complexities of renderer & alpha channels
void James_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b)
{

   SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);

}

//Looks for an action on the screen when the cut scene is playing.
void look_for_action(int *refresh_counter, SDL_Simplewin *sw, int *skip_checker)
{
  do{
    ++(*refresh_counter);
    SDL_Delay(SLEEP_TIME);
    SDL_QuitChecker(sw, skip_checker);
  }while( *refresh_counter < NUM_REFRESHES && !*skip_checker);
}

//Checks to see if anyone has quit and if so exits the program.
void SDL_QuitChecker(SDL_Simplewin *sw, int *skip_checker)
{
  James_SDL_Events(sw, skip_checker);
  if(sw->finished){
    exit(1);
  }
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

//Used to print sets of instructions to the screen.
void print_text(SDL_Simplewin *sw, char *instruction)
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

//Just a list of instructions to be printed.
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS])
{
  //First block of instructions
  instructions_list[0] = "fan_on_wall";
  instructions_list[1] = "cool_down_room";
  instructions_list[2] = "control_panel";
  instructions_list[3] = "neill_notes";
  instructions_list[4] = "change_temp";

  //Second block of instructions
  instructions_list[5] = "that_worked";
  instructions_list[6] = "room_cooling";
}

//Used to read in and print out the person's input.
void input_screen(SDL_Simplewin *sw, wrong_right *correct_indicator)
{
    SDL_Texture* image, *image_one;
    SDL_Surface *text, *text_one;
    SDL_Rect drcrect;
    char input_string[MAX_INPUT_CHARS], possible_answer[MAX_INPUT_CHARS];
    int input_index = 0, finish_checker = 0;

    //clear_screen(sw);
    initialise_input_string(input_string);
    initialise_drcrect(&drcrect, input_index);

    text_one = SDL_LoadBMP( "Instructions/code_entry.bmp" );
    if( text_one == NULL )
    {
      printf( "Unable to load image %s! SDL Error: %s\n", "bla", SDL_GetError() );
    }

    image_one = SDL_CreateTextureFromSurface(sw->renderer, text_one);
    TTF_Font *font = TTF_OpenFont("basictitlefont.ttf", 200);
    SDL_Color fg = { 255, 255, 255, 255 };

    do{

        check_user_variable_input(sw, input_string, &input_index, &finish_checker);

        text = TTF_RenderText_Solid(font, input_string, fg) ;
        image = SDL_CreateTextureFromSurface(sw->renderer, text);

        SDL_RenderClear(sw->renderer);
        SDL_RenderCopy(sw->renderer, image_one, NULL, NULL);
        SDL_RenderCopy(sw->renderer, image, NULL, &drcrect);
        SDL_RenderPresent(sw->renderer);

    }while(input_index < MAX_INPUT_CHARS && !finish_checker);

    create_answer_for_checking(possible_answer, input_string);

    if( strcmp(possible_answer, "fan < too hot") == 0){
        *correct_indicator = correct;
    }
}

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS])
{
  int i;

  for(i = 0; i < 13; ++i){
        possible_answer[i] = input_string[i];
    }

  possible_answer[13] = '\0';
}

void initialise_input_string(char input_string[MAX_INPUT_CHARS])
{
  int i;

  for(i = 0; i < MAX_INPUT_CHARS; ++i){
        input_string[i] = ' ';
    }
}

void initialise_drcrect(SDL_Rect *drcrect, int input_index)
{
  drcrect->x = 200;
  drcrect->y = 100;
  drcrect->w = 400 * (input_index + 1);
  drcrect->h = 70;
}

void check_user_variable_input(SDL_Simplewin *sw, char *input_string, int *input_index, int *finish_checker)
{
  //To identify event.
  SDL_Event event;

  int gameover = 0;

  while (gameover != INPUT_FINISHED){                                                                 //to make screen stay on.
    while( SDL_PollEvent( &event ) ){                                                                 //checks for events.
      if(event.type == SDL_KEYDOWN){                                                                  //checks for key being pressed
        char c = event.key.keysym.sym;                                                              //if the key is pressed assigns character
        if( (c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) ){
              if(c == ','){
                input_string[*input_index] = '<';
              }
              else if(c == '.'){
                input_string[*input_index] = '>';
              }
              else{
                input_string[*input_index] = c;
              }                                                                                     //puts all pressed characters in an array.
              ++(*input_index);                                                                     //adds one to the index.
              gameover = INPUT_FINISHED;
        }
        else if( c == '\b'){
          input_string[--(*input_index)] = ' ';
          gameover = INPUT_FINISHED; 
        }
        else if(c == '\r'){
          *finish_checker = 1;
          gameover = INPUT_FINISHED; 
        }
      }
    }
  }              

  input_string[MAX_INPUT_CHARS] = '\0';                                                               //concludes string

}

void clear_screen(SDL_Simplewin *sw)
{
  James_SDL_SetDrawColour(sw, 0, 0, 0);    //Sets colour to black.
  SDL_RenderClear(sw->renderer);           //Clears the screen of all rendered objects.
  SDL_RenderPresent(sw->renderer);         //Updates the screen with the objects.
}