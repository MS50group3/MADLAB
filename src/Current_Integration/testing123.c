//put james' shit in structs


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
#define MOVEMENT_INCREMENT 		  8
#define WALL                      1
#define BLANK                     0

// TYPEDEFS AND ENUMERATION

enum compass{up = 0, right = 1, down = 2, left = 3};
typedef enum compass compass;

enum tileType{path = 0, obstacle = 1, puz_1 = 2, puz_2 = 3, puz_3 = 4, puz_4 = 5, puz_5 = 6};
typedef enum tileType tileType;

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum on_off {off, on};
typedef enum on_off on_off;

enum menu_options{new_game = 1, load_game = 2, options = 3,  editor = 4, in_option_screen = 7};
typedef enum menu_options menu_options;

typedef struct roomGrid
{
    int **room_array;
    compass direction;
    SDL_Rect rcSprite, rcSrc1, rcObj, rcSrc3, rc_Block;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_bool finished;
    bool gamerunning;
    int left_x_coord;
    int right_x_coord;
    int bottom_y_coord;
    int top_y_coord;
    int x_sprite_centre;
    int y_sprite_centre;
    int probe;
    int skip_checker;
    int problem_quitter;
    int refresh_counter;
    Mix_Chunk *mus;
    int paused;
}roomGrid;

typedef struct Chicken
{
    SDL_Rect rcChicken;
    compass chick_facing;
    int chick_probe;
    int chick_lx_coord;
    int chick_rx_coord;
    int chick_by_coord;
    int chick_ty_coord;
    int x_chick_centre;
    int y_chick_centre;
}Chicken;


typedef struct progress
{   
    bool puzzle_1;
    bool puzzle_2;
    bool puzzle_3;
    bool puzzle_4;
    bool puzzle_5;
}progress;

struct cursor{
    int x; 
    int y; 
    int tileID;
}; 
typedef struct cursor cursor;

struct input{
    int mouse_x; 
    int mouse_y;
    int add; 
    int remove;
};
typedef struct input input;

struct map{
    int width; 
    int height;
};
typedef struct map map;


//FUNCTIONS FOR PROBLEMS

void print_instruction(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS], int start, int end);
void James_SDL_Events(roomGrid *room_grid);
void print_instruction_to_screen(roomGrid *room_grid, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);
void look_for_action(roomGrid *room_grid);
void SDL_QuitChecker(roomGrid *room_grid);
void initialise_SDL_component(SDL_Window *window, roomGrid *room_grid);
void neill_notes(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS]);
void first_problem(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS]);
void input_screen(roomGrid *room_grid, wrong_right *correct_indicator);
void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS]);
void initialise_input_string(char input_string[MAX_INPUT_CHARS]);
void initialise_drcrect(SDL_Rect *drcrect, int input_index);
void check_user_variable_input(roomGrid *room_grid, char *input_string, int *input_index, int *finish_checker);

//FUNCTIONS FOR MOVEMENT

void makeRoom(roomGrid *room_grid, FILE *map_file);
void print_room_array(roomGrid *room_grid, progress *puzzle);
void draw(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen);
void run_main_game(roomGrid *room_grid, progress *puzzle, Chicken *hen);
void free_room_array(roomGrid *room_grid);
void sound_on_off(roomGrid *room_grid);
void possible(roomGrid *room_grid, progress *puzzle);
int action(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen);
void interactProbe(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen);
void move(roomGrid *room_grid, progress *puzzle);
void initialise_roomgrid_components(roomGrid *room_grid, progress *puzzle);
void initialise_chicken(Chicken *hen, roomGrid *room_grid);
void changeChickenDirection(Chicken *hen);
void position_sprite(roomGrid *room_grid);
void movement(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen);
void collision_detection(roomGrid *room_grid);
void draw_room(SDL_Surface *background, /*SDL_Surface *sprite,*/ SDL_Texture *backtex, /*SDL_Texture *spritetex,*/ roomGrid *room_grid);
void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *backtex, roomGrid *room_grid);

//FUNCTIONS FOR MENU

