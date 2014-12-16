// PREPROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH     		800
#define SCREEN_HEIGHT    		640
#define TILE_SIZE         		 32
#define ROOM_X            		 25
#define ROOM_Y            		 20
#define SPRITE_VEL         		  5
#define SDL_8BITCOLOUR   		256
#define SLEEP_TIME       		100
#define NUM_INSTRUCTIONS  		 29
#define LENGTH_EXTENSION   		  5
#define LENGTH_PREFIX     		 14
#define NUM_REFRESHES     		 50
#define MAX_INPUT_CHARS  		 20
#define INPUT_FINISHED    100000000
#define CHARS_IN_ANS             13
#define RECT_X  				190
#define RECT_Y  				255
#define RECT_W  				700
#define RECT_H  				150
#define SUCCESSFUL                0
#define NUM_INSTRUCTIONS         29
#define MUSIC_CONST_ONE           2
#define MUSIC_CONST_TWO        4096

// TYPEDEFS AND ENUMERATION

enum compass{up = 0, right = 1, down = 2, left = 3};
typedef enum compass compass;

enum tileType{path = 0, obstacle = 1, puz_1 = 2, puz_2 = 3, puz_3 = 4, puz_4 = 5, puz_5 = 6};
typedef enum tileType tileType;

typedef struct roomGrid
{
    int **arr;
    compass direction;
    SDL_Rect rcSprite, rcSrc1, rcObj, rcSrc3, rc_Block;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_bool finished;
    bool gamerunning;
    int xa;
    int xb;
    int yb;
    int ya;
    int xc;
    int yc;
    int probe;
    int skip_checker;
    int refresh_counter;
}roomGrid;

typedef struct progress
{   
    bool puzzle_1;
    bool puzzle_2;
    bool puzzle_3;
    bool puzzle_4;
    bool puzzle_5;
}progress;

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum on_off {off, on};
typedef enum on_off on_off;

//FUNCTIONS FOR PROBLEMS

void print_instruction(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS], int start, int end);
void James_SDL_Events(roomGrid *rg);
void print_some_text(roomGrid *rg, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);
void look_for_action(roomGrid *rg);
void SDL_QuitChecker(roomGrid *rg);
void initialise_SDL_component(SDL_Window *window, roomGrid *rg);
void neill_notes(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS]);
void first_problem(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS]);
void input_screen(roomGrid *rg, wrong_right *correct_indicator);
void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS]);
void initialise_input_string(char input_string[MAX_INPUT_CHARS]);
void initialise_drcrect(SDL_Rect *drcrect, int input_index);
void check_user_variable_input(roomGrid *rg, char *input_string, int *input_index, int *finish_checker);

//FUNCTIONS FOR MOVEMENT

void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg, progress *pz);
void draw(roomGrid *rg, progress *pz, Mix_Chunk *mus, char *instructions_list[NUM_INSTRUCTIONS]);
void run(roomGrid *rg, progress *pz);
void freeArray(roomGrid *rg);
void possible(roomGrid *rg, progress *pz);
int action(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS]);
void interactProbe(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS]);
void move(roomGrid *rg, progress *pz);

//MAIN

int main(int argc, char *argv[])
{
    roomGrid roomStuff, *rg;
    rg = &roomStuff;

    progress puzzlesolved, *pz;
    pz = &puzzlesolved;

    FILE *fp = NULL;
    fp = fopen(argv[1], "r");

    if (fp == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    printf("File was opened.\n");

    makeRoom(rg, fp);

    fclose(fp);

    run(rg, pz);

    printArray(rg, pz);

    freeArray(rg);

    return(0);
}

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


// List of instructions to be used for printing.
void print_instruction(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS], int start, int end)
{
    int i;
    rg->finished = unfinished;

    for (i = start; i < end; ++i){
        print_some_text(rg, instructions_list[i]);
    }

}


// Just a list of instructions to be printed.
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS])
{
    //Opening scenes instructions
    instructions_list[0] = "MadLab";
    instructions_list[1] = "Where_am_I";
    instructions_list[2] = "looks_like";
    instructions_list[3] = "door_locked";
    instructions_list[4] = "shenanigans";
    instructions_list[5] = "neill_shenanigans";
    instructions_list[6] = "maybe_if_I";
    instructions_list[7] = "press_spacebar";
    instructions_list[8] = "find_neill";
    instructions_list[9] = "lets_go";

    //Neill's notes instructions
    instructions_list[10] = "neill_note";
	instructions_list[11] = "coding_stuff";
	instructions_list[12] = "door_jammed";
	instructions_list[13] = "room_too_hot";
	instructions_list[14] = "using_some_code";
	instructions_list[15] = "number";
	instructions_list[16] = "less_than_ten";
	instructions_list[17] = "but_if_we_have";
	instructions_list[18] = "greater_ten";
	instructions_list[19] = "number_eq_eq_ten";
  	instructions_list[20] = "number_is_ten";
  	instructions_list[21] = "useful_later";

    //First part of first problem instructions
	instructions_list[22] = "fan_on_wall";
	instructions_list[23] = "cool_down_room";
	instructions_list[24] = "control_panel";
	instructions_list[25] = "neill_notes";
	instructions_list[26] = "change_temp";

    //Second part of first problem instrucions.
	instructions_list[27] = "that_worked";
	instructions_list[28] = "room_cooling";
}


