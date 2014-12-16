#include "MadLab_headers.h"

//                      CORE FUNCTION DEFINITIONS

//Used to make the room from the scanned file.
void makeRoom(roomGrid *rg, FILE *fp)
{
    int i, j;

    rg -> arr = 0;
    rg -> arr = (int **)calloc((ROOM_Y) + 1, sizeof(int *));            //What's this 1 for?!

    if (rg -> arr == NULL){

        fprintf(stderr, "No memory available.\n");
        exit(3);

    }

    for (i = 0; i <= ROOM_Y; i++){
        rg -> arr[i] = (int *)calloc((ROOM_X)+1, sizeof(int));
        if (rg -> arr[i] ==  NULL){

            fprintf(stderr, "No memory available.\n");
            exit(4);

        }
    }

    for (i = 0; i < ROOM_Y; i++){
        for (j = 0; j < ROOM_X; j++){
            if (fscanf(fp, "%1d", &rg -> arr[i][j]) == 1);              //What's this 1 for?!
            else{

                fprintf(stderr, "Invalid array size.\n");
                exit(5);

            }
        }
    }
}

//The main part of the game running problems and movement etc.
void run(roomGrid *rg, progress *pz)
{
    SDL_Window *window = NULL;
    char *instructions_list[NUM_INSTRUCTIONS];

    initialise_SDL_component(window, rg);

    get_instructions(instructions_list);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, MUSIC_CONST_ONE, MUSIC_CONST_TWO);
    Mix_Chunk *mus = Mix_LoadWAV("20141124b.wav");

    //Prints the opening scene.
    print_instruction(rg, instructions_list, 0, 10);

    draw(rg, pz, mus, instructions_list);

    atexit(SDL_Quit);

    //Mix_HaltMusic(); 
    //Mix_FreeChunk(mus); 
    //Mix_CloseAudio();  
   // Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

//Used to initialise all of the necessary components of SDL.
void initialise_SDL_component(SDL_Window *window, roomGrid *rg)
{

    //Initialise SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) != SUCCESSFUL){
        fprintf(stderr, "\nUnable to initialise SDL:  %s\n",
                        SDL_GetError());
        exit(1);
    }
    else{
        window = SDL_CreateWindow ("MADLAB!",                   //window name
                                 SDL_WINDOWPOS_UNDEFINED,       //x-axis on the screen coordinate
                                 SDL_WINDOWPOS_UNDEFINED,       //y-axis screen coordinate
                                 SCREEN_WIDTH, SCREEN_HEIGHT,   //size of the window
                                 SDL_WINDOW_SHOWN);             //make the window resizeable       

        if (window == NULL)
        {
            printf("Could not create window: %s\n", SDL_GetError());
            exit(1);
        }
    }

    // Initialize PNG loading.
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){ 
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    //Initialise renderer.
    if ((rg -> renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL){
        fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //Initialise TTF component.
    if( TTF_Init() != SUCCESSFUL){
    	fprintf(stderr, "\nUnable to initialize TTF.\n");
    	SDL_Quit();
    	exit(1);
   }

}