void run_menu_screen(roomGrid *room_grid);
void load_menu_frame(roomGrid *room_grid);
void highlight_area(roomGrid *room_grid, int current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex);
bool getEvent(roomGrid *room_grid);
void cycle_options(roomGrid *room_grid);
void getloadscreenevent(roomGrid *room_grid);
void getkeyEvent(roomGrid *room_grid, int x);
void runloadscreen();
void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running);
void level_editor(roomGrid *room_grid);
void initialise_level_editor_map(int array[ROOM_Y][ROOM_X]);
void load_image(roomGrid *room_grid, SDL_Surface **surf, SDL_Texture **tex, char *image_name);
void editor_interactions(int map_array[ROOM_Y][ROOM_X], bool *running, input *input);
void configure_mouse(int excess, int *tile_x, int *tile_y, input input, cursor cursor, SDL_Rect *cursor_src, SDL_Rect *cursor_dst, SDL_Rect *tile_src);
void draw_edited_map(int map_array[ROOM_Y][ROOM_X], input input, int tile_x, int tile_y, SDL_Texture *tile_tex, SDL_Rect tile_src, SDL_Rect tile_dst, 
                     roomGrid *room_grid, SDL_Texture *cursor_tex, SDL_Rect cursor_src, SDL_Rect cursor_dst, SDL_Texture *back_tex);

//MAIN

int main(int aroom_gridc, char *argv[])
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    Chicken Fowl, *hen;
    hen = &Fowl;

    FILE *map_file = NULL;
    map_file = fopen(argv[1], "r");

    if (map_file == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    printf("File was opened.\n");

    makeRoom(room_grid, map_file);

    fclose(map_file);

    run_menu_screen(room_grid);

    run_main_game(room_grid, puzzle, hen);

    print_room_array(room_grid, puzzle);

    free_room_array(room_grid);

    return(0);
}

// FUNCTION DEFINITIONS

//Used to make the room from the scanned file.
void makeRoom(roomGrid *room_grid, FILE *map_file)
{
    int i, j;

    room_grid -> room_array = 0;
    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));

    if (room_grid -> room_array == NULL){

        fprintf(stderr, "No memory available.\n");
        exit(3);

    }

    for (i = 0; i <= ROOM_Y; i++){
        room_grid -> room_array[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        if (room_grid -> room_array[i] ==  NULL){

            fprintf(stderr, "No memory available.\n");
            exit(4);

        }
    }

    for (i = 0; i < ROOM_Y; i++){
        for (j = 0; j < ROOM_X; j++){
            if (fscanf(map_file, "%1d", &room_grid -> room_array[i][j]) == 1);
            else{

                fprintf(stderr, "Invalid room_array size.\n");
                exit(5);

            }
        }
    }
}

//The main part of the game running problems and movement etc.
void run_main_game(roomGrid *room_grid, progress *puzzle, Chicken *hen)
{
    char *instructions_list[NUM_INSTRUCTIONS];

    get_instructions(instructions_list);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, MUSIC_CONST_ONE, MUSIC_CONST_TWO);
    room_grid -> mus = Mix_LoadWAV("20141124b.wav");

    //Prints the opening scene.
    print_instruction(room_grid, instructions_list, 0, 10);

    draw(room_grid, puzzle, instructions_list, hen);

    atexit(SDL_Quit);

    //Mix_HaltMusic(); 
    //Mix_FreeChunk(mus); 
    //Mix_CloseAudio();  
   // Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

//Used to initialise all of the necessary components of SDL.
void initialise_SDL_component(SDL_Window *window, roomGrid *room_grid)
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

    //Initialize PNG loading.
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){ 
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    //Initialise renderer.
    if ((room_grid -> renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL){
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
void print_instruction(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS], int start, int end)
{
    int i;
    room_grid->finished = unfinished;
    room_grid -> problem_quitter = off;

    for (i = start; i < end; ++i){
        if(room_grid -> problem_quitter == off){
            print_instruction_to_screen(room_grid, instructions_list[i]);
        }
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
void print_instruction_to_screen(roomGrid *room_grid, char *instruction)
{
    room_grid->refresh_counter = 0;
    room_grid->skip_checker = off;
    SDL_Surface* image_surf = NULL;
    SDL_Texture* image_tex;

    // The following few lines are used to create a filename to get the .bmp to print to screen.
    char prefix[LENGTH_PREFIX] = "Instructions/";
    char extension[LENGTH_EXTENSION] = ".bmp";
    char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1);

    strcpy(filename, prefix);
    strcat(filename, instruction);
    strcat(filename, extension);

    // Loads image in and checks it.
    image_surf = SDL_LoadBMP(filename);

    if (image_surf == NULL){
        printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    }

    image_tex = SDL_CreateTextureFromSurface(room_grid -> renderer, image_surf);

    // Update the surface and apply the image.
    SDL_RenderCopy(room_grid -> renderer, image_tex, NULL, NULL);
    SDL_RenderPresent(room_grid -> renderer);

    // Wait the sleep time and free the malloc for the filename.
    look_for_action(room_grid);

    free(filename);
}

//Looks for actions relating to skipping or quitting.
void James_SDL_Events(roomGrid *room_grid)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)){

       switch (event.type){

            case SDL_QUIT:
                room_grid -> finished = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                room_grid -> skip_checker = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_x:
                        room_grid -> problem_quitter = on;
                        break;
                    case SDLK_SPACE:
                        room_grid -> skip_checker = 1;
                        break;
                }
        }
    }
}

