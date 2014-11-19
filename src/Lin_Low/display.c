#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "display.h"

struct display
{
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Surface *image;
    Uint32 white, black;
    SDL_Rect *box;
}; 

Display newDisplay(){
    SDL_Init(SDL_INIT_EVERYTHING);

    Display d = malloc(sizeof(struct display));

    // Create window and get a the associated surface
    d->window = SDL_CreateWindow("Puzzle",100,100,640,480,0);
    d->surface = SDL_GetWindowSurface(d->window);
    d->image = IMG_Load("../../gfx/computer.png");

    // Let the room be white. Fill it.
    d->white = SDL_MapRGB(d->surface->format,136,170,194);
    d->black = SDL_MapRGB(d->surface->format,0,0,0);
    
    // Box
    d->box = malloc(sizeof(SDL_Rect));
    *d->box = (SDL_Rect) {200,200,32,32};
    return d;
}

// Clear the display and draw backgroud
void startFrame(Display d){
    SDL_FillRect(d->surface,NULL,d->white); 
}

void drawBall(Display d, float x, float y){
    int xp = (int) ((640-32) * x);
    int yp = (int) ((480-32) * y);
    d->box->x = xp;
    d->box->y = yp;
    SDL_BlitSurface(d->image, NULL, d->surface, d->box);
}

void endFrame(Display d){
    SDL_UpdateWindowSurface(d->window);
    SDL_Delay(20);
}

void quit(Display d){
    SDL_Delay(3000);
    SDL_Quit();
}





