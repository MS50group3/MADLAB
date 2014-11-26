/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

/* definitions */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define TILE_SIZE    32
#define ROOM_X 25
#define ROOM_Y 24
#define OPEN 0
#define SPRITE_VEL 5

typedef struct roomGrid
{
	int **arr;
	compass direction;
	int currentX;
	int currentY;
}roomGrid;

typedef struct gameObjects
{
	
};

typedef enum compass{up = 0, right = 1, down = 2, left = 3}compass;

//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg);
void draw(SDL_Renderer *renderer, SDL_Rect rcSprite, SDL_Rect rcSrc, SDL_Window *window, SDL_Rect rcBrick, roomGrid *rg);
void run();
void freeArray(roomGrid *rg);


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


// (rg -> arr)[ROOM_X] = calloc(ROOM_Y +1, sizeof(char*));

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

	//rg -> arr[ROOM_X] = calloc(ROOM_Y +1, sizeof(char*));



	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			fscanf(fp, "%1d", &rg -> arr[i][j]);
		}
	}


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
	SDL_Rect rcSprite, rcSrc, rcBrick;
	//SDL_Surface* screenSurface = NULL;
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

//Initialize PNG loading ; 
	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) 
		{ 
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); success = false; 
			printf("%d", success);
		}


	// if (IMG_Init(IMG_INIT_PNG) != 0)
	// {
	// 	fprintf(stderr, "\nUnable to initialise SDL_image:  %s\n",
	// 					SDL_GetError());
	// 	exit(1);
	// }

	//IMG_Init(IMG_INIT_PNG);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	draw(renderer, rcSprite, rcSrc, window, rcBrick, rg);

	atexit(SDL_Quit);

	IMG_Quit();
	
	SDL_Quit();
}

void draw(SDL_Renderer *renderer, SDL_Rect rcSprite, SDL_Rect rcSrc, SDL_Window *window, SDL_Rect rcBrick, roomGrid *rg)
{
	SDL_Surface *background, *sprite, *bricks;
	SDL_Texture *backtex, *spritetex, *brickstex;
	bool gameRunning = true;
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
 	rcSprite.y = 32;
 	rcSprite.x = 0;
	rcSprite.w = TILE_SIZE;
	rcSprite.h = TILE_SIZE; 

	/* set sprite "destination" position - as called by RenderCopy, choose which to be */
	rcSrc.x = 32;
	rcSrc.y = 0;
	rcSrc.w = TILE_SIZE;
	rcSrc.h = TILE_SIZE;

	rcBrick.x = 32;
	rcBrick.y = 32;
	rcBrick.w = TILE_SIZE;
	rcBrick.h = TILE_SIZE;


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
					  	changeDirection(roomGrid *RG, )
						rcSprite.x -= 5;
						break;
					case SDLK_RIGHT:
					 	changeDirection(roomGrid *RG, )	
						rcSprite.x += 5;
						break;
					case SDLK_UP:
					 	changeDirection(roomGrid *RG, )
						rcSprite.y -= 5;
						break;
					case SDLK_DOWN:
					 	changeDirection(roomGrid *RG, )
						rcSprite.y += 5;
						break;
		    	}
		    	break;
				}
		}		

			/* collide with edges of screen */
			if (rcSprite.x <= 0)
				rcSprite.x = 0;
			if (rcSprite.x >= SCREEN_WIDTH - TILE_SIZE) 
				rcSprite.x = SCREEN_WIDTH - TILE_SIZE;

			if (rcSprite.y <= 0)
				rcSprite.y = 0;
			if (rcSprite.y >= SCREEN_HEIGHT - TILE_SIZE) 
				rcSprite.y = SCREEN_HEIGHT - TILE_SIZE;


	SDL_RenderClear(renderer);

	//SDL_RenderCopy(renderer, spritetex, &rcSrc, &rcSprite);
	//SDL_RenderCopy(renderer, backtex, NULL, NULL);

	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			rcBrick.x = (j*rcBrick.w);
     		rcBrick.y = (i*rcBrick.h);

			if (rg -> arr[i][j] != 0)
			{
				//brick destination position				
				SDL_RenderCopy(renderer, brickstex, NULL, &rcBrick);
			}
			//printf("%2c", );
		}
	}

	/* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
	
	//SDL_RenderCopy(renderer, backtex, NULL, NULL);
	SDL_RenderCopy(renderer, spritetex, &rcSrc, &rcSprite);
	//SDL_RenderCopy(renderer, brickstex, NULL, &rcBrick);
	SDL_RenderPresent(renderer);
}

	// SDL_Delay(5000);
	SDL_DestroyTexture(backtex);
	SDL_DestroyTexture(spritetex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


void chooseDirection(roomGrid *rg)
{
	rg -> currentX = 

	switch(rg -> direction)
		{		
		case(left):		((rcSprite.x >= rcBrick.x + TILE_SIZE) && (rcSprite.x + TILE_SIZE >= rcBrick.x + TILE_SIZE))
						pM -> probe = pM -> maze[pM -> x][pM -> y - 1];
						if(breadcrumbs(pM))
						{
							pM -> y--;
						};
						probeSurrounding(pM, pI);
						break;

		case(down):		((rcSprite.y >= rcBrick.y) && (rcSprite.y + TILE_SIZE >= rcBrick.y))
						pM -> probe = pM -> maze[pM -> x + 1][pM -> y];
						if(breadcrumbs(pM))
						{
							pM -> x++;
						};
						probeSurrounding(pM, pI);
						break;

		case(right):	((rcSprite.x <= rcBrick.x) && (rcSprite.x + TILE_SIZE <= rcBrick.x))
						pM -> probe = pM -> maze[pM -> x][pM -> y + 1];
						if(breadcrumbs(pM))
						{
							pM -> y++;
						};
						probeSurrounding(pM, pI);
						break;

		case(up):		((rcSprite.y <= rcBrick.y + TILE_SIZE) && (rcSprite.x + TILE_SIZE <= rcBrick.y + TILE_SIZE))
						pM -> probe = pM -> maze[pM -> x - 1][pM -> y];
						if(breadcrumbs(pM))
						{
							pM -> x--;
						};
						probeSurrounding(pM, pI);
						break;

		default:		fprintf(stderr, "Problem probing!\n");
						exit(6);
						break;
		}
	}
	return 0;
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