//The refresh counter is used to delay a certain time whilst looking for exits.
void look_for_action(roomGrid *room_grid)
{
    do
    {
        ++(room_grid -> refresh_counter);
        SDL_Delay(SLEEP_TIME);
        SDL_QuitChecker(room_grid);
    }
    while(room_grid -> refresh_counter < NUM_REFRESHES && !room_grid -> skip_checker && !room_grid -> problem_quitter);
}


void SDL_QuitChecker(roomGrid *room_grid)
{
    James_SDL_Events(room_grid);
    if (room_grid -> finished){
        exit(1);
    }
}


void draw(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
    SDL_Surface *background, *sprite, *chicken;
    SDL_Texture *backtex, *spritetex, *chickentex;

    load_image(room_grid, &background, &backtex, "lab1sheet.png");
    load_image(room_grid, &sprite, &spritetex, "prof2.png");
    load_image(room_grid, &chicken, &chickentex, "chicken.png");

    initialise_roomgrid_components(room_grid, puzzle);
    position_sprite(room_grid);
    Mix_PlayChannel(-1, room_grid -> mus, -1);

    while (room_grid -> gamerunning)
    {
        
        movement(room_grid, puzzle, instructions_list, hen);     
        collision_detection(room_grid);
        SDL_RenderClear(room_grid -> renderer);
        draw_room(background, /*sprite,*/ backtex, /*spritetex,*/ room_grid);

        /*RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
        SDL_RenderCopy(room_grid -> renderer, spritetex, &room_grid -> rcObj, &room_grid -> rcSprite);
        SDL_RenderPresent(room_grid -> renderer);
    }

    // SDL_Delay(5000);
    SDL_DestroyTexture(backtex);
    SDL_DestroyTexture(spritetex);
    SDL_DestroyTexture(chickentex);
    SDL_DestroyRenderer(room_grid -> renderer);
    SDL_DestroyWindow(room_grid -> window);
}


void draw_room(SDL_Surface *background, /*SDL_Surface *sprite,*/ SDL_Texture *backtex, /*SDL_Texture *spritetex,*/ roomGrid *room_grid)
{
    for (int i = 0; i <= ROOM_Y; i++){
        for (int j = 0; j < ROOM_X; j++){

            room_grid -> rc_Block.x = (j * TILE_SIZE);  // set the room_array location to the tile size and Block size
            room_grid -> rc_Block.y = (i * TILE_SIZE);

            //First ground tile does not go in a loop. It populates everything so just draw it. 
            //You also free up 0!
            rcsrc_set(41, 0, 32, 29, backtex, room_grid);
            
            if (room_grid -> room_array[i][j] == 1){
                rcsrc_set(71, 81, 45, 34, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 2){
                rcsrc_set(73, 0, 32, 29, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 3){
                rcsrc_set(121, 56, 76, 59, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 4){
                rcsrc_set(207, 70, 61, 41, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 5){
                rcsrc_set(279, 8, 55, 127, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 6){
                rcsrc_set(141, 0, 32, 32, backtex, room_grid);
            }

            if (room_grid -> room_array[i][j] == 7){
                rcsrc_set(279, 8, 55, 127, backtex, room_grid);
            }
        }
    }
}


void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *backtex, roomGrid *room_grid)
{
    room_grid -> rcSrc1.x = x_coord;
    room_grid -> rcSrc1.y = y_coord;
    room_grid -> rcSrc1.w = width;
    room_grid -> rcSrc1.h = height;

    SDL_RenderCopy(room_grid -> renderer, backtex, &room_grid -> rcSrc1, &room_grid -> rc_Block);
}


void initialise_roomgrid_components(roomGrid *room_grid, progress *puzzle)
{
    room_grid -> gamerunning = true;
    puzzle -> puzzle_1 = false;
    room_grid -> paused = 0;
    room_grid -> left_x_coord = 0;
    room_grid -> bottom_y_coord = 0;
    room_grid -> top_y_coord = 0;
    room_grid -> direction = 0;
}


void initialise_chicken(Chicken *hen, roomGrid *room_grid)
{
    // hen -> facing = room_grid -> facing;
    // hen -> 
    hen -> chick_lx_coord = 0;
    hen -> chick_rx_coord = 0;
    hen -> chick_by_coord = 0;
    hen -> chick_ty_coord = 0;
    hen -> x_chick_centre = 0;
    hen -> y_chick_centre = 0;
}


void position_sprite(roomGrid *room_grid)
{

    /* set sprite "source" position - as called by RenderCopy, choose which to be */
    room_grid -> rcSprite.y = TILE_SIZE*3;
    room_grid -> rcSprite.x = TILE_SIZE*3;
    room_grid -> rcSprite.w = TILE_SIZE;
    room_grid -> rcSprite.h = TILE_SIZE;

    room_grid -> rcObj.x = 0;  
    room_grid -> rcObj.y = 0;
    room_grid -> rcObj.w = TILE_SIZE;
    room_grid -> rcObj.h = TILE_SIZE;

    room_grid -> rc_Block.w = TILE_SIZE;
    room_grid -> rc_Block.h = TILE_SIZE;
}


void position_chicken(Chicken *hen, roomGrid *room_grid)
{
    //SDL_RenderCopy(room_grid -> renderer, chickentex, &hen -> rcChicken);
    hen -> rcChicken.y = 400;
    hen -> rcChicken.x = 320;
    hen -> rcChicken.w = TILE_SIZE;
    hen -> rcChicken.h = TILE_SIZE;
}


void movement(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
    SDL_Delay(20);
    SDL_Event event;  // call SDL_Event
        if (SDL_PollEvent(&event))  // If there is an event
        {
        // HandleEvent(event, rcSrc, rcSprite); //Run the HandleEvent function
        switch (event.type) 
        {
            case SDL_QUIT:
                room_grid -> gamerunning = false;
                break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_q:
                    room_grid -> gamerunning = false;
                    break;
                case SDLK_LEFT:
                    room_grid -> direction = left;
                    (!((room_grid -> rcSprite.x) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_RIGHT:
                    room_grid -> direction = right;
                    (!((room_grid -> rcSprite.x) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_UP:
                    room_grid -> direction = up;
                    (!((room_grid -> rcSprite.y) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_DOWN:
                    room_grid -> direction = down;
                    (!((room_grid -> rcSprite.y) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_SPACE:
                    interactProbe(room_grid, puzzle, instructions_list, hen);
                    break;
                case SDLK_9:
                    sound_on_off(room_grid);
                    break;
            }
            break;
        }
    }
}


void sound_on_off(roomGrid *room_grid)
{
    if (room_grid -> paused == off)
    {
        Mix_Pause(-1);
        room_grid -> paused = on;      
    }

    else if (room_grid -> paused == on)
    {
        Mix_Resume(-1);
        room_grid -> paused = off;
    }
}


void collision_detection(roomGrid *room_grid)
{
    //Left edge.
    if (room_grid -> rcSprite.x <= 0){
        room_grid -> rcSprite.x = 0;
    }
    //Right edge
    if (room_grid -> rcSprite.x >= SCREEN_WIDTH - TILE_SIZE){
        room_grid -> rcSprite.x = SCREEN_WIDTH - TILE_SIZE;
    }
    //Top edge
    if (room_grid -> rcSprite.y <= 0){
        room_grid -> rcSprite.y = 0;
    }
    //Bottom edge
    if (room_grid -> rcSprite.y >= SCREEN_HEIGHT - TILE_SIZE){ 
        room_grid -> rcSprite.y = SCREEN_HEIGHT - TILE_SIZE;
    }

    SDL_RenderClear(room_grid -> renderer);
}

void possible(roomGrid *room_grid, progress *puzzle)
{
    room_grid -> left_x_coord = (room_grid -> rcSprite.x) / TILE_SIZE;
    room_grid -> top_y_coord = (room_grid -> rcSprite.y) / TILE_SIZE;
    room_grid -> bottom_y_coord = ((room_grid -> rcSprite.y - 1) + TILE_SIZE) / TILE_SIZE;
    room_grid -> right_x_coord = ((room_grid -> rcSprite.x - 1) + TILE_SIZE) / TILE_SIZE;

    switch (room_grid -> direction)
    {       
        case(left):     if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> left_x_coord - 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1])){
                            if(room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1] == 0){

                                move(room_grid, puzzle);

                            }
                        };
                        break;

        case(down):     if ((room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> right_x_coord])){
                            if(room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord] == 0){

                                move(room_grid, puzzle);

                            }
                        };
                        break;

        case(right):    if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> right_x_coord + 1])){
                            if(room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1] == 0){

                                move(room_grid, puzzle);

                            }
                        };
                        break;

        case(up):       if (room_grid -> rcSprite.y != 0)
                        {
                            if ((room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> right_x_coord])){
                            if (room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord] == 0){

                                move(room_grid, puzzle);
                        }      
                        }
                        };
                        break;

        default:        fprintf(stderr, "Problem probing!\n");
                        exit(6);
                        break;
     }
}


