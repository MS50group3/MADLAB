// PREPROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define SCREEN_WIDTH     		800
#define SCREEN_HEIGHT    		640
#define TILE_SIZE         		 32
#define ROOM_X            		 25
#define ROOM_Y            		 20
#define SPRITE_VEL         		  5
#define SDL_8BITCOLOUR   		256
#define SLEEP_TIME       		100
#define NUM_INSTRUCTIONS  		 62
#define LENGTH_EXTENSION   		  5
#define LENGTH_PREFIX     		 14
#define NUM_REFRESHES     		 50
#define MAX_INPUT_CHARS  		 20
#define INPUT_FINISHED    100000000
#define RECT_X  				190
#define RECT_Y  				255
#define RECT_W  				700
#define RECT_H  				150
#define SUCCESSFUL                0
#define MUSIC_CONST_ONE           2
#define MUSIC_CONST_TWO        4096
#define MOVEMENT_INCREMENT 		  8
#define WALL                      1
#define ALT                       2
#define BLANK                     0
#define NUM_DIRECTIONS            4

#define MAX_NUM_LINES 1000
#define MAX_SIZE_OF_LINE 1000
#define CLEAR_SUCCESS 0
#define NUM_LETTERS_ALPHABET 26
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %sOccured in %s, line %d\n\n", PHRASE, __FILE__, __LINE__); exit(1); }
#define RADIANS_CONST 0.0174532925
#define ERROR_VALUE -1000
#define MAX_STACK_SIZE 1000
#define START_ITERATION_END 5
#define MAX_EMBEDDED_LOOPS 1000
#define MIDDLE_OF_BOARD 320
#define WWIDTH            800
#define WHEIGHT           640


// TYPEDEFS AND ENUMERATION

enum compass{up = 0, right = 1, down = 2, left = 3};
typedef enum compass compass;

enum tileType{path = 0, obstacle = 1, puz_1 = 9, puz_2 = 3, puz_3 = 1, puz_4 = 7, puz_5 = 6, puz_6 = 5};
typedef enum tileType tileType;

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum on_off {off, on};
typedef enum on_off on_off;

enum menu_options{new_game = 1, image_drawing = 2, options = 3,  editor = 4, in_option_screen = 7};
typedef enum menu_options menu_options;

enum special_buttons{enter = '\r', backspace = '\b', escape = 27};
typedef enum special_buttons special_buttons;

enum success_unsuccess {unsuccessful, successful};
typedef enum success_unsuccess success_unsuccess;

enum uncoloured_coloured {uncoloured, coloured};
typedef enum uncoloured_coloured uncoloured_coloured;

enum grid_location {top_right, bottom_right, bottom_left, top_left};
typedef enum grid_location grid_location;

enum rt_lt {rt_dir, lt_dir};
typedef enum rt_lt rt_lt;

enum looping_array {start_word, start_number, end_number, current_iteration, variable};
typedef enum looping_array looping_array;

typedef uncoloured_coloured board_array[WWIDTH][WHEIGHT];

struct program{
    char prog_line[MAX_NUM_LINES][MAX_SIZE_OF_LINE];
    int current_word;
    int num_lines_in_file;
};
typedef struct program program;

struct player{

    board_array player_board;

    int row;
    int col;
    int angle;

    float variable_values[NUM_LETTERS_ALPHABET];
    float current_constant;
    int current_variable;
    int current_operator;
    int current_steps_taken;

    on_off variable_checker;
    on_off constant_checker;
    on_off operation_indicator;
    on_off loop_indicator;

    int set_variable;
    int looping_index;
    int looping_array[START_ITERATION_END][MAX_EMBEDDED_LOOPS];
};
typedef struct player player;

struct polish_stack{

    float numbers_stack[MAX_STACK_SIZE];
    int current_index;

};
typedef struct polish_stack polish_stack;

typedef struct roomGrid
{
    int **room_array;
    compass direction;
    SDL_Rect rc_sprite, rc_sprite_pos, rc_src, rc_obj, rc_obj_dest, rc_dest;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    fin_unfin finished;
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
    SDL_Rect srcChicken, dstChicken;
    compass chick_facing;
    int chick_probe;
    int chick_lx_coord;
    int chick_rx_coord;
    int chick_by_coord;
    int chick_ty_coord;
    int x_chick_centre;
    int y_chick_centre;
    bool chicken_cross_road;
}Chicken;


struct progress
{   
    bool puzzle_1_seen;
    bool puzzle_1_solved;
    bool puzzle_2_seen;
    bool puzzle_2_solved;
    bool puzzle_3_seen;
    bool puzzle_3_solved;
    bool puzzle_4_seen;
    bool puzzle_4_solved;
    bool puzzle_5_seen;
    bool puzzle_5_solved;
    bool puzzle_6_seen;
    bool puzzle_6_solved;

    bool player_has_a_weight;
    bool player_has_b_weight;
    bool a_weight_on_hinge;
    bool b_weight_on_hinge;
};
typedef struct progress progress;

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

struct edit{
    int previous;
    int src_value;
};
typedef struct edit Edit;

struct problem{
    char *correct_answer;
    int first_instructions_start;
    int first_instructions_end;
    int second_instructions_end;
    int num_chars_in_ans;
};
typedef struct problem problem;

//FUNCTIONS FOR PROBLEMS

void print_instruction(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS], int start, int end);
void James_SDL_Events(roomGrid *room_grid);
void print_instruction_to_screen(roomGrid *room_grid, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);
void look_for_action(roomGrid *room_grid);
void SDL_QuitChecker(roomGrid *room_grid);
void initialise_SDL_component(SDL_Window *window, roomGrid *room_grid);
void neill_notes(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS]);

