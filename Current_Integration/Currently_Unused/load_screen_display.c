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
    SDL_Surface *image2;
    SDL_Surface *controls;
    Uint32 white, black;
    SDL_Rect *box;
    SDL_Event *event;
};

// Create all the relevant stuff for a display
Display newDisplay(){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    IMG_Quit();
    Display d = malloc(sizeof(struct display));
    d->event = malloc(sizeof(SDL_Event));
    
    // Create window and get the associated surface
    d->window = SDL_CreateWindow("Puzzle",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WWIDTH,WHEIGHT,0);
    d->background = SDL_GetWindowSurface(d->window);
    //set original background image
    d->image = IMG_Load("screen1.png");
    
    //set background image with different colour words to alternate with original so words change colour on key up or down
    d->image2= IMG_Load("screen2.png");
    //load image of controls
    d->controls=IMG_Load("controls.png");
    
    // Box
    d->box = malloc(sizeof(SDL_Rect));
    *d->box = (SDL_Rect) {333,442,143,31};
    
    return d;
}

// Draw original backgroud
void startFrame(Display d){
    SDL_BlitSurface(d->image, NULL, d->background, NULL);

}

//draw correct part of background image each time (a rectangular box around the written options)
void drawBox(Display d, int x){
    
    if(x==1){
        //draw original background so all options are white apart from "new game", which will become yellow
        SDL_BlitSurface(d->image, NULL, d->background, NULL);
        *d->box=(SDL_Rect) {333,442,143,31};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==2){
        //draw original background so all options are white apart from "load game", which will become yellow
        SDL_BlitSurface(d->image, NULL, d->background, NULL);
        *d->box=(SDL_Rect) {336,473,143,31};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==3){
        //draw original background so all options are white apart from "controls", which will become yellow
        SDL_BlitSurface(d->image, NULL, d->background, NULL);
        *d->box=(SDL_Rect) {344,499,119,32};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);

    }
    else if(x==4){
        //draw original background so all options are white apart from final option, which will become yellow
        SDL_BlitSurface(d->image, NULL, d->background, NULL);
        *d->box=(SDL_Rect) {331,526,140,30};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==7){
        //draw controls screen
        SDL_BlitSurface(d->controls, NULL, d->background, NULL);
       
    }
   
}

void endFrame(Display d){
    SDL_UpdateWindowSurface(d->window);
}

void quit(Display d){
    SDL_Quit();
}

bool getEvent(Display d){
    
    bool arrived = SDL_PollEvent(d->event);
    if (! arrived) return false; // No event polled at all
    
    if (d->event->type != SDL_QUIT) return false; // Filter all events other than quit
    return true;
}