void move(roomGrid *room_grid, progress *puzzle)
{
    switch(room_grid -> direction)
    {       
        case(left):     (room_grid -> rcObj.x == 224) ? (room_grid -> rcObj.x = 256): (room_grid -> rcObj.x = 224);
                        room_grid -> rcSprite.x -= MOVEMENT_INCREMENT;
                        break;

        case(down):     (room_grid -> rcObj.x == 96) ? (room_grid -> rcObj.x = 128): (room_grid -> rcObj.x = 96);
                        room_grid -> rcSprite.y += MOVEMENT_INCREMENT;                  
                        break;

        case(right):    (room_grid -> rcObj.x == 160) ? (room_grid -> rcObj.x = 192): (room_grid -> rcObj.x = 160);
                        room_grid -> rcSprite.x += MOVEMENT_INCREMENT;
                        break;

        case(up):       (room_grid -> rcObj.x == 32) ? (room_grid -> rcObj.x = 64): (room_grid -> rcObj.x = 32);
                        room_grid -> rcSprite.y -= MOVEMENT_INCREMENT;
                        break;

        default:        fprintf(stderr, "Problem moving!\n");
                        exit(6);
                        break;
    }
}


void interactProbe(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
    room_grid -> x_sprite_centre = (room_grid -> rcSprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
    room_grid -> y_sprite_centre = (room_grid -> rcSprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
    room_grid -> probe = 0;

    switch (room_grid -> direction)
    {       
        case(left):     room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre][room_grid -> x_sprite_centre - 1];
                        if (action(room_grid, puzzle, instructions_list, hen)){

                        };
                        break;

        case(down):     room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre + 1][room_grid -> x_sprite_centre];
                        if (action(room_grid, puzzle, instructions_list, hen)){

                        };
                        break;

        case(right):    room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre][room_grid -> x_sprite_centre + 1];
                        if (action(room_grid, puzzle, instructions_list, hen)){

                        };
                        break;

        case(up):       if (room_grid -> rcSprite.y != 0)
                        {
                            room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre - 1][room_grid -> x_sprite_centre];
                            if (action(room_grid, puzzle, instructions_list, hen)){
                            }
                        };
                        break;
    }
}


