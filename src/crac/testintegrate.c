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
#define SPRITE_VEL 5


typedef enum compass{up = 0, right = 1, down = 2, left = 3}compass;

typedef enum tileType{path = 0, obstacle = 1, puz_1 = 2, puz_2 = 3, puz_3 = 4, puz_4 = 5, puz_5 = 6}tileType;

typedef struct roomGrid
{
	int **arr;
	compass direction;
	SDL_Rect rcSprite, rcSrc1, rcObj, rcSrc3, rc_Block;
	bool gameRunning;
	int xa;
	int xb;
	int yb;
	int ya;
	int xc;
	int yc;
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

// All info required for windows / renderer & event loop
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Surface *surface;
};
typedef struct SDL_Simplewin SDL_Simplewin;