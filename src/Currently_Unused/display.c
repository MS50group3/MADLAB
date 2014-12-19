#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

#define WWIDTH 800
#define WHEIGHT 600

struct display
{
    SDL_Window *window;
    SDL_Surface *background;
    SDL_Surface *image;
    Uint32 white, black;
    SDL_Rect *box;
    SDL_Event *event;
}; 

// Create all the relevant stuff for a display
Display newDisplay(){

    SDL_Init(SDL_INIT_EVERYTHING);

    Display d = malloc(sizeof(struct display));
    d->event = malloc(sizeof(SDL_Event));

    // Create window and get the associated surface
    d->window = SDL_CreateWindow("Puzzle",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WWIDTH,WHEIGHT,0);
    d->background = SDL_GetWindowSurface(d->window);
    d->image = IMG_Load("../../gfx/computer.png");
    //d->sprite = SDL_LoadBMP("../../gfx/prof2.bmp");

    // Let the room be white. Fill it.
    d->white = SDL_MapRGB(d->background->format,136,170,194);
    d->black = SDL_MapRGB(d->background->format,0,0,0);
    
    // Box
    d->box = malloc(sizeof(SDL_Rect));
    *d->box = (SDL_Rect) {200,200,32,32};
    return d;
}

// Clear the display and draw backgroud
void startFrame(Display d){
    SDL_FillRect(d->background,NULL,d->white); 
}

void drawBall(Display d, float x, float y){
    int xp = (int) ((WWIDTH-32) * x);
    int yp = (int) ((WHEIGHT-32) * y);
    d->box->x = xp;
    d->box->y = yp;
    SDL_BlitSurface(d->image, NULL, d->background, d->box);
}

void endFrame(Display d){
    SDL_UpdateWindowSurface(d->window);
    SDL_Delay(20);
}

void quit(Display d){
    SDL_Delay(20);
    SDL_Quit();
}

bool getEvent(Display d){

    bool arrived = SDL_PollEvent(d->event);
    if (! arrived) return false; // No event polled at all

    if (d->event->type != SDL_QUIT) return false; // Filter all events other than quit
    return true;
}