void problem_generator(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS], problem *prob_point, bool *current_puzzle_solved, char *input_image_name);
void input_screen(roomGrid *room_grid, char *correct_answer, int chars_in_ans, bool *current_puzzle_solved, char *input_screen);

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS], int chars_in_ans);
void initialise_input_string(char input_string[MAX_INPUT_CHARS]);
void initialise_drcrect(SDL_Rect *drcrect, int input_index);
void check_user_variable_input(roomGrid *room_grid, char *input_string, int *input_index, int *finish_checker);

void initialise_problem(problem *prob_point, char *correct_answer, int first_inst_start, int first_instr_end,
                        int num_chars_ans, int second_inst_end);
void door_hinge_problem(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS]);
void find_weight_a(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS]);
void find_weight_b(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS]);



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
void edge_detection(roomGrid *room_grid);
void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *backtex, roomGrid *room_grid);
void initialise_chicken(Chicken *hen, roomGrid *room_grid);
void changeChickenDirection(Chicken *hen);
void draw_room(SDL_Texture *grafix_tex, roomGrid *room_grid);
void draw_obj(SDL_Texture *grafix_tex, roomGrid *room_grid);
void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *grafix_tex, roomGrid *room_grid);
void rcobj_set(int x_coord, int y_coord, int width, int height, int dest_x, int dest_y, SDL_Texture *grafix_tex, roomGrid *room_grid);
void position_chicken(Chicken *hen, roomGrid *room_grid);
void chicken_walks(Chicken *hen, roomGrid *room_grid);
void chicken_edge_detection(roomGrid *room_grid, Chicken *hen);
void permit_chicken(Chicken *hen, roomGrid *room_grid);
void eggfault(Chicken *hen, roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS]);
void chicken_help(Chicken *hen, roomGrid *room_grid);
void chicken_direction(Chicken *hen, roomGrid *room_grid);
void hen_sequence(Chicken *hen, roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS]);

//FUNCTIONS FOR MENU

void run_menu_screen(roomGrid *room_grid, char *argv[]);
void load_menu_frame(roomGrid *room_grid);
void highlight_area(roomGrid *room_grid, int current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex);
bool getEvent(roomGrid *room_grid);
void cycle_options(roomGrid *room_grid, char *argv[]);
void getloadscreenevent(roomGrid *room_grid);
void getkeyEvent(roomGrid *room_grid, int x);
void runloadscreen();
void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running, char *argv[]);
void level_editor(roomGrid *room_grid);
void initialise_level_editor_map(int array[ROOM_Y][ROOM_X]);
void load_image(roomGrid *room_grid, SDL_Surface **surf, SDL_Texture **tex, char *image_name);
void editor_interactions(int map_array[ROOM_Y][ROOM_X], bool *running, input *input);
void configure_mouse(int excess, int *tile_x, int *tile_y, input input, cursor cursor, SDL_Rect *cursor_src, SDL_Rect *cursor_dst, SDL_Rect *tile_src);
Edit draw_edited_map(int map_array[ROOM_Y][ROOM_X], input input, int tile_x, int tile_y, SDL_Texture *tile_tex, SDL_Rect tile_src, SDL_Rect tile_dst, 
                     roomGrid *room_grid, SDL_Texture *cursor_tex, SDL_Rect cursor_src, SDL_Rect cursor_dst, SDL_Texture *back_tex, SDL_Texture *red_tex, Edit edit);


//MAIN

