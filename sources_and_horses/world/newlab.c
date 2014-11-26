/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

/* definitions */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 640
#define TILE_SIZE    32
#define ROOM_X 25
#define ROOM_Y 20
#define OPEN 0
#define SPRITE_VEL 5


typedef enum compass{up = 0, right = 1, down = 2, left = 3}compass;

typedef enum tileType{path = 0, obstacle = 1, interactive = 2}tileType;

typedef struct roomGrid
{
	int **arr;
	compass direction;
	SDL_Rect rcSprite, rcSrc, rcBrick;
	int xa;
	int xb;
	int yb;
	int ya;
	int xs;
	int ys;
	int vertd;
	int probe;

}roomGrid;


//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg);
void draw(SDL_Renderer *renderer, SDL_Window *window, roomGrid *rg);
void run();
void freeArray(roomGrid *rg);
void possible(roomGrid *rg);
int walk(roomGrid *rg);


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
	printf("File was opened.\n");

	makeRoom(rg, fp);
	fclose(fp);

	run(rg);
	printArray(rg);
	freeArray(rg);

	return 0;
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
		}
	}
}


void run(roomGrid *rg)
{
	SDL_Window *window = NULL;
	bool success = true;

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

	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //Initialize PNG loading ; 
		{ 
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); success = false; 
			printf("%d", success);
		}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	draw(renderer, window, rg);
	atexit(SDL_Quit);
	IMG_Quit();
	SDL_Quit();
}

