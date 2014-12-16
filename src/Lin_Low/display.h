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
#define ROOM_Y 25
#define SPRITE_VEL 5
#define WWIDTH 800
#define WHEIGHT 600
#define WALL 1
#define BLANK 0

typedef enum compass{up = 0, right = 1, down = 2, left = 3/*, space = 4*/}compass;

typedef enum tileType{path = 0, obstacle = 1, puz_1 = 2, puz_2 = 3, puz_3 = 4, puz_4 = 5, puz_5 = 6}tileType;

typedef struct roomGrid
{
    int **arr;
    compass direction;
    SDL_Rect rcSprite, rcSrc1, rcSrc2, rcSrc3, rc_Block;
    int xa;
    int ya;
    int xb;
    int yb;
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
typedef struct display
{
    SDL_Window *window;
    SDL_Surface *background;
    SDL_Surface *image;
    SDL_Surface *image2;
    SDL_Surface *controls;
    Uint32 white, black;
    SDL_Rect *box;
    SDL_Event *event;
} *Display;

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

//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg, progress *pz);
void draw(SDL_Renderer *renderer, SDL_Window *window, roomGrid *rg, progress *pz);
void run(roomGrid *rg, progress *pz);
void freeArray(roomGrid *rg);
void possible(roomGrid *rg, progress *pz);
int action(roomGrid *rg, progress *pz);
void interactProbe(roomGrid *rg, progress *pz);

Display newDisplay();
void startFrame(Display d);
void drawBox(Display d, int x);
void endFrame(Display d);
void quit(Display d);
bool getEvent(Display d);
void LoadScreen(Display d);
void getloadscreenevent(Display d);
void getkeyEvent(Display d, int x);
void runloadscreen();