int main(int aroom_gridc, char *argv[])
{
    roomGrid *room_grid = (roomGrid *)malloc(sizeof(roomGrid));

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

    run_menu_screen(room_grid, argv);

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
    room_grid -> mus = Mix_LoadWAV("sfx/20141124b.wav");

    //Prints the opening scene.
    print_instruction(room_grid, instructions_list, 0, 10);

    draw(room_grid, puzzle, instructions_list, hen);

    atexit(SDL_Quit);

    /*shut down SDL, Music, go outside, and have a nice day*/
    Mix_HaltMusic(); 
    Mix_FreeChunk(room_grid -> mus); 
    Mix_CloseAudio();  
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

//Used to initialise all of the necessary components of SDL.
void initialise_SDL_component(SDL_Window *window, roomGrid *room_grid)
{

    //Initialise SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) != SUCCESSFUL){
        fprintf(stderr, "\nUnable to initialise SDL:  %s\n", SDL_GetError());
        exit(1);
    }
    else{
        window = SDL_CreateWindow ("MADLAB!",                      //window name
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

    //Initialise PNG loading.
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){ 
        printf( "SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError());
    }

    //Initialise renderer.
    if ((room_grid -> renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL){
        fprintf(stderr, "\nUnable to initialise SDL Renderer:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //Initialise TTF component.
    if( TTF_Init() != SUCCESSFUL){
    	fprintf(stderr, "\nUnable to initialise TTF.\n");
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

    //First block of instructions
    instructions_list[29] = "door_still_locked";
    instructions_list[30] = "work_out";
    instructions_list[31] = "code_is_five";
    instructions_list[32] = "binary";
    instructions_list[33] = "info_here";
    instructions_list[34] = "bin_notes";

    //Second block of instructions
    instructions_list[35] = "door_open";

    //Hen related .bmp images
    instructions_list[36] = "chicken_in_here";
    instructions_list[37] = "leave_it_alone";
    instructions_list[38] = "come_back_let_it_out";
    instructions_list[39] = "latch_loose";
    instructions_list[40] = "got_out";
    instructions_list[41] = "eggfault";

    //Discovering the x problem.
    instructions_list[42] = "door_still_locked";
    instructions_list[43] = "oh_my_word";
    instructions_list[44] = "hinge_sticks";
    instructions_list[45] = "x_part_hinge";
    instructions_list[46] = "swing_open";
    instructions_list[47] = "x_eq_five";
    instructions_list[48] = "two_weights";
    instructions_list[49] = "a_weight_b_weight";
    instructions_list[50] = "a_eq_b_eq";
    instructions_list[51] = "go_find";
    instructions_list[52] = "finally_get_out";

    //Picking up the a weight.
    instructions_list[53] = "a_weight";
    instructions_list[54] = "put_by_door";

    //Picking up the b weight.
    instructions_list[55] = "found_b";
    instructions_list[56] = "put_on_door_hinge";

    //Combining the weights.
    instructions_list[57] = "a_weight_on_hinge";
    instructions_list[58] = "b_weight_on_hinge";
    instructions_list[59] = "both_weights";
    instructions_list[60] = "x_is_eq";
    instructions_list[61] = "door_finally_open";

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
                room_grid -> finished = finished;
                break;
            case SDL_MOUSEBUTTONDOWN:
                room_grid -> skip_checker = on;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        room_grid -> problem_quitter = on;
                        break;
                    case SDLK_SPACE:
                        room_grid -> skip_checker = on;
                        break;
                }
                break;
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
    }while(room_grid -> refresh_counter < NUM_REFRESHES && !room_grid -> skip_checker && !room_grid -> problem_quitter);
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
    SDL_Surface *grafix;
    SDL_Texture *grafix_tex;

    /*One texture to rule them all*/
    grafix = IMG_Load("gfx/tile_array.png");  //if you want to add new items, to code, ensure to check the txt file with the coordinates
    grafix_tex = SDL_CreateTextureFromSurface(room_grid -> renderer, grafix);
    SDL_FreeSurface (grafix);

    initialise_roomgrid_components(room_grid, puzzle);
    initialise_chicken(hen, room_grid);
    position_sprite(room_grid);
    Mix_PlayChannel(-1, room_grid -> mus, -1);

    while (room_grid -> gamerunning)
    {
        SDL_Delay(20);
        movement(room_grid, puzzle, instructions_list, hen);     
        edge_detection(room_grid);
        SDL_RenderClear(room_grid -> renderer);
        
        if(hen -> chicken_cross_road)
        {
            chicken_edge_detection(room_grid, hen);
            permit_chicken(hen, room_grid);
            eggfault(hen, room_grid, instructions_list);
        }

        draw_room(grafix_tex, room_grid);
        draw_obj(grafix_tex, room_grid);

        /*RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
       // SDL_RenderCopy(room_grid -> renderer, chickentex, &hen -> srcChicken, &hen -> dstChicken);
        SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_sprite_pos, &room_grid -> rc_sprite);  //draws 
        SDL_RenderPresent(room_grid -> renderer);
    }

    SDL_DestroyTexture(grafix_tex);
    SDL_DestroyRenderer(room_grid -> renderer);

    //THIS IS CAUSING A SEGFAULT!
    //SDL_DestroyWindow(room_grid -> window);
}


void draw_room(SDL_Texture *grafix_tex, roomGrid *room_grid)
{
    for (int i = 0; i <= ROOM_Y; ++i){
        for (int j = 0; j < ROOM_X; ++j){

            room_grid -> rc_dest.x = (j * TILE_SIZE);              //the destination rects are set to i and j
            room_grid -> rc_dest.y = (i * TILE_SIZE);

            rcsrc_set(34, 138, 32, 32, grafix_tex, room_grid);     //first ground tile does not go in an if statement; it populates everything. 
            
            if (room_grid -> room_array[i][j] == 1){
                rcsrc_set(3, 174, 31, 31, grafix_tex, room_grid);  //draw desk
                rcsrc_set(71, 138, 32, 32, grafix_tex, room_grid); //draw computer on top of it
            }

            if (room_grid -> room_array[i][j] == 2){
                rcsrc_set(0, 138, 32, 32, grafix_tex, room_grid);  //draw a wall
            }
        }
    }
}


void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *grafix_tex, roomGrid *room_grid)
{
    room_grid -> rc_src.x = x_coord;
    room_grid -> rc_src.y = y_coord;
    room_grid -> rc_src.w = width;
    room_grid -> rc_src.h = height;

    SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_src, &room_grid -> rc_dest);
}

/*draws an object by selecting values from the tile sheet and drawing them to a destination on the game map*/
void draw_obj(SDL_Texture *grafix_tex, roomGrid *room_grid)
{
    /*draw and position extractor*/
    rcobj_set(264, 63, 64, 64, 0, 0, grafix_tex, room_grid);

    /*draw and position fan*/
    rcobj_set(0, 62, 64, 64, 737, 318, grafix_tex, room_grid);

}

void rcobj_set(int x_coord, int y_coord, int width, int height, int dest_x, int dest_y, SDL_Texture *grafix_tex, roomGrid *room_grid)
{
    room_grid -> rc_obj.x = x_coord;                     //the x-coordinate of the object on the tile sheet
    room_grid -> rc_obj.y = y_coord;                     //the y-coordiante of the object on the tile sheet
    room_grid -> rc_obj.w = width;                       //the height and width for objects are 64 normally, but really can be anything
    room_grid -> rc_obj.h = height;

    room_grid -> rc_obj_dest.x = dest_x;                 //the x-coordinate of the object on the game map; takes some trial and error to figure out
    room_grid -> rc_obj_dest.y = dest_y;                 //the y-coordinate of the object on the game map;
    room_grid -> rc_obj_dest.w = room_grid -> rc_obj.w;  //these are set to be the same so another value does not have to be passed
    room_grid -> rc_obj_dest.h = room_grid -> rc_obj.h;

    SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_obj, &room_grid -> rc_obj_dest);
}


void initialise_roomgrid_components(roomGrid *room_grid, progress *puzzle)
{
    room_grid -> gamerunning = true;

    puzzle -> puzzle_1_seen   = false;
    puzzle -> puzzle_1_solved = false;
    puzzle -> puzzle_2_seen   = false;
    puzzle -> puzzle_2_solved = false;
    puzzle -> puzzle_3_seen   = false;
    puzzle -> puzzle_3_solved = false;
    puzzle -> puzzle_4_seen   = false;
    puzzle -> puzzle_4_solved = false;
    puzzle -> puzzle_5_seen   = false;
    puzzle -> puzzle_5_solved = false;
    puzzle -> puzzle_6_seen   = false;
    puzzle -> puzzle_6_solved = false;

    puzzle -> player_has_a_weight = false;
    puzzle -> player_has_b_weight = false;
    puzzle -> a_weight_on_hinge = false;
    puzzle -> b_weight_on_hinge = false;

    room_grid -> paused = 0;
    room_grid -> left_x_coord = 0;
    room_grid -> bottom_y_coord = 0;
    room_grid -> top_y_coord = 0;
    room_grid -> direction = 0;
}


void initialise_chicken(Chicken *hen, roomGrid *room_grid)
{
    hen -> chicken_cross_road = false;
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
    room_grid -> rc_sprite.y = TILE_SIZE*16;  //if you want to change sprite position, make it a multiple of 32 or else you get clipping
    room_grid -> rc_sprite.x = TILE_SIZE*5;
    room_grid -> rc_sprite.w = TILE_SIZE;
    room_grid -> rc_sprite.h = TILE_SIZE;

    room_grid -> rc_sprite_pos.x = 0;  
    room_grid -> rc_sprite_pos.y = 0;
    room_grid -> rc_sprite_pos.w = TILE_SIZE;
    room_grid -> rc_sprite_pos.h = TILE_SIZE; 

    room_grid -> rc_dest.w = TILE_SIZE;
    room_grid -> rc_dest.h = TILE_SIZE;
}


void position_chicken(Chicken *hen, roomGrid *room_grid)
{
    hen -> chick_facing = room_grid -> direction;
    hen -> srcChicken.y = 0;
    hen -> srcChicken.x = 0;
    hen -> srcChicken.w = TILE_SIZE;
    hen -> srcChicken.h = TILE_SIZE;

    hen -> dstChicken.y = 320;
    hen -> dstChicken.x = 320;
    hen -> dstChicken.w = TILE_SIZE;
    hen -> dstChicken.h = TILE_SIZE;
}


void movement(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
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
                    (!((room_grid -> rc_sprite.x) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_RIGHT:
                    room_grid -> direction = right;
                    (!((room_grid -> rc_sprite.x) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_UP:
                    room_grid -> direction = up;
                    (!((room_grid -> rc_sprite.y) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
                    break;
                case SDLK_DOWN:
                    room_grid -> direction = down;
                    (!((room_grid -> rc_sprite.y) % TILE_SIZE)) ? possible(room_grid, puzzle): move(room_grid, puzzle);
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


void edge_detection(roomGrid *room_grid)
{
    //Left edge.
    if (room_grid -> rc_sprite.x <= 0){
        room_grid -> rc_sprite.x  = 0;
    }
    //Right edge
    if (room_grid -> rc_sprite.x >= SCREEN_WIDTH - TILE_SIZE){
        room_grid -> rc_sprite.x  = SCREEN_WIDTH - TILE_SIZE;
    }
    //Top edge
    if (room_grid -> rc_sprite.y <= 0){
        room_grid -> rc_sprite.y  = 0;
    }
    //Bottom edge
    if (room_grid -> rc_sprite.y >= SCREEN_HEIGHT - TILE_SIZE){ 
        room_grid -> rc_sprite.y  = SCREEN_HEIGHT - TILE_SIZE;
    }

    SDL_RenderClear(room_grid -> renderer);
}

void possible(roomGrid *room_grid, progress *puzzle)
{
    room_grid -> left_x_coord = (room_grid -> rc_sprite.x) / TILE_SIZE;
    room_grid -> top_y_coord = (room_grid -> rc_sprite.y) / TILE_SIZE;
    room_grid -> bottom_y_coord = ((room_grid -> rc_sprite.y - 1) + TILE_SIZE) / TILE_SIZE;
    room_grid -> right_x_coord = ((room_grid -> rc_sprite.x - 1) + TILE_SIZE) / TILE_SIZE;

    switch (room_grid -> direction)
    {       
        case(left):     if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> left_x_coord - 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1])){
                            if(room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1] == 0){

                                move(room_grid, puzzle);

                            }
                        }
                        break;

        case(down):     if ((room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> right_x_coord])){
                            if(room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord] == 0){

                                move(room_grid, puzzle);

                            }
                        }
                        break;

        case(right):    if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> right_x_coord + 1])){
                            if(room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1] == 0){

                                move(room_grid, puzzle);

                            }
                        }
                        break;

        case(up):       if (room_grid -> rc_sprite.y != 0)
                        {
                            if ((room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> right_x_coord])){
                            if (room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord] == 0){

                                move(room_grid, puzzle);
                        }      
                        }
                        }
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
        case(left):     (room_grid -> rc_sprite_pos.x == 224) ? (room_grid -> rc_sprite_pos.x = 256): (room_grid -> rc_sprite_pos.x = 224);
                        room_grid -> rc_sprite.x -= MOVEMENT_INCREMENT;
                        break;

        case(down):     (room_grid -> rc_sprite_pos.x == 96) ? (room_grid -> rc_sprite_pos.x = 128): (room_grid -> rc_sprite_pos.x = 96);
                        room_grid -> rc_sprite.y += MOVEMENT_INCREMENT;                  
                        break;

        case(right):    (room_grid -> rc_sprite_pos.x == 160) ? (room_grid -> rc_sprite_pos.x = 192): (room_grid -> rc_sprite_pos.x = 160);
                        room_grid -> rc_sprite.x += MOVEMENT_INCREMENT;
                        break;

        case(up):       (room_grid -> rc_sprite_pos.x == 32) ? (room_grid -> rc_sprite_pos.x = 64): (room_grid -> rc_sprite_pos.x = 32);
                        room_grid -> rc_sprite.y -= MOVEMENT_INCREMENT;
                        break;

        default:        fprintf(stderr, "Problem moving!\n");
                        exit(6);
    }
}