int action(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
    switch(room_grid -> probe)
    {
        case(puz_1):        printf("in puz_1 case\n");
                            if ((puzzle -> puzzle_1) == false){
                                printf("Spaced!\n");

                                neill_notes(room_grid, instructions_list);

                                puzzle -> puzzle_1 = true;
                                return 1;
                            }
                            else{
                                printf("Already spaced!\n");

                                first_problem(room_grid, instructions_list);

                                return 0;
                            }
                            break;

        case(puz_2):        return 0;
                            break;

        case(puz_3):        return 0;
                            break;

        case(puz_4):        return 0;
                            break; 

        case(puz_5):        initialise_chicken(hen, room_grid); 
                            printf("Bring out the chicken!\n");
                            return 0;
                            break;

        default:            fprintf(stderr, "PANIC!\n");
                            return 0;
                            break;
    }
}


void changeChickenDirection(Chicken *hen)
{
    if (hen -> chick_facing == left)
    {
        hen -> chick_facing = up;
    }
    else
    {
        hen -> chick_facing++;
    }
}


void neill_notes(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS])
{
    room_grid -> finished = 0;

    //Prints the instructions for the Neill's Notes cutscene.
    print_instruction(room_grid, instructions_list, 10, 22);
}

void first_problem(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS])
{
    room_grid -> finished = 0;
    wrong_right correct_indicator = incorrect;

    //Prints first part of the instructions.
    print_instruction(room_grid, instructions_list, 22, 27);

    //Now we go to the input screen for the text.
    while(correct_indicator != correct && room_grid -> problem_quitter == off){
        input_screen(room_grid, &correct_indicator);
    }

    //Prints second part of the instructions.
    if(room_grid -> problem_quitter == off){
        print_instruction(room_grid, instructions_list, 27, 29);
    }

}

