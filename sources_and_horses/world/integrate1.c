/**************************************
*  World & First Problem Integration  *
*		       1 Dec 2014             *
**************************************/

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* definitions */
#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    640
#define TILE_SIZE         32
#define ROOM_X            25
#define ROOM_Y            20
#define SPRITE_VEL         5
#define SDL_8BITCOLOUR   256
#define SLEEP_TIME       100
#define NUM_INSTRUCTIONS  10
#define LENGTH_EXTENSION   5
#define LENGTH_PREFIX     14
#define NUM_REFRESHES     50

/* structures */

// All info required for windows / renderer & event loop
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Surface *surface;
};
typedef struct SDL_Simplewin SDL_Simplewin;

typedef enum compass{up = 0, right = 1, down = 2, left = 3/*, space = 4*/}compass;

typedef enum tileType{path = 0, obstacle = 1, puz_1 = 2, puz_2 = 3, puz_3 = 4, puz_4 = 5, puz_5 = 6}tileType;

typedef struct roomGrid
{
	int **arr;
	compass direction;
	SDL_Rect rcSprite, rcSrc1, rcSrc2, rcSrc3, rc_Block;
	int xa;
	int xb;
	int yb;
	int ya;
	int xc;
	int yc;
	int vertd;
	int probe;
}roomGrid;

typedef struct progress
{	
	bool puzzle_1;
	bool puzzle_2;
	bool puzzle_3;
	bool puzzle_4;
	bool puzzle_5;
}progress;

/* prototypes */

void James_SDL_Init(SDL_Simplewin *sw);
void James_SDL_Events(SDL_Simplewin *sw, int *skip_checker);
void James_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void print_some_text(SDL_Simplewin *sw, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);
void look_for_action(int *refresh_counter, SDL_Simplewin *sw, int *skip_checker);
void SDL_QuitChecker(SDL_Simplewin *sw, int *skip_checker);

//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg, progress *pz);
void draw(SDL_Renderer *renderer, SDL_Window *window, roomGrid *rg, progress *pz);
void run(roomGrid *rg, progress *pz);
void freeArray(roomGrid *rg);
void possible(roomGrid *rg, progress *pz);
int action(roomGrid *rg, progress *pz);
void interactProbe(roomGrid *rg, progress *pz);
void James_Shit(SDL_Simplewin *sw);

int main(int argc, char *argv[])
{
	roomGrid roomStuff, *rg;
	rg = &roomStuff;

	progress puzzlesolved, *pz;
	pz = &puzzlesolved;

	FILE *fp = NULL;
	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("File could not be opened.\n");
		exit(1);
	}
	printf("File was opened.\n");

	makeRoom(rg, fp);
	fclose(fp);

	run(rg, pz);
	printArray(rg, pz);
	//freeArray(rg);

	return 0;
}

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
                         SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   //This is added in to create a surface to push .bmp files onto.
   sw->surface = SDL_GetWindowSurface(sw->win);

   //Creates a renderable surface for any pixel drawing/ screen filling.
   sw->renderer = SDL_GetRenderer(sw->win);
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

	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			fscanf(fp, "%1d", &rg -> arr[i][j]);
			/*else
			{
				fprintf(stderr, "Invalid array size.\n");
				exit(5);
			}*/
		}
	}
}


void run(roomGrid *rg, progress *pz)
{
	bool success = true;
/*	SDL_Window *window = NULL;
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "\nUnable to initialise SDL:  %s\n",
						SDL_GetError());
		exit(1);
	}
	else
	{
		window = SDL_CreateWindow ("MADLAB 0.0.1!",         //window name
								 SDL_WINDOWPOS_UNDEFINED,       //x-axis on the screen coordinate
								 SDL_WINDOWPOS_UNDEFINED,       //y-axis screen coordinate
								 SCREEN_WIDTH, SCREEN_HEIGHT,   //size of the window
								 SDL_WINDOW_RESIZABLE);         //make the window resizeable       

		if (window == NULL) 
		{
			printf("Could not create window: %s\n", SDL_GetError());
			exit(1);
		}
	}*/

	SDL_Simplewin sw; 
	James_SDL_Init(&sw);

	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //Initialize PNG loading ; 
		{ 
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); success = false; 
			printf("%d", success);
		}

	//sw.renderer = SDL_CreateRenderer(sw.win, -1, SDL_RENDERER_ACCELERATED);
	James_Shit(&sw);
	draw(sw.renderer, sw.win, rg, pz);
	atexit(SDL_Quit);
	IMG_Quit();
	SDL_Quit();
}

