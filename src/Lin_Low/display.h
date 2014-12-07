#include <stdbool.h>

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

Display newDisplay();
void startFrame(Display d);
void endFrame(Display d);
void quit(Display d);
bool getEvent(Display d);
void drawBox(Display d, int x);
void LoadScreen(Display d);
void save(int array[ROOM_Y][ROOM_X]);
void runEditorfromLoadscreen(void);
Display newDisplay();

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

#define WWIDTH 800
#define WHEIGHT 600
#define WALL 1
#define BLANK 0