void interactProbe(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS], Chicken *hen)
{
    room_grid -> x_sprite_centre = (room_grid -> rc_sprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
    room_grid -> y_sprite_centre = (room_grid -> rc_sprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
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

        case(up):       if (room_grid -> rc_sprite.y != 0)
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
    problem action_problem, *prob_point;
    prob_point = &action_problem;


    switch(room_grid -> probe)
    {
        case(puz_1):        if ((puzzle -> puzzle_1_seen) == false){

                                neill_notes(room_grid, instructions_list);
                                puzzle -> puzzle_1_seen = true;

                                return 1;
                            }
                            else if( (puzzle -> puzzle_1_solved) == false){     

                                initialise_problem(prob_point, "fan<toohot", 22, 27, 13, 29);
                                problem_generator(room_grid, instructions_list, prob_point, &puzzle -> puzzle_1_solved, "Instructions/code_entry.bmp");

                                return 0;
                            }
                            return 1;
                            break;

        case(puz_2):        door_hinge_problem(room_grid, puzzle, instructions_list);
                            return 0;
                            break; 

        case(puz_3):        if ((puzzle -> puzzle_3_solved) == false){

                                initialise_problem(prob_point, "101", 29, 35, 3, 36);
                                problem_generator(room_grid, instructions_list, prob_point, &puzzle -> puzzle_3_solved, "Instructions/code_entry_two.bmp");

                                return 0;
                            }
                            return 1;
                            break;

        case(puz_4):        find_weight_a(room_grid, puzzle, instructions_list);
                            return 0;
                            break; 

        case(puz_5):        hen_sequence(hen, room_grid, instructions_list);
                            return 0;
                            break;

        case(puz_6):        find_weight_b(room_grid, puzzle, instructions_list);
                            return 0;
                            break; 

        default:            fprintf(stderr, "PANIC!\n");
                            return 0;
                            break;
    }
}

void door_hinge_problem(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS])
{
    if(puzzle -> puzzle_2_seen == false){
        print_instruction(room_grid, instructions_list, 42, 53);
        puzzle -> puzzle_2_seen = true;
    }
    
    if(puzzle -> player_has_a_weight == true){
        print_instruction(room_grid, instructions_list, 57, 58);
        puzzle -> player_has_a_weight = false;
        puzzle -> a_weight_on_hinge = true;
    }
    
    if(puzzle -> player_has_b_weight == true){
        print_instruction(room_grid, instructions_list, 58, 59);
        puzzle -> player_has_b_weight = false;
        puzzle -> b_weight_on_hinge = true;
    }
    
    if(puzzle -> a_weight_on_hinge == true && puzzle -> b_weight_on_hinge == true){
        print_instruction(room_grid, instructions_list, 59, 62);
    }
}

void find_weight_a(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS])
{
    if(puzzle -> puzzle_4_seen == false){
        print_instruction(room_grid, instructions_list, 53, 55);
        puzzle -> player_has_a_weight = true;
        puzzle -> puzzle_4_seen = true;
    }
}

