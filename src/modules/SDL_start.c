
 /**********************************
 *          The SDL Module         *
 *                                 *
 * This module controls everything *
 *     about graphics and sound    *
 **********************************/

/* headers */
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer>
#include <SDL2/SDL_image>

/* definitions */
#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    640

 typedef struct SDL{
   SDL_bool finished;
   SDL_Window   *window;
   SDL_Texture  *texture;
   SDL_Renderer *renderer;
   SDL_Surface  *surface;
};SDL;

void SDL_start()
{
  SDL_Window *window = NULL;
  bool success = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  //test that SDL init'd properly
  {
    fprintf(stderr, "\nUnable to initialise SDL:  %s\n", SDL_GetError()); //if not, there is an error message
    exit(1);
  }
  else
  {
    window = SDL_CreateWindow ("MADLAB!",                    //window name
                                SDL_WINDOWPOS_UNDEFINED,     //x-axis on the screen coordinate
                                SDL_WINDOWPOS_UNDEFINED,     //y-axis screen coordinate
                                SCREEN_WIDTH, SCREEN_HEIGHT, //size of the window
                                SDL_WINDOW_SHOWN);
  
  }

  if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  //initialise PNG loading 
  { 
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); success = false; //test and error message
    printf("%d", success);
  }

  if(!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG))  //initialise .ogg file loading
  { 
    printf("Mix_Init could not initialise! You are in trouble! Errors!\n");                            //test and error message
    exit(1);
  }

  // Setup audio mode
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_U16SYS, 2, 4096);
  /*if) == -1 )
  {
    success = false;    
  }*/
  Mix_Music *mus;                    //Background Music 
  mus = Mix_LoadMUS("acdc.ogg");     //load the file and create a pointer
  Mix_PlayMusic(mus,0);              //Music loop=1


  //when its time to quit do the following
  atexit(SDL_Quit);
  IMG_Quit();
  Mix_HaltMusic(); 
  Mix_FreeMusic(mus); 
  Mix_CloseAudio();  
  Mix_Quit();
  SDL_Quit();

}
