/* test to draw individual rooms */

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

/* definitions */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 640
#define TILE_SIZE      32
#define ROOM_X         25
#define ROOM_Y         24
#define OPEN            0

typedef struct roomGrid
{
  int **arr;
  SDL_Rect rc_block, rcSrc;
}roomGrid;

int  mapTiles [100][100];

//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg);
void draw(SDL_Renderer *renderer, SDL_Rect rc_block, SDL_Rect rcSrc, SDL_Window *window, roomGrid *rg);
void run(roomGrid *rg);

int main(int argc, char *argv[])
{
  roomGrid roomStuff, *rg;
  rg = &roomStuff;
  FILE *fp = NULL;
  fp = fopen(argv[1], "r");

  if (fp == NULL)
  {
    printf("File could not be opened.\n");
    exit(1);
  }
  printf("File was successfully opened.\n");

  makeRoom(rg, fp);
  fclose(fp);

  run(rg);
  printArray(rg);

  return 0;
}

/* make space for the array for the room */
void makeRoom(roomGrid *rg, FILE *fp)
{
  rg -> arr = 0;

  rg -> arr = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
  if (rg -> arr == NULL)
  {
    fprintf(stderr, "No memory available.\n");
    exit(3);
  }

  for(int i = 0; i <= ROOM_Y; i++)
  {
    rg -> arr[i] = (int *)calloc((ROOM_X)+1, sizeof(int));
    if (rg -> arr[i] ==  NULL)
    {
      fprintf(stderr, "No memory available.\n");
      exit(4);
    }
  }

  /* reading in the blocking file */
  for (int i = 0; i < ROOM_Y; i++)
  {
    for (int j = 0; j < ROOM_X; j++)
    {
      fscanf(fp, "%1d", &rg -> arr[i][j]);
    }
  }

  /*for (int x = 0; x < ROOM_X; x++)
  {
    for (int y = 0; y < ROOM_Y; y++)
    {
      mapTiles[x][y]
    }
  }*/

  /* test print */
  for (int i = 0; i < ROOM_Y; i++)
  {
    for (int j = 0; j < ROOM_X; j++)
    {
      printf("%2d", rg -> arr[i][j]);
    }
    printf("\n");
  }
}

void run(roomGrid *rg)
{
  SDL_Window *window = NULL;
  SDL_Rect rc_block, rcSrc;
  bool success = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  //SDL returns a 0 if successful, so if not
  {
    fprintf(stderr, "\nUnable to initialise SDL:  %s\n", SDL_GetError());
    exit(1);                               //get out of there!
  }
    else
    {
      window = SDL_CreateWindow ("MADLAB Fuck Yeah!",          //window name
                                  SDL_WINDOWPOS_UNDEFINED,     //x-axis on the screen coordinate
                                  SDL_WINDOWPOS_UNDEFINED,     //y-axis screen coordinate
                                  SCREEN_WIDTH, SCREEN_HEIGHT, //size of the window
                                  SDL_WINDOW_RESIZABLE);       //make the window resizeable 
                                                      
      if (window == NULL) //if the window is not created...
      {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);          //...bail
      }
    }

  //Initialise PNG loading
  if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //test that it actually works
  { 
    printf( "SDL_image could not initialise! SDL_image Error: %s\n", 
    IMG_GetError()); success = false; 
    printf("%d", success);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  draw(renderer, rc_block, rcSrc, window, rg);
  atexit(SDL_Quit);

  IMG_Quit();
  SDL_Quit();
}

void draw(SDL_Renderer *renderer, SDL_Rect rc_block, SDL_Rect rcSrc,  SDL_Window *window, roomGrid *rg)
{
  SDL_Surface *background;
  SDL_Texture *backtex;
  bool gameRunning = true;

  /* loading giant png file */
  background = IMG_Load("test_array.png");
  backtex = SDL_CreateTextureFromSurface(renderer, background);
  SDL_FreeSurface (background);

    /* set animation frame */
  rg -> rc_block.w = TILE_SIZE;
  rg -> rc_block.h = TILE_SIZE;

  rcSrc.w = TILE_SIZE;
  rcSrc.h = TILE_SIZE;

  while (gameRunning)
  {
    SDL_Event event;                         //call SDL_Event
    if (SDL_PollEvent(&event))               //if there is an event
    {              
     //HandleEvent(event, rcSrc, rcSprite);  //Run the HandleEvent function
      switch (event.type)
      {
        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_q:
            gameRunning = false;
            break;
        }
      }
    }       

   SDL_RenderClear(renderer);

   for (int i = 0; i < ROOM_Y; i++)
    {
      for (int j = 0; j < ROOM_X; j++)
      {
        rg -> rc_block.x = (j * TILE_SIZE); //set the array location to the tile size and block size
        rg -> rc_block.y = (i * TILE_SIZE);

        if (rg -> arr[i][j] == 1)
        { 
          rcSrc.x = 0;
          rcSrc.y = 0;
         SDL_RenderCopy(renderer, backtex, &rcSrc, &rg -> rc_block);
        }
        if (rg -> arr[i][j] == 0)
        {
          rcSrc.x = 32;
          rcSrc.y = 0;
          SDL_RenderCopy(renderer, backtex, &rcSrc, &rg -> rc_block);
          //SDL_RenderCopy(renderer, backtex, NULL, NULL);
        }
        if (rg -> arr[i][j] == 2)
        {
          rcSrc.x = 64;
          rcSrc.y = 0;
          SDL_RenderCopy(renderer, backtex, &rcSrc, &rg -> rc_block);
        }
      }
    }
   
    /* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
    //SDL_RenderCopy(renderer, backtex, NULL, NULL);
    SDL_RenderPresent(renderer);

  }//end of the while loop

  SDL_DestroyTexture(backtex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

/*prints the array*/
void printArray(roomGrid *rg)
{
  for (int i = 0; i < ROOM_Y; i++)
  {
    for (int j = 0; j < ROOM_X; j++)
    {
      printf("%2d", rg -> arr[i][j]);
    }
    printf("\n");
  }
}