void find_weight_b(roomGrid *room_grid, progress *puzzle, char *instructions_list[NUM_INSTRUCTIONS])
{
    if(puzzle -> puzzle_6_seen == false){
        print_instruction(room_grid, instructions_list, 55, 57);
        puzzle -> player_has_b_weight = true;
        puzzle -> puzzle_6_seen = true;
    }

}

void hen_sequence(Chicken *hen, roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS])
{
    static int interaction_counter = 0;

    if(interaction_counter == 0){
        print_instruction(room_grid, instructions_list, 36, 38);
        ++interaction_counter;
    }
    else if(interaction_counter == 1){
        print_instruction(room_grid, instructions_list, 38, 39);
        ++interaction_counter;
    }
    else if(interaction_counter == 2 && !(hen -> chicken_cross_road)){
        print_instruction(room_grid, instructions_list, 39, 41);
        ++interaction_counter;

        printf("Bring out the chicken!\n");
        position_chicken(hen, room_grid);
        hen -> chicken_cross_road = true;
    }

}

void initialise_problem(problem *prob_point, char *correct_answer, int first_inst_start, int first_instr_end,
                        int num_chars_ans, int second_inst_end)
{
    prob_point -> correct_answer = correct_answer;
    prob_point -> first_instructions_start = first_inst_start;
    prob_point -> first_instructions_end = first_instr_end;
    prob_point -> second_instructions_end = second_inst_end;
    prob_point -> num_chars_in_ans = num_chars_ans;
}