void print_room_array(roomGrid *room_grid, progress *puzzle)
{
    for (int i = 0; i < ROOM_Y; i++){
        for (int j = 0; j < ROOM_X; j++){
            printf("%2d", room_grid -> room_array[i][j]);
        }
        printf("\n");
    }
}


void free_room_array(roomGrid *room_grid)
{
    for (int i = 0; i < ROOM_Y; i++){
        free(room_grid -> room_array[i]);
    }

    free(room_grid -> room_array);
}

//Used to read in and print out the person's input.
void input_screen(roomGrid *room_grid, wrong_right *correct_indicator)
{
    SDL_Texture* image, *image_one;
    SDL_Surface *text, *text_one;
    SDL_Rect drcrect;
    char input_string[MAX_INPUT_CHARS], possible_answer[MAX_INPUT_CHARS];
    int input_index = 0, finish_checker = unfinished;

    initialise_input_string(input_string);
    initialise_drcrect(&drcrect, input_index);

    text_one = SDL_LoadBMP( "Instructions/code_entry.bmp" );
    if( text_one == NULL )
    {
      printf( "Unable to load image %s! SDL Error: %s\n", "bla", SDL_GetError() );
    }

    image_one = SDL_CreateTextureFromSurface(room_grid->renderer, text_one);
    TTF_Font *font = TTF_OpenFont("opendisplay.ttf", 200);

    if(font == NULL){
        printf("\nCouldn't load text.\n");
    }

    SDL_Color fg = { 0, 0, 0, 0};

    do{

        check_user_variable_input(room_grid, input_string, &input_index, &finish_checker);

        text = TTF_RenderText_Solid(font, input_string, fg) ;
        image = SDL_CreateTextureFromSurface(room_grid->renderer, text);

        SDL_RenderClear(room_grid->renderer);
        SDL_RenderCopy(room_grid->renderer, image_one, NULL, NULL);
        SDL_RenderCopy(room_grid->renderer, image, NULL, &drcrect);
        SDL_RenderPresent(room_grid->renderer);

        if(input_index == CHARS_IN_ANS + 1){
          finish_checker = finished;
        }

    }while(input_index < MAX_INPUT_CHARS && !finish_checker);

    create_answer_for_checking(possible_answer, input_string);

    if( strcmp(possible_answer, "fan < too hot") == 0){
        *correct_indicator = correct;
    }

    look_for_action(room_grid);
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

void check_user_variable_input(roomGrid *room_grid, char *input_string, int *input_index, int *finish_checker)
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
              }                                                                                      //puts all pressed characters in an room_array.
              ++(*input_index);                                                                      //adds one to the index.
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

void run_menu_screen(roomGrid *room_grid)
{
    static int first_pass = 0;

    if(first_pass == 0){
        initialise_SDL_component(room_grid->window, room_grid);
        ++first_pass;
    }

    load_menu_frame(room_grid);
    
    cycle_options(room_grid);

}

void save(int array[ROOM_Y][ROOM_X]){
    
    FILE *writing_file;

    writing_file = fopen("Your_level.txt","w");
    if(writing_file == NULL) {
        printf("ERROR opening file...exiting\n");
    }
    
    for (int i = 0; i < ROOM_Y; ++i)
    {
        for (int j = 0; j < ROOM_X; ++j)
        {
            fprintf(writing_file, "%d ", array[i][j]);
        }
        
        fprintf(writing_file,"\n");
    }
    
    fclose(writing_file);
}

