#include "newlab3.h"

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
	draw(renderer, window, rg, pz);
	atexit(SDL_Quit);
	IMG_Quit();
	SDL_Quit();
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
    	SDL_Event event; 

		if (SDL_PollEvent(&event))  
		{
			switch (event.type) 
			{	

				case SDL_QUIT:
					exit(0);

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
	SDL_DestroyTexture(backtex);
	SDL_DestroyTexture(spritetex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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