void James_Shit(SDL_Simplewin *sw)
{
	//List of instructions to be used for printing.
	char *instructions_list[NUM_INSTRUCTIONS];

	//Used for looping through the instructions.
	int i;

	get_instructions(instructions_list);

	for(i = 0; i < NUM_INSTRUCTIONS; ++i){
		print_some_text(sw, instructions_list[i]);
	}

}

void draw(SDL_Renderer *renderer, SDL_Window *window, roomGrid *rg, progress *pz)
{
	SDL_Surface *background, *sprite;
	SDL_Texture *backtex, *spritetex;
	bool gameRunning = true;
	rg -> xa = 0;
	rg -> yb = 0;
	rg -> ya = 0;
	rg -> vertd = 0;
	rg -> direction = 0;
	pz -> puzzle_1 = false;
	//int i = 0, j =0;
	// int colorkey;

	/* making dat dere background */
	background = IMG_Load("test_array.png");
	backtex = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface (background);

	/* I have created life itself yo */                                                        
	sprite = SDL_LoadBMP("prof2.bmp");
	spritetex = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_FreeSurface (sprite);

	/* set sprite "source" position - as called by RenderCopy, choose which to be */
 	rg -> rcSprite.y = 32;
 	rg -> rcSprite.x = 0;
	rg -> rcSprite.w = TILE_SIZE;
	rg -> rcSprite.h = TILE_SIZE; 

	/* set sprite "destination" position - as called by RenderCopy, choose which to be */
	rg -> rcSrc1.x = 0;
	rg -> rcSrc1.y = 0;
	rg -> rcSrc1.w = TILE_SIZE;
	rg -> rcSrc1.h = TILE_SIZE;
	rg -> rcSrc2.x = 32;
	rg -> rcSrc2.y = 0;
	rg -> rcSrc2.w = TILE_SIZE;
	rg -> rcSrc2.h = TILE_SIZE;
	rg -> rcSrc3.x = 64;
	rg -> rcSrc3.y = 0;
	rg -> rcSrc3.w = TILE_SIZE;
	rg -> rcSrc3.h = TILE_SIZE;


	rg -> rc_Block.w = TILE_SIZE;
	rg -> rc_Block.h = TILE_SIZE;


	while (gameRunning)
	{
    	SDL_Event event; //call SDL_Event

		if (SDL_PollEvent(&event))  //If there is an event
		{
			// HandleEvent(event, rcSrc, rcSprite); //Run the HandleEvent function
			switch (event.type) 
			{
				case SDL_KEYDOWN:
				switch (event.key.keysym.sym)     
				{
					case SDLK_q:
						gameRunning = false;
						break;
					case SDLK_LEFT:
						rg -> direction = left;
						if (!((rg -> rcSprite.x) % TILE_SIZE))
						{
							possible(rg, pz);
						}
						 else
						{
						 	rg -> rcSprite.x -= 8;
						}
						break;
					case SDLK_RIGHT:
						rg -> direction = right;
						if (!((rg -> rcSprite.x) % TILE_SIZE))
						{
							possible(rg, pz);
						}
						else
						{
							rg -> rcSprite.x += 8;
						}
						break;
					case SDLK_UP:
						rg -> direction = up;
						if (!((rg -> rcSprite.y) % TILE_SIZE))
						{
							possible(rg, pz);
						}
						else
						{
							rg -> rcSprite.y -= 8;
						}
						break;
					case SDLK_DOWN:
						rg -> direction = down;
						if (!((rg -> rcSprite.y) % TILE_SIZE))
						{
							possible(rg, pz);
						}
						else
						{
							rg -> rcSprite.y += 8;
						}
						break;
					case SDLK_SPACE:
						interactProbe(rg, pz); 
						if (rg -> arr[rg->rcSprite.y][rg->rcSprite.x] == 9)
						{
							printf("Things are working\n");
						}
						break;
		    	}
		    	break;
			}
		}		

		/* collide with edges of screen */
		if (rg -> rcSprite.x <= 0)
			rg -> rcSprite.x = 0;
		if (rg -> rcSprite.x >= SCREEN_WIDTH - TILE_SIZE) 
			rg -> rcSprite.x = SCREEN_WIDTH - TILE_SIZE;

		if (rg -> rcSprite.y <= 0)
			rg -> rcSprite.y = 0;
		if (rg -> rcSprite.y >= SCREEN_HEIGHT - TILE_SIZE) 
			rg -> rcSprite.y = SCREEN_HEIGHT - TILE_SIZE;


		SDL_RenderClear(renderer);



		for (int i = 0; i <= ROOM_Y; i++)
		{
			for (int j = 0; j < ROOM_X; j++)
			{
				
				rg -> rc_Block.x = (j * TILE_SIZE); //set the array location to the tile size and Block size
				rg -> rc_Block.y = (i * TILE_SIZE);
				if (rg -> arr[i][j] == 0)
				{
					SDL_RenderCopy(renderer, backtex, &rg -> rcSrc2, &rg -> rc_Block);
				}
				if (rg -> arr[i][j] == 1)
				{
					SDL_RenderCopy(renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
				}
				if (rg -> arr[i][j] == 2)
				{
					SDL_RenderCopy(renderer, backtex, &rg -> rcSrc3, &rg -> rc_Block);
				}
			}
		}

		/* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
		SDL_RenderCopy(renderer, spritetex, &rg -> rcSrc2, &rg -> rcSprite);
		SDL_RenderPresent(renderer);
	}


	// SDL_Delay(5000);
	//SDL_DestroyTexture(backtex);
	//SDL_DestroyTexture(spritetex);
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyWindow(window);
}

void possible(roomGrid *rg, progress *pz)
{
	rg -> xa = (rg -> rcSprite.x) / TILE_SIZE;
	rg -> ya = (rg -> rcSprite.y) / TILE_SIZE;
	rg -> yb = ((rg -> rcSprite.y-1) + TILE_SIZE) / TILE_SIZE;
	rg -> xb = ((rg -> rcSprite.x-1) + TILE_SIZE) / TILE_SIZE;

	switch(rg -> direction)
	{		
		case(left):		if ((rg -> arr[rg -> ya][rg -> xa - 1]) == (rg -> arr[rg -> yb][rg -> xa - 1]))
						{
							if(rg -> arr[rg -> yb][rg -> xa - 1] == 0)
							{
								rg -> rcSprite.x -= 8;
							}
						};
						break;

		case(down):		if((rg -> arr[rg -> yb + 1][rg -> xa]) == (rg -> arr[rg -> yb + 1][rg -> xb]))
						{
							if(rg -> arr[rg -> yb + 1][rg -> xa] == 0)
							{
								rg -> rcSprite.y += 8;
							}
						};
						break;

		case(right):	if((rg -> arr[rg -> ya][rg -> xb + 1]) == (rg -> arr[rg -> yb][rg -> xb + 1]))
						{
							if(rg -> arr[rg -> ya][rg -> xb + 1] == 0)
							{
								rg -> rcSprite.x += 8;
							}
						};
						break;

		case(up):		if((rg -> arr[rg -> ya - 1][rg -> xa]) == (rg -> arr[rg -> ya - 1][rg -> xb]))
						{
							if(rg -> arr[rg -> ya - 1][rg -> xa] == 0)
							{
								rg -> rcSprite.y -= 8;
							}
						};
						break;

		default:		fprintf(stderr, "Problem probing!\n");
						exit(6);
						break;
	 }
}


void interactProbe(roomGrid *rg, progress *pz)
{
	rg -> xc = (rg -> rcSprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
	rg -> yc = (rg -> rcSprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
	rg -> probe = 0;

	switch(rg -> direction)
	{		
		case(left):		rg -> probe = rg -> arr[rg -> yc][rg -> xc - 1];
						if(action(rg, pz))
						{
							rg -> rcSprite.x += 8;
						};
						break;

		case(down):		rg -> probe = rg -> arr[rg -> yc + 1][rg -> xc];
						if(action(rg, pz))
						{

						};
						break;

		case(right):	rg -> probe = rg -> arr[rg -> yc][rg -> xc + 1];
						if(action(rg, pz))
						{

						};
						break;

		case(up):		rg -> probe = rg -> arr[rg -> yc - 1][rg -> xc];
						if(action(rg, pz))
						{

						};
						break;
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

	//free(filename);
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







int action(roomGrid *rg, progress *pz)
{
	switch(rg -> probe)
	{
		case(puz_1):		printf("in puz_1 case\n");
							if ((pz -> puzzle_1) == false)
							{
								printf("Spaced!\n");
								pz -> puzzle_1 = true;
								return 1;
							}
							else
							{
								printf("Already spaced!\n");
								return 0;
							}
							break;

		case(puz_2):		
							return 0;
							break;

		case(puz_3):		return 0;
							break;

		case(puz_4):		return 0;
							break;

		case(puz_5):		return 0;
							break;

		default:			return 0;
							fprintf(stderr, "PANIC!\n");
							exit(7);
							break;
	}
}


void printArray(roomGrid *rg, progress *pz)
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

void freeArray(roomGrid *rg)
{
	for (int i = 0; i < ROOM_Y; i++)
	{
		free(rg -> arr[i]);
	}
	free(rg -> arr);
}