void level_editor(roomGrid *room_grid)
{
    
    bool running = true;
    input input;
    cursor cursor;
    
    input.add = 0;
    input.remove = 0;
    
    int map_array[ROOM_Y][ROOM_X];
    
    initialise_level_editor_map(map_array);
    
    // Background, tile, cursor and menu stuff
    SDL_Surface *back_surf, *tile_surf, *cursor_surf, *menu_surf, *options_surf;
    SDL_Texture *back_tex, *tile_tex, *cursor_tex, *menu_tex, *options_tex;
    SDL_Rect tile_src, tile_dst, cursor_src, cursor_dst;
    
    // Make the tile
    load_image(room_grid, &tile_surf, &tile_tex, "block.png");

    // Make the cursor
    cursor_surf = IMG_Load("cursor.png");
    Uint32 colorkey = SDL_MapRGB(cursor_surf->format, 127, 0, 127);

    SDL_SetColorKey( cursor_surf, SDL_TRUE, colorkey);
    cursor_tex = SDL_CreateTextureFromSurface(room_grid -> renderer, cursor_surf);

    SDL_FreeSurface (cursor_surf);
    
    // Make the background
    load_image(room_grid, &back_surf, &back_tex, "labtile2.png");    
    
    // Run the meat of the program.
    while(running){

        int excess = 0, tile_x = 0, tile_y = 0;
        
        editor_interactions(map_array, &running, &input);
        
        // Get the mouse coords
        SDL_GetMouseState(&input.mouse_x, &input.mouse_y);

        configure_mouse(excess, &tile_x, &tile_y, input, cursor, &cursor_src, &cursor_dst, &tile_src);

        draw_edited_map(map_array, input, tile_x, tile_y, tile_tex, tile_src, tile_dst, room_grid, cursor_tex, cursor_src, cursor_dst, back_tex);
        
    }
    
    load_menu_frame(room_grid);

    load_image(room_grid, &menu_surf, &menu_tex, "screen2.png");

    load_image(room_grid, &options_surf, &options_tex, "controls.png");
    
    highlight_area(room_grid, editor, menu_tex, options_tex);
    
}

void draw_edited_map(int map_array[ROOM_Y][ROOM_X], input input, int tile_x, int tile_y, SDL_Texture *tile_tex, SDL_Rect tile_src, SDL_Rect tile_dst, 
                     roomGrid *room_grid, SDL_Texture *cursor_tex, SDL_Rect cursor_src, SDL_Rect cursor_dst, SDL_Texture *back_tex)
{

    if(input.add == 1)
    {
        map_array[tile_y][tile_x] = WALL;
    }
    
    if (input.remove == 1)
    {
        map_array[tile_y][tile_x] = BLANK;
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
            
            if (map_array[i][j] == WALL)
            {   
                // If the array element is a 1, draw a wall
                SDL_RenderCopy(room_grid -> renderer, tile_tex, &tile_src, &tile_dst);
            }
            else if ( map_array[i][j] == BLANK)
            {   // If the element is a 0, draw a floor tile
                SDL_RenderCopy(room_grid -> renderer, back_tex, &tile_src, &tile_dst);
            }
        }
    }

    SDL_RenderCopy(room_grid -> renderer, cursor_tex, &cursor_src, &cursor_dst);
    
    // Update the screen with the latest render 
    SDL_RenderPresent(room_grid -> renderer);
        
}

void configure_mouse(int excess, int *tile_x, int *tile_y, input input, cursor cursor, SDL_Rect *cursor_src, SDL_Rect *cursor_dst, SDL_Rect *tile_src)
{
    // Round the coords to the nearest multiple of TILE_SIZE
    excess = input.mouse_x % TILE_SIZE;
    input.mouse_x = input.mouse_x - excess;
    
    excess = input.mouse_y % TILE_SIZE;
    input.mouse_y = input.mouse_y - excess;
    
    // Which tile 'element' are we in
    *tile_x = input.mouse_x / TILE_SIZE;
    *tile_y = input.mouse_y / TILE_SIZE;
    
    // curstor details
    cursor.x = input.mouse_x;
    cursor.y = input.mouse_y;
    
    // Where to get the image from (relative)
    cursor_src->y = 0;
    cursor_src->x = 0;
    cursor_src->w = TILE_SIZE;
    cursor_src->h = TILE_SIZE;
    
    // Where to put it (relative)
    cursor_dst->y = cursor.y;
    cursor_dst->x = cursor.x;
    cursor_dst->w = TILE_SIZE;
    cursor_dst->h = TILE_SIZE;
    
    tile_src->y=0;
    tile_src->x=0;
    tile_src->w=TILE_SIZE;
    tile_src->h=TILE_SIZE;
}

void editor_interactions(int map_array[ROOM_Y][ROOM_X], bool *running, input *input)
{
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
                    *running = false;
                    break;
                    
                case SDLK_s:
                    save(map_array);
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
                    input -> add = 1;
                    break;
                    
                case SDL_BUTTON_RIGHT:
                    input -> remove = 1;
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
                    input -> add = 0;
                    break;
                    
                case SDL_BUTTON_RIGHT:
                    input -> remove = 0;
                    break;
                    
                default:
                    break;
            }
                break;
        }
    }
}