// Used to print sets of instructions to the screen.
void print_some_text(roomGrid *rg, char *instruction)
{
    rg->refresh_counter = 0;
    rg->skip_checker = off;
    SDL_Surface* text_one = NULL;
    SDL_Texture* image;

    // The following few lines are used to create a filename to get the .bmp to print to screen.
    char prefix[LENGTH_PREFIX] = "Instructions/";
    char extension[LENGTH_EXTENSION] = ".bmp";
    char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1);

    strcpy(filename, prefix);
    strcat(filename, instruction);
    strcat(filename, extension);

    // Loads image in and checks it.
    text_one = SDL_LoadBMP(filename);
    image = SDL_CreateTextureFromSurface(rg -> renderer, text_one);

    if (text_one == NULL){
        printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    }

    // Update the surface and apply the image.
    SDL_RenderCopy(rg -> renderer, image, NULL, NULL);
    SDL_RenderPresent(rg -> renderer);

    // Wait the sleep time and free the malloc for the filename.
    look_for_action(rg);

    free(filename);
}

//Looks for actions relating to skipping or quitting.
void James_SDL_Events(roomGrid *rg)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
       switch (event.type)
        {
            case SDL_QUIT:
                rg -> finished = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                rg -> skip_checker = 1;
                break;
            case SDL_KEYDOWN:
                rg -> skip_checker = 1;
                break;
        }
    }
}

//The refresh counter is used to delay a certain time whilst looking for exits.
void look_for_action(roomGrid *rg)
{
    do
    {
        ++(rg -> refresh_counter);
        SDL_Delay(SLEEP_TIME);
        SDL_QuitChecker(rg);
    }
    while(rg -> refresh_counter < NUM_REFRESHES && !rg -> skip_checker);
}


void SDL_QuitChecker(roomGrid *rg)
{
    James_SDL_Events(rg);
    if (rg -> finished){
        exit(1);
    }
}


