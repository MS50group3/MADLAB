#include <stdlib.h>
#include "display.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

void run(){
    
    Display d=newDisplay();
    startFrame(d);
    int x=1;
    bool gameRunning=true;
    SDL_Event event;
    
    while(gameRunning)
    {
        drawBox(d, x);
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    gameRunning=false;
                    break;
                    
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        if(x==2||x==3||x==4){
                            x--;
                        }
                        drawBox(d, x);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        
                    if(x==1||x==2||x==3){
                            x++;
                        }
                            drawBox(d, x);
                            break;
                        
                    }
                
                    case SDLK_SPACE:
                        if(x==3){
                        //set x=7 and draw controls page
                            x=x+4;
                            drawBox(d, x);
                        break;
                        }
                        //insert what happens with editor here
                        
                        //if on controls page, wait for the spacebar to be pressed, then draw load screen menu
                        if(x==7){
                            x=3;
                            if(SDL_PollEvent(&event))
                            {
                                switch(event.type)
                                {
                                    case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym)
                                    {
                                        case SDLK_SPACE:
                                            drawBox(d, x);

                                    }
                                }
                            }
                        }
                        
                }
            
            }
        }
        
        endFrame(d);
        
    }

    quit(d);
}

int main(){
    run();
}