void initialise_level_editor_map(int map_array[ROOM_Y][ROOM_X])
{
    int i, j;

    for (i = 0; i < ROOM_Y; ++i) {
        for (j = 0; j < ROOM_X; ++j) {
            map_array[i][j] = 0;
        }
    }

}


// Draw original backgroud
void load_menu_frame(roomGrid *room_grid)
{

    SDL_Surface *background_surf;
    SDL_Texture *background_tex;

    load_image(room_grid, &background_surf, &background_tex, "screen1.png");

    SDL_RenderCopy(room_grid -> renderer, background_tex, NULL, NULL);
    SDL_RenderPresent(room_grid -> renderer);

}

//draw correct part of background image each time (a rectangular box around the written options)
void highlight_area(roomGrid *room_grid, int current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex){
    
   SDL_Rect tile_src, tile_drc;

   //Draw original background.
   load_menu_frame(room_grid);

    if(current_selection == new_game){
        tile_src = (SDL_Rect) {333,442,143,31};
        tile_drc = (SDL_Rect) {333,472,143,31};
    }
    else if(current_selection == load_game){
        tile_src = (SDL_Rect) {336,473,143,31};
        tile_drc = (SDL_Rect) {336,504,143,31};
    }
    else if(current_selection == options){
        tile_src = (SDL_Rect) {344,499,119,32};
        tile_drc = (SDL_Rect) {344,532,119,32};

    }
    else if(current_selection == editor){
        tile_src = (SDL_Rect) {331,526,140,30};
        tile_drc = (SDL_Rect) {331,560,140,30};
    }

    if(current_selection == new_game || current_selection == load_game || current_selection == options || current_selection == editor){
        SDL_RenderCopy(room_grid -> renderer, menu_tex, &tile_src, &tile_drc);
        SDL_RenderPresent(room_grid -> renderer);
    }
    else if(current_selection == in_option_screen){ 
        //Draw controls screen
        SDL_RenderCopy(room_grid -> renderer, options_tex, NULL, NULL);
        SDL_RenderPresent(room_grid -> renderer);;
       
    }
   
}

void cycle_options(roomGrid *room_grid){
    
    SDL_Event event;
    bool menu_running = true;
    int current_selection = new_game;

    SDL_Surface *menu_surf = NULL, *options_surf = NULL;
    SDL_Texture *menu_tex = NULL, *options_tex = NULL;

    load_image(room_grid, &menu_surf, &menu_tex, "screen2.png");

    load_image(room_grid, &options_surf, &options_tex, "controls.png");
    
    highlight_area(room_grid, current_selection, menu_tex, options_tex);

    while(menu_running)
    {
        
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(1);
                    break;
                    
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        if( current_selection == load_game || current_selection == options || current_selection == editor ){
                            current_selection--;
                        }
                        highlight_area(room_grid, current_selection, menu_tex, options_tex);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if( current_selection == new_game || current_selection == load_game || current_selection == options ){
                            current_selection++;
                        }
                        highlight_area(room_grid, current_selection, menu_tex, options_tex);
                        break;   
                    }
                        
                    case SDLK_SPACE:

                        menu_space_press(room_grid, &current_selection, menu_tex, options_tex, &menu_running);
                
                }
            }
        
        }
    
    }
}

void load_image(roomGrid *room_grid, SDL_Surface **surf, SDL_Texture **tex, char *image_name)
{
    *surf = IMG_Load(image_name);
    *tex = SDL_CreateTextureFromSurface(room_grid -> renderer, *surf);
    SDL_FreeSurface(*surf);
}

void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running)
{
    SDL_Event event;

    if( *current_selection == new_game ){
        *menu_running = false;
    }

    if( *current_selection == options){

        highlight_area(room_grid, in_option_screen, menu_tex, options_tex);

        while( *current_selection == options ){
            if(SDL_PollEvent(&event)){

                switch(event.type){

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                        case SDLK_SPACE:
                        
                            *current_selection = new_game;
                            highlight_area(room_grid, *current_selection, menu_tex, options_tex);
                            break;
                            
                    }
                }
            }
        }
    }
    
    if( *current_selection == editor ){

        //Option 4 opens editor/level builder
        level_editor(room_grid);

    }

}