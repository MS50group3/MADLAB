#include "display.h"

/* display.h contains SDL includes, hash defines, typedefs and some
 premade functions */

void save(int array[ROOM_Y][ROOM_X]){
    
    FILE *of;
    of = fopen("../src/Your_level.txt","w");
    if(of == NULL) {
        printf("ERROR opening file...exiting\n");
    }
    
    for (int i = 0; i < ROOM_Y; ++i)
    {
        for (int j = 0; j < ROOM_X; ++j)
        {
            fprintf(of, "%d ", array[i][j]);
        }
        
        fprintf(of,"\n");
    }
    
    fclose(of);
}

void runEditorfromLoadscreen(Display d){
    
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
    /*
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
    */
    
    //PROBLEM HERE!
    SDL_Renderer *renderer = SDL_CreateRenderer(d->window, -1, SDL_RENDERER_ACCELERATED);
    
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
    tile_surf = IMG_Load("block.png");
    tiletex = SDL_CreateTextureFromSurface(renderer, tile_surf);
    SDL_FreeSurface(tile_surf);
    
    /* Make the cursor */
    cursor_surf = IMG_Load("cursor.png");

    Uint32 colorkey = SDL_MapRGB(cursor_surf->format, 127, 0, 127);
    SDL_SetColorKey( cursor_surf, SDL_TRUE, colorkey);
    
    cursor_tex = SDL_CreateTextureFromSurface(renderer, cursor_surf);
    SDL_FreeSurface (cursor_surf);
    
    /* Make the background */
    back_surf = IMG_Load("labtile2.png");

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
                        
                    case SDLK_s:
                        save(array);
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
    SDL_DestroyWindow(d->window);
    SDL_Quit();
    
}

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
        startFrame(d);
        *d->box=(SDL_Rect) {333,442,143,31};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==2){
        //draw original background so all options are white apart from "load game", which will become yellow
        startFrame(d);
        *d->box=(SDL_Rect) {336,473,143,31};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==3){
        //draw original background so all options are white apart from "controls", which will become yellow
        startFrame(d);
        *d->box=(SDL_Rect) {344,499,119,32};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);

    }
    else if(x==4){
        //draw original background so all options are white apart from final option, which will become yellow
        startFrame(d);
        *d->box=(SDL_Rect) {331,526,140,30};
        SDL_BlitSurface(d->image2, d->box, d->background, d->box);
    }
    else if(x==7){
        //draw controls screen
        SDL_BlitSurface(d->controls, NULL, d->background, NULL);
       
    }
   
}

void LoadScreen(Display d){
    
    SDL_Event event;
    bool gameRunning=true;
    int x=1;
    
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
                            //options 3 is controls page
                            x=x+4;
                            drawBox(d, x);
                            break;
                        }
                        
                        if(x==4){
                            //Option 4 opens editor/level builder
                            runEditorfromLoadscreen(d);
                            break;
                            
                        }
                        
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
                                            break;
                                            
                                    }
                                }
                            }
                        }
                
                }
            }
            
        endFrame(d);
        
        }
    
    }
}

void endFrame(Display d){
    SDL_UpdateWindowSurface(d->window);
}

void quit(Display d){
    SDL_Quit();
}