void draw(SDL_Renderer *renderer, SDL_Window *window, roomGrid *rg)
{
	SDL_Surface *background, *sprite, *bricks;
	SDL_Texture *backtex, *spritetex, *brickstex;
	bool gameRunning = true;
	rg -> xa = 0;
	rg -> yb = 0;
	rg -> ya = 0;
	rg -> vertd = 0;
	rg -> direction = 0;
	//int i = 0, j =0;
	// int colorkey;

	/* making dat dere background */
	background = SDL_LoadBMP("pokemonlab.bmp");
	backtex = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface (background);
	/* I have created life itself yo */                                                        
	sprite = SDL_LoadBMP("prof2.bmp");
	spritetex = SDL_CreateTextureFromSurface(renderer, sprite);
	SDL_FreeSurface (sprite);
	/* bob's brick laying corp*/
	bricks = IMG_Load("maze.png");
	brickstex = SDL_CreateTextureFromSurface(renderer, bricks);
	SDL_FreeSurface (bricks);

	/* set sprite "source" position - as called by RenderCopy, choose which to be */
 	rg -> rcSprite.y = 32;
 	rg -> rcSprite.x = 0;
	rg -> rcSprite.w = TILE_SIZE;
	rg -> rcSprite.h = TILE_SIZE; 

	/* set sprite "destination" position - as called by RenderCopy, choose which to be */
	rg -> rcSrc.x = 32;
	rg -> rcSrc.y = 0;
	rg -> rcSrc.w = TILE_SIZE;
	rg -> rcSrc.h = TILE_SIZE;

	rg -> rcBrick.x = 32;
	rg -> rcBrick.y = 32;
	rg -> rcBrick.w = TILE_SIZE;
	rg -> rcBrick.h = TILE_SIZE;


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
						if (!((rg -> rcSprite.x) % TILE_SIZE))
						{
							rg -> direction = left;
							possible(rg);
						}
						// 	if (possible(rg))
						// 	{
						// 		rg -> rcSprite.x -= 8;
						// 	}
						// }
						 else
						{
						 	rg -> rcSprite.x -= 8;
						}
						break;
					case SDLK_RIGHT:
						if (!((rg -> rcSprite.x) % TILE_SIZE))
						{
							rg -> direction = left;
							possible(rg);
						}
						else
						{
							rg -> rcSprite.x += 8;
						}
						break;
					case SDLK_UP:
						if (!((rg -> rcSprite.y) % TILE_SIZE))
						{
							rg -> direction = up;
							possible(rg);
						}
						else
						{
							rg -> rcSprite.y -= 8;
						}
						break;
					case SDLK_DOWN:
						if (!((rg -> rcSprite.y) % TILE_SIZE))
						{
							rg -> direction = down;
							possible(rg);
						}
						else
						{
							rg -> rcSprite.y += 8;
						}
						break;
					case SDLK_SPACE:
						;
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

	//SDL_RenderCopy(renderer, spritetex, &rcSrc, &rcSprite);
	//SDL_RenderCopy(renderer, backtex, NULL, NULL);

	for (int i = 0; i <= ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			rg -> rcBrick.x = (j*rg -> rcBrick.w);
     		rg -> rcBrick.y = (i*rg -> rcBrick.h);

			if (rg -> arr[i][j] != 0)
			{
				//brick destination position				
				SDL_RenderCopy(renderer, brickstex, NULL, &rg -> rcBrick);
			}
			//printf("%2c", );
		}
	}

	/* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
	
	//SDL_RenderCopy(renderer, backtex, NULL, NULL);
	SDL_RenderCopy(renderer, spritetex, &rg -> rcSrc, &rg -> rcSprite);
	//SDL_RenderCopy(renderer, brickstex, NULL, &rcBrick);
	SDL_RenderPresent(renderer);
}


	// SDL_Delay(5000);
	SDL_DestroyTexture(backtex);
	SDL_DestroyTexture(spritetex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void possible(roomGrid *rg)
{
	rg -> xa = (rg -> rcSprite.x) / TILE_SIZE;
	rg -> ya = (rg -> rcSprite.y) / TILE_SIZE;
	rg -> yb = ((rg -> rcSprite.y-1) + TILE_SIZE) / TILE_SIZE;
	rg -> xb = ((rg -> rcSprite.x-1) + TILE_SIZE) / TILE_SIZE;
	rg -> xs = (rg -> rcSprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
	rg -> ys = (rg -> rcSprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
	rg -> probe = 0;

	printf("vertice a%d\n", rg -> xa);
	printf("vertice c%d\n", rg -> ya);
	printf("vertice b%d\n", rg -> yb);
	printf("sprite.x %d\n", rg -> rcSprite.x);
	printf("sprite.y %d\n", rg -> rcSprite.y);
	printf("direction %d\n", rg -> direction);

	// if (rg -> direction == left)
	// {
	// 	if ((rg -> arr[rg -> ya][rg -> xa - 1] == OPEN) && (rg -> arr[rg -> yb][rg -> xa - 1] == OPEN))
	// 	{
	// 		return 1;
	// 	}

	// 	return 0;
	// }
	
	// else
	// {
	// 	return 0;
	// }

	switch(rg -> direction)
	{		
		case(left):		if ((rg -> arr[rg -> ya][rg -> xa - 1]) == (rg -> arr[rg -> yb][rg -> xa - 1]))
						{
							rg -> probe = rg -> arr[rg -> yb][rg -> xa - 1];
							printf("probe %d\n", rg -> arr[rg -> ya][rg -> xa - 1]);
							if(walk(rg))
							{
								rg -> rcSprite.x -= 8;
							}
							//rg -> rcSprite.x -= 8;
						};
						break;

		case(down):		if((rg -> arr[rg -> yb + 1][rg -> xa]) == (rg -> arr[rg -> yb + 1][rg -> xb]))
						{
							rg -> probe = rg -> arr[rg -> yb + 1][rg -> xa];
							if(walk(rg))
							{
									rg -> rcSprite.y += 8;
							}
						};
						break;

		case(right):	if((rg -> arr[rg -> ya][rg -> xb + 1]) == (rg -> arr[rg -> yb][rg -> xb + 1]))
						{
							rg -> probe = rg -> arr[rg -> ya][rg -> xb + 1];
							if(walk(rg))
							{
									rg -> rcSprite.x += 8;
							}
						};
						break;

		case(up):		if((rg -> arr[rg -> ya - 1][rg -> xa]) == (rg -> arr[rg -> ya - 1][rg -> xb]))
						{
							rg -> probe = rg -> arr[rg -> ya - 1][rg -> xa];
							if(walk(rg))
							{
									rg -> rcSprite.y -= 8;
							}
						};
						break;

		default:		fprintf(stderr, "Problem probing!\n");
						exit(6);
						//return 0;
						break;
	// 	}
	 }
	// return 0;
}

int walk(roomGrid *rg)
{
	switch(rg -> probe)
	{
	case(path):			return 1;
						break;

	case(obstacle):		return 0;
						break;

	case(interactive):	return 0;
						break;

	default:			return 0;
						fprintf(stderr, "PANIC!\n");
						exit(7);
						break;
	}
}


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

void freeArray(roomGrid *rg)
{
	for (int i = 0; i < ROOM_Y; i++)
	{
		free(rg -> arr[i]);
	}
	free(rg -> arr);
}