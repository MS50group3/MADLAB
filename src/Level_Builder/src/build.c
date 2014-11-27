#include "newlab3.h"

#define WALL 1
#define BLANK 0

/* newlab3.h contains SDL includes, hash defines and some
premade functions */

typedef struct Cursor
{
	int x, y, tileID;
} Cursor;

typedef struct input
{
	int mouse_x, mouse_y;
	int add, remove;
} Input;

typedef struct map
{
	int width, height;
} Map;





int main(void){

	bool success = true;
	bool running = true;
	Input input;
	Cursor cursor;

	input.add = 0;
	input.remove = 0;

	int array[ROOM_Y][ROOM_X];


	// Init to zero
	for (int i = 0; i < ROOM_Y; ++i) {
		for (int j = 0; j < ROOM_X; ++j) {	
			array[i][j]=0;
		}
	}

	/* Create the necessary window, surface, renderer and tex's */
	SDL_Window *window;	
	window = SDL_CreateWindow ("Level Editor",        		//window name
							 SDL_WINDOWPOS_UNDEFINED,       //x-axis on the screen coordinate
							 SDL_WINDOWPOS_UNDEFINED,       //y-axis screen coordinate
							 SCREEN_WIDTH, SCREEN_HEIGHT,   //size of the window
							 SDL_WINDOW_RESIZABLE);         //make the window resizeable       

	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //Initialize PNG loading ; 
	{ 
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); success = false; 
		printf("%d", success);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// Background stuff
	SDL_Surface *back_surf;
	SDL_Texture *backtex;

	// Tile stuff
	SDL_Surface *tile_surf;
	SDL_Texture *tiletex;
	SDL_Rect tile_src, tile_dst;

	// Cursor stuff
	SDL_Surface *cursor_surf;
	SDL_Texture *cursor_tex;
	SDL_Rect cursor_src, cursor_dst;

	/* Make the tile */
	tile_surf = IMG_Load("../gfx/block.png");
	tiletex = SDL_CreateTextureFromSurface(renderer, tile_surf);
	SDL_FreeSurface(tile_surf);

	/* Make the cursor */
	cursor_surf = IMG_Load("../gfx/cursor.png");
	Uint32 colorkey = SDL_MapRGB(cursor_surf->format, 127, 0, 127);
	SDL_SetColorKey( cursor_surf, SDL_TRUE, colorkey);

	cursor_tex = SDL_CreateTextureFromSurface(renderer, cursor_surf);	
	SDL_FreeSurface (cursor_surf);

	/* Make the background */
	back_surf = IMG_Load("../gfx/labtile2.png");
	backtex = SDL_CreateTextureFromSurface(renderer, back_surf);
	SDL_FreeSurface(back_surf);


	// Run the meat of the program.
	while(running){
		
		// Event handling time
		SDL_Event event; 

		if (SDL_PollEvent(&event))  // If there is an event
		{
			switch (event.type) 
			{	
				// Quit
				case SDL_QUIT:
					exit(0);
				break;

				// Keydowns
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)     
					{
						case SDLK_q:
							running = false;
						break;

						default:
						break;
			    	}
			    break;

			    // Key ups
			    case SDL_KEYUP:
			    	switch (event.key.keysym.sym)
			    	{
						default:
						break;
			    	}
			    break;

			    // Click
			    case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							input.add = 1;
						break;
						
						case SDL_BUTTON_RIGHT:
							input.remove = 1;
						break;
						
						default:
						break;
					}
				break;
				
				// "Unclick" - reset the values on the key release
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							input.add = 0;
						break;
						
						case SDL_BUTTON_RIGHT:
							input.remove = 0;
						break;
						
						default:
						break;
					}
				break;
			}
		}

		// Get the mouse coords
		SDL_GetMouseState(&input.mouse_x, &input.mouse_y);

		// Round the coords to the nearest multiple of TILE_SIZE
		int excess = input.mouse_x % TILE_SIZE;
		input.mouse_x = input.mouse_x - excess;

		excess = input.mouse_y % TILE_SIZE;
		input.mouse_y = input.mouse_y - excess;

		// Which tile 'element' are we in
		int tile_x = input.mouse_x / TILE_SIZE;
		int tile_y = input.mouse_y / TILE_SIZE;

		// Cursor details
		cursor.x = input.mouse_x;
		cursor.y = input.mouse_y;

		// Where to get the image from (relative)
		cursor_src.y = 0;
		cursor_src.x = 0;
		cursor_src.w = TILE_SIZE;
		cursor_src.h = TILE_SIZE;
		
		// Where to put it (relative)
		cursor_dst.y = cursor.y;
		cursor_dst.x = cursor.x;
		cursor_dst.w = TILE_SIZE;
		cursor_dst.h = TILE_SIZE;

		tile_src.y=0;
		tile_src.x=0;
		tile_src.w=TILE_SIZE;
		tile_src.h=TILE_SIZE;

		if(input.add == 1)
		{
			array[tile_y][tile_x] = WALL;
		}

		if (input.remove == 1)
		{
			array[tile_y][tile_x] = BLANK;
		}

		for (int i = 0; i < ROOM_Y; ++i)
		{
			for (int j = 0; j < ROOM_X; ++j)
			{	
				// Where to put the tile
				tile_dst.x = j*TILE_SIZE;
				tile_dst.y = i*TILE_SIZE;
				tile_dst.w = TILE_SIZE;
				tile_dst.h = TILE_SIZE;

				if (array[i][j] == WALL)
				{	
					// If the array element is a 1, draw a wall
					SDL_RenderCopy(renderer, tiletex, &tile_src, &tile_dst);
				}
				else if (array[i][j] == BLANK)
				{	// If the element is a 0, draw a floor tile
					SDL_RenderCopy(renderer, backtex, &tile_src, &tile_dst);
				}
			}
		}

		SDL_RenderCopy(renderer, cursor_tex, &cursor_src, &cursor_dst);

		/* Update the screen with the latest render */
		SDL_RenderPresent(renderer);
	}

	// Tear everything down
    SDL_DestroyTexture(backtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();

}