void draw(roomGrid *rg, progress *pz, Mix_Chunk *mus, char *instructions_list[NUM_INSTRUCTIONS])
{
    SDL_Surface *background, *sprite;
    SDL_Texture *backtex, *spritetex;
    rg -> gamerunning = true;
    pz -> puzzle_1 = false;
    rg -> xa = 0;
    rg -> yb = 0;
    rg -> ya = 0;
    rg -> direction = 0;

    /* making dat dere background */
    background = IMG_Load("lab1sheet.png");
    backtex = SDL_CreateTextureFromSurface(rg -> renderer, background);
    SDL_FreeSurface (background);

    /* I have created life itself yo */
    sprite = SDL_LoadBMP("prof2.bmp");
    spritetex = SDL_CreateTextureFromSurface(rg -> renderer, sprite);
    SDL_FreeSurface (sprite);

    /* set sprite "source" position - as called by RenderCopy, choose which to be */
    rg -> rcSprite.y = 32;
    rg -> rcSprite.x = 0;
    rg -> rcSprite.w = TILE_SIZE;
    rg -> rcSprite.h = TILE_SIZE;

    rg -> rcObj.x = 32;  
    rg -> rcObj.y = 0;
    rg -> rcObj.w = TILE_SIZE;
    rg -> rcObj.h = TILE_SIZE;

    rg -> rc_Block.w = TILE_SIZE;
    rg -> rc_Block.h = TILE_SIZE;

    Mix_PlayChannel(-1, mus, -1);

    while (rg -> gamerunning)
    {
        SDL_Delay(20);
        SDL_Event event;  // call SDL_Event
        if (SDL_PollEvent(&event))  // If there is an event
        {
            // HandleEvent(event, rcSrc, rcSprite); //Run the HandleEvent function
            switch (event.type) 
            {
                case SDL_QUIT:
                    rg -> gamerunning = false;
                    break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_q:
                        rg -> gamerunning = false;
                        break;
                    case SDLK_LEFT:
                        rg -> direction = left;
                        (!((rg -> rcSprite.x) % TILE_SIZE)) ? possible(rg, pz): move(rg, pz);
                        break;
                    case SDLK_RIGHT:
                        rg -> direction = right;
                        (!((rg -> rcSprite.x) % TILE_SIZE)) ? possible(rg, pz): move(rg, pz);
                        break;
                    case SDLK_UP:
                        rg -> direction = up;
                        (!((rg -> rcSprite.y) % TILE_SIZE)) ? possible(rg, pz): move(rg, pz);
                        break;
                    case SDLK_DOWN:
                        rg -> direction = down;
                        (!((rg -> rcSprite.y) % TILE_SIZE)) ? possible(rg, pz): move(rg, pz);
                        break;
                    case SDLK_SPACE:
                        interactProbe(rg, pz, instructions_list);
                        break;
                }
                break;
            }
        }       

        /* collide with edges of screen */
        if (rg -> rcSprite.x <= 0)
        {
            rg -> rcSprite.x = 0;
        }
        if (rg -> rcSprite.x >= SCREEN_WIDTH - TILE_SIZE)
        {
            rg -> rcSprite.x = SCREEN_WIDTH - TILE_SIZE;
        }

        if (rg -> rcSprite.y <= 0)
        {
            rg -> rcSprite.y = 1;
        }
        if (rg -> rcSprite.y >= SCREEN_HEIGHT - TILE_SIZE)
        { 
            rg -> rcSprite.y = SCREEN_HEIGHT - TILE_SIZE;
        }

        SDL_RenderClear(rg -> renderer);

        for (int i = 0; i <= ROOM_Y; i++)
        {
            for (int j = 0; j < ROOM_X; j++)
            {
                rg -> rc_Block.x = (j * TILE_SIZE);  // set the array location to the tile size and Block size
                rg -> rc_Block.y = (i * TILE_SIZE);

                // first ground tile does not go in a loop. It populates everything so just draw it. You also free up 0!
                rg -> rcSrc1.x = 41;
                rg -> rcSrc1.y =  0;
                rg -> rcSrc1.w = 32;
                rg -> rcSrc1.h = 29;
                SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                
                if (rg -> arr[i][j] == 1)
                {
                    rg -> rcSrc1.x = 71;
                    rg -> rcSrc1.y = 81;
                    rg -> rcSrc1.w = 45;
                    rg -> rcSrc1.h = 34;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 2)
                {
                    rg -> rcSrc1.x = 73;
                    rg -> rcSrc1.y =  0;
                    rg -> rcSrc1.w = TILE_SIZE;
                    rg -> rcSrc1.h = 29;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 3)
                {
                    rg -> rcSrc1.x = 121;
                    rg -> rcSrc1.y =  56;
                    rg -> rcSrc1.w =  76;
                    rg -> rcSrc1.h =  59;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 4)
                {
                    rg -> rcSrc1.x = 207;
                    rg -> rcSrc1.y =  70;
                    rg -> rcSrc1.w =  61;
                    rg -> rcSrc1.h =  41;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 5)
                {
                    rg -> rcSrc1.x = 279;
                    rg -> rcSrc1.y =   8;
                    rg -> rcSrc1.w =  55;
                    rg -> rcSrc1.h = 127;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 6)
                {
                    rg -> rcSrc1.x = 141;
                    rg -> rcSrc1.y =   0;
                    rg -> rcSrc1.w = TILE_SIZE;
                    rg -> rcSrc1.h = TILE_SIZE;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
                if (rg -> arr[i][j] == 7)
                {
                    rg -> rcSrc1.x = 279;
                    rg -> rcSrc1.y =   8;
                    rg -> rcSrc1.w =  55;
                    rg -> rcSrc1.h = 127;
                    SDL_RenderCopy(rg -> renderer, backtex, &rg -> rcSrc1, &rg -> rc_Block);
                }
            }
        } //end of for loop

    /* RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
    SDL_RenderCopy(rg -> renderer, spritetex, &rg -> rcObj, &rg -> rcSprite);
    SDL_RenderPresent(rg -> renderer);
    }

    // SDL_Delay(5000);
    SDL_DestroyTexture(backtex);
    SDL_DestroyTexture(spritetex);
    SDL_DestroyRenderer(rg -> renderer);
    SDL_DestroyWindow(rg -> window);
}

//What the fuck are xa and ya?!

void possible(roomGrid *rg, progress *pz)
{
    rg -> xa = (rg -> rcSprite.x) / TILE_SIZE;
    rg -> ya = (rg -> rcSprite.y) / TILE_SIZE;
    rg -> yb = ((rg -> rcSprite.y-1) + TILE_SIZE) / TILE_SIZE;
    rg -> xb = ((rg -> rcSprite.x-1) + TILE_SIZE) / TILE_SIZE;

    switch (rg -> direction)
    {       
        case(left):     if ((rg -> arr[rg -> ya][rg -> xa - 1]) == (rg -> arr[rg -> yb][rg -> xa - 1]))
                        {
                            if(rg -> arr[rg -> yb][rg -> xa - 1] == 0)
                            {
                                move(rg, pz);
                            }
                        };
                        break;

        case(down):     if ((rg -> arr[rg -> yb + 1][rg -> xa]) == (rg -> arr[rg -> yb + 1][rg -> xb]))
                        {
                            if(rg -> arr[rg -> yb + 1][rg -> xa] == 0)
                            {
                                move(rg, pz);
                            }
                        };
                        break;

        case(right):    if ((rg -> arr[rg -> ya][rg -> xb + 1]) == (rg -> arr[rg -> yb][rg -> xb + 1]))
                        {
                            if(rg -> arr[rg -> ya][rg -> xb + 1] == 0)
                            {
                                move(rg, pz);
                            }
                        };
                        break;

        case(up):       if ((rg -> arr[rg -> ya-1][rg -> xa]) == (rg -> arr[rg -> ya-1][rg -> xb]))
                        {
                            if (rg -> arr[rg -> ya - 1][rg -> xa] == 0)
                            {
                                move(rg, pz);
                            }
                        };
                        break;

        default:        fprintf(stderr, "Problem probing!\n");
                        exit(6);
                        break;
     }
}


void move(roomGrid *rg, progress *pz)
{
    switch(rg -> direction)
    {       
        case(left):     (rg -> rcObj.x == 0) ? (rg -> rcObj.x = 32): (rg -> rcObj.x = 0);
                        rg -> rcSprite.x -= 8;
                        break;

        case(down):     (rg -> rcObj.x == 0) ? (rg -> rcObj.x = 32): (rg -> rcObj.x = 0);
                        rg -> rcSprite.y += 8;                  
                        break;

        case(right):    (rg -> rcObj.x == 0) ? (rg -> rcObj.x = 32): (rg -> rcObj.x = 0);
                        rg -> rcSprite.x += 8;
                        break;

        case(up):       (rg -> rcObj.x == 0) ? (rg -> rcObj.x = 32): (rg -> rcObj.x = 0);
                        rg -> rcSprite.y -= 8;
                        break;

        default:        fprintf(stderr, "Problem moving!\n");
                        exit(6);
                        break;
    }
}


void interactProbe(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS])
{
    rg -> xc = (rg -> rcSprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
    rg -> yc = (rg -> rcSprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
    rg -> probe = 0;

    switch (rg -> direction)
    {       
        case(left):     rg -> probe = rg -> arr[rg -> yc][rg -> xc - 1];
                        if (action(rg, pz, instructions_list))
                        {
                            rg -> rcSprite.x += 8;
                        };
                        break;

        case(down):     rg -> probe = rg -> arr[rg -> yc + 1][rg -> xc];
                        if (action(rg, pz, instructions_list))
                        {

                        };
                        break;

        case(right):    rg -> probe = rg -> arr[rg -> yc][rg -> xc + 1];
                        if (action(rg, pz, instructions_list))
                        {

                        };
                        break;

        case(up):       rg -> probe = rg -> arr[rg -> yc - 1][rg -> xc];
                        if (action(rg, pz, instructions_list))
                        {

                        };
                        break;
    }
}


int action(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS])
{
    switch(rg -> probe)
    {
        case(puz_1):        printf("in puz_1 case\n");
                            if ((pz -> puzzle_1) == false){
                                printf("Spaced!\n");

                                neill_notes(rg, instructions_list);

                                pz -> puzzle_1 = true;
                                return 1;
                            }
                            else{
                                printf("Already spaced!\n");

                                first_problem(rg, instructions_list);

                                return 0;
                            }
                            break;

        case(puz_2):        return 0;
                            break;

        case(puz_3):        return 0;
                            break;

        case(puz_4):        return 0;
                            break; 

        case(puz_5):        return 0;
                            break;

        default:            fprintf(stderr, "PANIC!\n");
                            //exit(7);
                            return 0;
                            break;
    }
}

void neill_notes(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS])
{
    rg -> finished = 0;

    //Prints the instructions for the Neill's Notes cutscene.
    print_instruction(rg, instructions_list, 10, 22);
}

void first_problem(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS])
{
    rg -> finished = 0;
    wrong_right correct_indicator = incorrect;

    //Prints first part of the instructions.
    print_instruction(rg, instructions_list, 22, 27);

    //Now we go to the input screen for the text.
	do{
		input_screen(rg, &correct_indicator);
	}while(correct_indicator != correct);

    //Prints second part of the instructions.
	print_instruction(rg, instructions_list, 27, 29);

}

void printArray(roomGrid *rg, progress *pz)
{
    for (int i = 0; i < ROOM_Y; i++){
        for (int j = 0; j < ROOM_X; j++){
            printf("%2d", rg -> arr[i][j]);
        }
        printf("\n");
    }
}


void freeArray(roomGrid *rg)
{
    for (int i = 0; i < ROOM_Y; i++){
        free(rg -> arr[i]);
    }

    free(rg -> arr);
}

//Used to read in and print out the person's input.
void input_screen(roomGrid *rg, wrong_right *correct_indicator)
{
    SDL_Texture* image, *image_one;
    SDL_Surface *text, *text_one;
    SDL_Rect drcrect;
    char input_string[MAX_INPUT_CHARS], possible_answer[MAX_INPUT_CHARS];
    int input_index = 0, finish_checker = unfinished;

    //clear_screen(sw);
    initialise_input_string(input_string);
    initialise_drcrect(&drcrect, input_index);

    text_one = SDL_LoadBMP( "Instructions/code_entry.bmp" );
    if( text_one == NULL )
    {
      printf( "Unable to load image %s! SDL Error: %s\n", "bla", SDL_GetError() );
    }

    image_one = SDL_CreateTextureFromSurface(rg->renderer, text_one);
    TTF_Font *font = TTF_OpenFont("opendisplay.ttf", 200);

    if(font == NULL){
    	printf("\nCouldn't load text.\n");
    }

    SDL_Color fg = { 0, 0, 0, 0};

    do{

        check_user_variable_input(rg, input_string, &input_index, &finish_checker);

        text = TTF_RenderText_Solid(font, input_string, fg) ;
        image = SDL_CreateTextureFromSurface(rg->renderer, text);

        SDL_RenderClear(rg->renderer);
        SDL_RenderCopy(rg->renderer, image_one, NULL, NULL);
        SDL_RenderCopy(rg->renderer, image, NULL, &drcrect);
        SDL_RenderPresent(rg->renderer);

        if(input_index == CHARS_IN_ANS + 1){
          finish_checker = finished;
        }

    }while(input_index < MAX_INPUT_CHARS && !finish_checker);

    create_answer_for_checking(possible_answer, input_string);

    if( strcmp(possible_answer, "fan < too hot") == 0){
        *correct_indicator = correct;
    }
}

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS])
{
  int i;

  for(i = 0; i < CHARS_IN_ANS; ++i){
        possible_answer[i] = input_string[i];
    }

  possible_answer[CHARS_IN_ANS] = '\0';
}

void initialise_input_string(char input_string[MAX_INPUT_CHARS])
{
  int i;

  for(i = 0; i < MAX_INPUT_CHARS; ++i){
        input_string[i] = ' ';
    }
}

void initialise_drcrect(SDL_Rect *drcrect, int input_index)
{
  drcrect->x = RECT_X;
  drcrect->y = RECT_Y;
  drcrect->w = RECT_W * (input_index + 1);
  drcrect->h = RECT_H;
}

void check_user_variable_input(roomGrid *rg, char *input_string, int *input_index, int *finish_checker)
{
  //To identify event.
  SDL_Event event;

  int gameover = 0;

  while (gameover != INPUT_FINISHED){                                                                 //to make screen stay on.
    while( SDL_PollEvent( &event ) ){                                                                 //checks for events.
      if(event.type == SDL_KEYDOWN){                                                                  //checks for key being pressed
        char c = event.key.keysym.sym;                                                                //if the key is pressed assigns character
        if( (c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) ){
              if(c == ','){
                input_string[*input_index] = '<';
              }
              else if(c == '.'){
                input_string[*input_index] = '>';
              }
              else{
                input_string[*input_index] = c;
              }                                                                                     //puts all pressed characters in an array.
              ++(*input_index);                                                                     //adds one to the index.
              gameover = INPUT_FINISHED;
        }
        else if( c == '\b'){
          input_string[--(*input_index)] = ' ';
          gameover = INPUT_FINISHED; 
        }
        else if(c == '\r'){
          *finish_checker = finished;
          gameover = INPUT_FINISHED; 
        }
      }
    }
  }              

  input_string[MAX_INPUT_CHARS] = '\0';                                                               //concludes string

}