void permit_chicken(Chicken *hen, roomGrid *room_grid)
{
    switch (hen -> chick_facing)
    {       
        case(left):     if(!((hen -> dstChicken.x) % TILE_SIZE)){
                            chicken_help(hen, room_grid);
                        } 
                        else{
                            (hen -> dstChicken.x -= MOVEMENT_INCREMENT);
                        }
                        break;

        case(down):     if(!((hen -> dstChicken.y) % TILE_SIZE)){
                            chicken_help(hen, room_grid);
                        }
                        else{
                            (hen -> dstChicken.y += MOVEMENT_INCREMENT);
                        }
                        break;

        case(right):    if(!((hen -> dstChicken.x) % TILE_SIZE)){
                            chicken_help(hen, room_grid);
                        }
                        else{
                            (hen -> dstChicken.x += MOVEMENT_INCREMENT);
                        }
                        break;

        case(up):       if(!((hen -> dstChicken.y) % TILE_SIZE)){
                            if (hen -> dstChicken.y != 0){
                            chicken_help(hen, room_grid);
                            }
                        }
                        else{
                            (hen -> dstChicken.y -= MOVEMENT_INCREMENT);
                        }
                        break;

        default:        fprintf(stderr, "Problem probing!\n");
                        exit(6);
    }
}

void chicken_help(Chicken *hen, roomGrid *room_grid)
{
    hen -> chick_facing = rand() % 4;
    chicken_walks(hen, room_grid);
}


void chicken_walks(Chicken *hen, roomGrid *room_grid)
{
    hen -> chick_lx_coord = (hen -> dstChicken.x) / TILE_SIZE;
    hen -> chick_ty_coord = (hen -> dstChicken.y) / TILE_SIZE;
    hen -> chick_by_coord = ((hen -> dstChicken.y - 1) + TILE_SIZE) / TILE_SIZE;
    hen -> chick_rx_coord = ((hen -> dstChicken.x - 1) + TILE_SIZE) / TILE_SIZE;

    switch (hen -> chick_facing)
    {       
        case(left):     if ((room_grid -> room_array[hen -> chick_ty_coord][hen -> chick_lx_coord - 1]) == (room_grid -> room_array[hen -> chick_by_coord][hen -> chick_lx_coord - 1])){
                            if(room_grid -> room_array[hen -> chick_by_coord][hen -> chick_lx_coord - 1] == 0){
                                chicken_direction(hen, room_grid);  
                            }
                            else {
                                hen -> chick_facing = rand() % 4;
                            }
                        }
                        break;

        case(down):     if ((room_grid -> room_array[hen -> chick_by_coord + 1][hen -> chick_lx_coord]) == (room_grid -> room_array[hen -> chick_by_coord + 1][hen -> chick_rx_coord])){
                            if(room_grid -> room_array[hen -> chick_by_coord + 1][hen -> chick_lx_coord] == 0){
                                chicken_direction(hen, room_grid);  
                            }
                            else {
                                hen -> chick_facing = rand() % 4;
                            }
                        }
                        break;

        case(right):    if ((room_grid -> room_array[hen -> chick_ty_coord][hen -> chick_rx_coord + 1]) == (room_grid -> room_array[hen -> chick_by_coord][hen -> chick_rx_coord + 1])){
                            if(room_grid -> room_array[hen -> chick_ty_coord][hen -> chick_rx_coord + 1] == 0){
                                chicken_direction(hen, room_grid);
                            } 
                            else {
                                hen -> chick_facing = rand() % 4;
                            }
                        }
                        break;

        case(up):       if (hen -> dstChicken.y != 0){
                            if ((room_grid -> room_array[hen -> chick_by_coord-1][hen -> chick_lx_coord]) == (room_grid -> room_array[hen -> chick_by_coord-1][hen -> chick_rx_coord])){
                                if (room_grid -> room_array[hen -> chick_by_coord - 1][hen -> chick_lx_coord] == 0){
                                    chicken_direction(hen, room_grid);
                                }
                            else {
                                hen -> chick_facing = rand() % 4;   
                                }
                            }
                        }
                        break;

        default:        fprintf(stderr, "Problem probing!\n");
                        exit(6);
    }
}


void chicken_direction(Chicken *hen, roomGrid *room_grid)
{
    switch (hen -> chick_facing)
    {       
        case(left):     (hen -> srcChicken.x == 364) ? (hen -> srcChicken.x = 396): (hen -> srcChicken.x = 364);
                        hen -> dstChicken.x -= MOVEMENT_INCREMENT;
                        break;

        case(down):     (hen -> srcChicken.x == 364) ? (hen -> srcChicken.x = 396): (hen -> srcChicken.x = 364);
                        hen -> dstChicken.y += MOVEMENT_INCREMENT;
                        break;

        case(right):    (hen -> srcChicken.x == 300) ? (hen -> srcChicken.x = 332): (hen -> srcChicken.x = 300);
                        hen -> dstChicken.x += MOVEMENT_INCREMENT;
                        break;

        case(up):       (hen -> srcChicken.x == 300) ? (hen -> srcChicken.x = 332): (hen -> srcChicken.x = 300);
                        hen -> dstChicken.y -= MOVEMENT_INCREMENT;
                        break;

        default:        fprintf(stderr, "Problem probing!\n");
                        exit(6);
    }
}


void chicken_edge_detection(roomGrid *room_grid, Chicken *hen)
{
    //Left edge.
    if (hen -> dstChicken.x <= 0){
        hen -> dstChicken.x = 0;
        hen -> chick_facing = right;
    }
    //Right edge
    if (hen -> dstChicken.x >= SCREEN_WIDTH - TILE_SIZE){
        hen -> dstChicken.x = SCREEN_WIDTH - TILE_SIZE;
        hen -> chick_facing = left;
    }
    //Top edge
    if (hen -> dstChicken.y <= 0){
        hen -> dstChicken.y = 0;
        hen -> chick_facing = down;
    }
    //Bottom edge
    if (hen -> dstChicken.y >= SCREEN_HEIGHT - TILE_SIZE){ 
        hen -> dstChicken.y = SCREEN_HEIGHT - TILE_SIZE;
        hen -> chick_facing = up;
    }

    SDL_RenderClear(room_grid -> renderer);
}


void eggfault(Chicken *hen, roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS])
{
    hen -> x_chick_centre = (hen -> dstChicken.x + (TILE_SIZE / 2)) / TILE_SIZE;
    hen -> y_chick_centre = (hen -> dstChicken.y + (TILE_SIZE / 2)) / TILE_SIZE;
    room_grid -> x_sprite_centre = (room_grid -> rc_sprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
    room_grid -> y_sprite_centre = (room_grid -> rc_sprite.y + (TILE_SIZE / 2)) / TILE_SIZE;

    if (((room_grid -> room_array[hen -> x_chick_centre]) == (room_grid -> room_array[room_grid -> x_sprite_centre]))
        && (room_grid -> room_array[hen -> y_chick_centre] == room_grid -> room_array[room_grid -> y_sprite_centre])){

        print_instruction(room_grid, instructions_list, 41, 42);
        room_grid -> gamerunning = false;
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

void problem_generator(roomGrid *room_grid, char *instructions_list[NUM_INSTRUCTIONS], problem *prob_point, bool *current_puzzle_solved, char *input_image_name)
{
    room_grid -> finished = 0;

    //Prints first part of the instructions.
    print_instruction(room_grid, instructions_list, prob_point->first_instructions_start, prob_point->first_instructions_end);

    //Now we go to the input screen for the text.
    while(*current_puzzle_solved == false && room_grid -> problem_quitter == off){
        input_screen(room_grid, prob_point->correct_answer, prob_point->num_chars_in_ans, current_puzzle_solved, input_image_name);
    }

    //Prints second part of the instructions.
    if(room_grid -> problem_quitter == off){
        print_instruction(room_grid, instructions_list, prob_point->first_instructions_end, prob_point->second_instructions_end);
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
void input_screen(roomGrid *room_grid, char *correct_answer, int chars_in_ans, bool *current_puzzle_solved, char *input_screen)
{
    SDL_Texture* image, *image_one;
    SDL_Surface *text, *text_one;
    SDL_Rect drcrect;
    char input_string[MAX_INPUT_CHARS], possible_answer[MAX_INPUT_CHARS];
    int input_index = 0, finish_checker = unfinished;

    initialise_input_string(input_string);
    initialise_drcrect(&drcrect, input_index);

    text_one = SDL_LoadBMP( input_screen );

    if( text_one == NULL )
    {
      printf( "Unable to load image %s! SDL Error: %s\n", "bla", SDL_GetError() );
    }

    image_one = SDL_CreateTextureFromSurface(room_grid->renderer, text_one);
    TTF_Font *font = TTF_OpenFont("gfx/opendisplay.ttf", 200);

    if(font == NULL){
        printf("\nCouldn't load text.\n");
    }

    SDL_Color fg = { 0, 0, 0, 0};

    SDL_RenderClear(room_grid->renderer);
    SDL_RenderCopy(room_grid->renderer, image_one, NULL, NULL);
    SDL_RenderPresent(room_grid->renderer);

    do{

        check_user_variable_input(room_grid, input_string, &input_index, &finish_checker);

        text = TTF_RenderText_Solid(font, input_string, fg) ;
        image = SDL_CreateTextureFromSurface(room_grid->renderer, text);

        SDL_RenderClear(room_grid->renderer);
        SDL_RenderCopy(room_grid->renderer, image_one, NULL, NULL);
        SDL_RenderCopy(room_grid->renderer, image, NULL, &drcrect);
        SDL_RenderPresent(room_grid->renderer);

        if(input_index == chars_in_ans + 1){
          finish_checker = finished;
        }

    }while(input_index < MAX_INPUT_CHARS && !finish_checker && room_grid -> problem_quitter == off);

    create_answer_for_checking(possible_answer, input_string, chars_in_ans);

    if( strcmp(possible_answer, correct_answer) == 0){
        *current_puzzle_solved = true;
    }

    look_for_action(room_grid);
}

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS], int chars_in_ans)
{
  int i, j = 0;

    while( i < chars_in_ans ){
        if(input_string[i] != ' '){
            possible_answer[j] = input_string[i];
            ++j;
        }
        ++i;
    }

  possible_answer[j] = '\0';

  printf("\n%s\n", possible_answer);
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

  while (gameover != INPUT_FINISHED){                                                                                   //to make screen stay on.
    while( SDL_PollEvent( &event ) ){                                                                                   //checks for events.
      if(event.type == SDL_KEYDOWN){                                                                                    //checks for key being pressed
        char c = event.key.keysym.sym;                                                                                  //if the key is pressed assigns character
        if( (c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) || (c >= '0' && c <= '9') ){
              if(c == ','){
                input_string[*input_index] = '<';
              }
              else if(c == '.'){
                input_string[*input_index] = '>';
              }
              else{
                input_string[*input_index] = c;
              }                                                                                                          //puts all pressed characters in an room_array.
              ++(*input_index);                                                                                          //adds one to the index.
              gameover = INPUT_FINISHED;
        }
        else if( c == backspace){
          input_string[--(*input_index)] = ' ';
          gameover = INPUT_FINISHED; 
        }
        else if(c == enter){
          *finish_checker = finished;
          gameover = INPUT_FINISHED; 
        }
        else if(c == escape){
            room_grid -> problem_quitter = on;
            gameover = INPUT_FINISHED;
        }
      }
    }
  }              

  input_string[MAX_INPUT_CHARS] = '\0';                                                               //concludes string

}

void run_menu_screen(roomGrid *room_grid, char *argv[])
{
    static int first_pass = 0;

    if(first_pass == 0){
        initialise_SDL_component(room_grid->window, room_grid);
        ++first_pass;
    }

    load_menu_frame(room_grid);
    
    cycle_options(room_grid, argv);

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
    Edit edit;
    bool running = true;
    input input;
    cursor cursor;
    
    input.add = 0;
    input.remove = 0;
    
    edit.previous  = 0;
    edit.src_value = 0;
    
    int map_array[ROOM_Y][ROOM_X];
    int excess = 0, tile_x = 0, tile_y = 0;
    
    initialise_level_editor_map(map_array);
    
    // Background, tile, cursor and menu stuff
    SDL_Surface *back_surf, *tile_surf, *red_surf, *cursor_surf, *menu_surf, *options_surf;
    SDL_Texture *back_tex, *tile_tex, *red_tex, *cursor_tex, *menu_tex, *options_tex;
    SDL_Rect tile_src, tile_dst, cursor_src, cursor_dst;
    
    // Make the tile
    load_image(room_grid, &tile_surf, &tile_tex, "block.png");

    red_surf = IMG_Load("block_red.png");
    red_tex = SDL_CreateTextureFromSurface(room_grid -> renderer, red_surf);
    SDL_FreeSurface(red_surf);

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
        
        editor_interactions(map_array, &running, &input);
        
        // Get the mouse coords
        SDL_GetMouseState(&input.mouse_x, &input.mouse_y);

        configure_mouse(excess, &tile_x, &tile_y, input, cursor, &cursor_src, &cursor_dst, &tile_src);

        edit = draw_edited_map(map_array, input, tile_x, tile_y, tile_tex, tile_src, tile_dst, room_grid, cursor_tex, cursor_src, cursor_dst, back_tex, red_tex, edit);
        
    }
    
    load_menu_frame(room_grid);

    load_image(room_grid, &menu_surf, &menu_tex, "screen2.png");

    load_image(room_grid, &options_surf, &options_tex, "controls.png");
    
    highlight_area(room_grid, editor, menu_tex, options_tex);
    
}

Edit draw_edited_map(int map_array[ROOM_Y][ROOM_X], input input, int tile_x, int tile_y, SDL_Texture *tile_tex, SDL_Rect tile_src, SDL_Rect tile_dst, 
                     roomGrid *room_grid, SDL_Texture *cursor_tex, SDL_Rect cursor_src, SDL_Rect cursor_dst, SDL_Texture *back_tex, SDL_Texture *red_tex, Edit edit)
{

    if (input.add == edit.previous && edit.previous == 1) // If the mouse has been held down
        {
            map_array[tile_y][tile_x] = edit.src_value;
        }

        else if(input.add == 1) // If we've got a new add signal, add a tile
        {   
            map_array[tile_y][tile_x]++;
            map_array[tile_y][tile_x] = map_array[tile_y][tile_x] % 3;
            edit.src_value = map_array[tile_y][tile_x];
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

            else if ( map_array[i][j] == ALT)
            {   // If the element is a 2, draw a red tile
                SDL_RenderCopy(room_grid -> renderer, red_tex, &tile_src, &tile_dst);
            }
        }
    }

    SDL_RenderCopy(room_grid -> renderer, cursor_tex, &cursor_src, &cursor_dst);
    
    // Update the screen with the latest render 
    SDL_RenderPresent(room_grid -> renderer);

    edit.previous = input.add;

    return edit;   
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
    else if(current_selection == image_drawing){
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

    if(current_selection == new_game || current_selection == image_drawing || current_selection == options || current_selection == editor){
        SDL_RenderCopy(room_grid -> renderer, menu_tex, &tile_src, &tile_drc);
        SDL_RenderPresent(room_grid -> renderer);
    }
    else if(current_selection == in_option_screen){ 
        //Draw controls screen
        SDL_RenderCopy(room_grid -> renderer, options_tex, NULL, NULL);
        SDL_RenderPresent(room_grid -> renderer);;
       
    }
   
}

void cycle_options(roomGrid *room_grid, char *argv[])
{
    
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
                        if( current_selection == image_drawing || current_selection == options || current_selection == editor ){
                            current_selection--;
                        }
                        highlight_area(room_grid, current_selection, menu_tex, options_tex);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if( current_selection == new_game || current_selection == image_drawing || current_selection == options ){
                            current_selection++;
                        }
                        highlight_area(room_grid, current_selection, menu_tex, options_tex);
                        break;   
                    }
                        
                    case SDLK_SPACE:

                        menu_space_press(room_grid, &current_selection, menu_tex, options_tex, &menu_running, argv);
                
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

void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running, char *argv[])
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

    if( *current_selection == image_drawing ){

    } 
}