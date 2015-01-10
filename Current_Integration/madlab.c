// PREPROCESSING

#include "extern.h"

#define SCREEN_WIDTH     		800
#define SCREEN_HEIGHT    		640
#define TILE_SIZE         		 32
#define ROOM_X            		 25
#define ROOM_Y            		 20
#define SPRITE_VEL         		  5
#define SDL_8BITCOLOUR   		256
#define SLEEP_TIME       		100
#define NUM_INSTRUCTIONS  		 68
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
#define TERMINAL                  2
#define DESK                      3
#define BLANK                     0
#define NUM_DIRECTIONS            4
#define NUM_TILE_TYPES			  4
#define NUM_ARGS                  3

// TYPEDEFS AND ENUMERATION

enum tileType{path = 0, obstacle = 1, puz_1 = 9, puz_2 = 3, puz_3 = 1, puz_4 = 7, puz_5 = 6, puz_6 = 5};
typedef enum tileType tileType;

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum on_off {off, on};
typedef enum on_off on_off;

enum menu_options{new_game = 1, image_drawing = 2, options = 3,  editor = 4, in_option_screen = 7};
typedef enum menu_options menu_options;

enum special_buttons{enter = '\r', backspace = '\b', escape = 27};
typedef enum special_buttons special_buttons;

enum success_unsuccess {unsuccessful, successful};
typedef enum success_unsuccess success_unsuccess;

enum looping_array {start_word, start_number, end_number, current_iteration, variable};
typedef enum looping_array looping_array;

enum inst{ FD, LT, RT, FROM, TO };
typedef enum inst Inst;

enum op{ ADD, SUB, MULT, DIV, NONE };
typedef enum op Op;

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
    SDL_Texture *cursor_tex; 
    SDL_Rect cursor_src;
    SDL_Rect cursor_dst;
}; 
typedef struct cursor cursor;

struct editor_input{
    int mouse_x; 
    int mouse_y;
    int mouse_tile_x;
    int mouse_tile_y;
    int add; 
    int remove;
};
typedef struct editor_input editor_input;

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
void run_main_game(roomGrid *room_grid, progress *puzzle, Chicken *hen, char *instructions_list[NUM_INSTRUCTIONS]);
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
void draw_obj(SDL_Texture *grafix_tex, roomGrid *room_grid, progress *puzzle, Chicken *hen);
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

void run_menu_screen(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS]);
void load_menu_frame(roomGrid *room_grid);
void highlight_area(roomGrid *room_grid, int current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex);
bool getEvent(roomGrid *room_grid);
void cycle_options(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS]);
void getloadscreenevent(roomGrid *room_grid);
void getkeyEvent(roomGrid *room_grid, int x);
void runloadscreen();
void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS]);

void level_editor(roomGrid *room_grid);
void load_image(roomGrid *room_grid, SDL_Surface **surf, SDL_Texture **tex, char *image_name);


//FUNCTIONS FOR EDITOR
void save(roomGrid *room_grid);
void initialise_level_editor_map(int **map_array);
void level_editor(roomGrid *room_grid);
void editor_interactions(roomGrid *room_grid, bool *running, editor_input *editor_input);

void configure_mouse(int excess, editor_input *editor_input, cursor *cursor);

Edit draw_edited_map(roomGrid *room_grid, editor_input *editor_input, Edit edit, SDL_Texture *grafix_tex, cursor *cursor);

//FUNCTION FOR INTERPRETER BONUS FEATURE
void image_drawing_tool(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS]);

//MAIN

int main(int argc, char *argv[])
{
    roomGrid *room_grid = (roomGrid *)malloc(sizeof(roomGrid));

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    Chicken Fowl, *hen;
    hen = &Fowl;

    char *instructions_list[NUM_INSTRUCTIONS];

    FILE *map_file = NULL;
    map_file = fopen(argv[1], "r");

    if (map_file == NULL){
       printf("File could not be opened.\n");
       exit(1);
    }

    printf("File was opened.\n");

    makeRoom(room_grid, map_file);

    fclose(map_file);

    get_instructions(instructions_list);

    run_menu_screen(room_grid, argv, argc, instructions_list);

    run_main_game(room_grid, puzzle, hen, instructions_list);

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
void run_main_game(roomGrid *room_grid, progress *puzzle, Chicken *hen, char *instructions_list[NUM_INSTRUCTIONS])
{
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
    instructions_list[1] = "my_lab";
    instructions_list[2] = "my_assistant";
    instructions_list[3] = "shenanigans";
    instructions_list[4] = "loves_shenanigans";
    instructions_list[5] = "he_pressed";
    instructions_list[6] = "the_secret_button";
    instructions_list[7] = "bad_things_happen";
    instructions_list[8] = "the_secret_button";
    instructions_list[9] = "fix_my_lab";

    //Neill's notes instructions
    instructions_list[10] = "neill_left_notes";
	instructions_list[11] = "coding_stuff";
	instructions_list[12] = "stuff_in_here";
	instructions_list[13] = "down_temperature";
	instructions_list[14] = "fan_lt_too_cold";
	instructions_list[15] = "less_than_too_cold";
	instructions_list[16] = "fan_gt_too_cold";
	instructions_list[17] = "greater_than_too_cold";
	instructions_list[18] = "fan_eq_too_cold";
	instructions_list[19] = "at_too_cold";
  	instructions_list[20] = "take_notes";
  	instructions_list[21] = "go_check_out";

    //First part of first problem instructions
	instructions_list[22] = "heres_fan";
	instructions_list[23] = "cool_down_room";
	instructions_list[24] = "control_panel";
	instructions_list[25] = "like_neills_notes";
	instructions_list[26] = "change_temperature";

    //Second part of first problem instrucions.
	instructions_list[27] = "it_worked";
	instructions_list[28] = "cooling_down";

    //First block of instructions
    instructions_list[29] = "computer_fritz";
    instructions_list[30] = "enter_a_code";
    instructions_list[31] = "code_is_five";
    instructions_list[32] = "binary";
    instructions_list[33] = "info_here";
    instructions_list[34] = "binary_notes";

    //Second block of instructions
    instructions_list[35] = "mended_it";

    //Hen related .bmp images
    instructions_list[36] = "chicken_in_here";
    instructions_list[37] = "leave_it_alone";
    instructions_list[38] = "come_back_let_it_out";
    instructions_list[39] = "latch_loose";
    instructions_list[40] = "got_out";
    instructions_list[41] = "eggfault";

    //Discovering the x problem.
    instructions_list[42] = "problem_with_door";
    instructions_list[43] = "hinge_sticks";
    instructions_list[44] = "pressure_on_hinge";
    instructions_list[45] = "weight_on_hinge_five";
    instructions_list[46] = "x_eq_five";
    instructions_list[47] = "weights_in_lab";
    instructions_list[48] = "a_weight_b_weight";
    instructions_list[49] = "a_eq_b_eq";
    instructions_list[50] = "use_these_weights";
    instructions_list[51] = "right_pressure";
    instructions_list[52] = "sort_out_this_door";

    //Picking up the a weight.
    instructions_list[53] = "found_a_weight";
    instructions_list[54] = "will_be_useful";

    //Picking up the b weight.
    instructions_list[55] = "b_weight";
    instructions_list[56] = "to_door_hinge";

    //Combining the weights.
    instructions_list[57] = "a_weight_on_hinge";
    instructions_list[58] = "b_weight_on_hinge";
    instructions_list[59] = "both_weights_on_hinge";
    instructions_list[60] = "so_x_eq_a_eq_b_eq";
    instructions_list[61] = "the_right_weight";

    //No file for parsing specified.
    instructions_list[62] = "works_yet";
    instructions_list[63] = "play_game";

    //File for parser specified.
    instructions_list[64] = "computer_to_draw";
    instructions_list[65] = "see_if_it_works";

    //Error with parser.
    instructions_list[66] = "something_wrong";
    instructions_list[67] = "check_answer";

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
    static int first_pass = 0;

    SDL_Surface *grafix;
    SDL_Texture *grafix_tex;

    /*One texture to rule them all*/
    grafix = IMG_Load("gfx/tile_array.png");  //if you want to add new items to the code check the txt file for the coordinates
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
        draw_obj(grafix_tex, room_grid, puzzle, hen);

        /*RenderClear to wipe framebuffer, RenderCopy to compose final framebuffer, RenderPresent puts on screen*/
        SDL_RenderCopy(room_grid -> renderer, grafix_tex, &hen -> srcChicken, &hen -> dstChicken);
        SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_sprite_pos, &room_grid -> rc_sprite);  //draws 
        SDL_RenderPresent(room_grid -> renderer);

        if(puzzle -> puzzle_1_solved && puzzle -> puzzle_2_solved && puzzle -> puzzle_3_solved && first_pass == 0){
            printf("\n\n\n\nTop fucking work!\n\n\n\n\n");
            ++first_pass;
        }
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
void draw_obj(SDL_Texture *grafix_tex, roomGrid *room_grid, progress *puzzle, Chicken *hen)
{
    /*draw and position extractor*/
    rcobj_set(264, 63, 64, 64, 0, 0, grafix_tex, room_grid);

    /*draw and position fan*/
    rcobj_set(0, 62, 64, 64, 737, 318, grafix_tex, room_grid);

    /*draw weight a*/
    if((puzzle -> player_has_a_weight == false) && (puzzle -> a_weight_on_hinge == false) ){
        rcobj_set(208, 131, 32, 32, 0, 128, grafix_tex, room_grid);
    }

    /*draw weight b*/
    if((puzzle -> player_has_b_weight == false) && (puzzle -> b_weight_on_hinge == false)){
        rcobj_set(240, 131, 32, 32, 672, 0, grafix_tex, room_grid);
    }
    
    /*draw door*/
    rcobj_set(332, 66, 96, 96, 416, 0, grafix_tex, room_grid);

    /*draw chicken_cage*/
    if(hen -> chicken_cross_road == true){
        rcobj_set(529, 0, 96, 96, 192, 256, grafix_tex, room_grid);
    }
    else{
        rcobj_set(433, 0, 96, 96, 192, 256, grafix_tex, room_grid);
    }

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

        case(puz_2):        if(puzzle -> puzzle_1_seen == true){
                                door_hinge_problem(room_grid, puzzle, instructions_list);
                            }
                            return 0;
                            break; 

        case(puz_3):        if ((puzzle -> puzzle_1_seen == true) && (puzzle -> puzzle_3_solved) == false){

                                initialise_problem(prob_point, "101", 29, 35, 3, 36);
                                problem_generator(room_grid, instructions_list, prob_point, &puzzle -> puzzle_3_solved, "Instructions/code_entry_two.bmp");

                                return 0;
                            }
                            return 1;
                            break;

        case(puz_4):        if((puzzle -> puzzle_1_seen == true) && (puzzle -> puzzle_2_seen == true)){
                                find_weight_a(room_grid, puzzle, instructions_list);
                            }
                            return 0;
                            break; 

        case(puz_5):        hen_sequence(hen, room_grid, instructions_list);
                            return 0;
                            break;

        case(puz_6):        if((puzzle -> puzzle_1_seen == true) && (puzzle -> puzzle_2_seen == true)){
                                find_weight_b(room_grid, puzzle, instructions_list);
                            }
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
        puzzle -> puzzle_2_solved = true;
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

  int i = 0, j = 0;


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

void run_menu_screen(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS])
{
    static int first_pass = 0;

    if(first_pass == 0){
        initialise_SDL_component(room_grid->window, room_grid);
        ++first_pass;
    }

    load_menu_frame(room_grid);
    
    cycle_options(room_grid, argv, argc, instructions_list);

}

void save(roomGrid *room_grid){
    
    FILE *writing_file;

    writing_file = fopen("Your_level.txt","w");
    if(writing_file == NULL) {
        printf("ERROR opening file...exiting\n");
    }
    
    for (int i = 0; i < ROOM_Y; ++i)
    {
        for (int j = 0; j < ROOM_X; ++j)
        {
            fprintf(writing_file, "%d ", room_grid->room_array[i][j]);
        }
        
        fprintf(writing_file,"\n");
    }
    
    fclose(writing_file);
}


void level_editor(roomGrid *room_grid)
{
    Edit edit;
    bool running = true;
    editor_input editor_input;
    cursor cursor;
    
    editor_input.add = 0;
    editor_input.remove = 0;
    
    edit.previous  = 0;
    edit.src_value = 0;
    
    int excess = 0;
    
    initialise_level_editor_map(room_grid->room_array);
    
    // Background, tile, cursor and menu stuff
    SDL_Surface *grafix_surf, *cursor_surf, *menu_surf, *options_surf;
    SDL_Texture *grafix_tex, *menu_tex, *options_tex;
    
    // One texture to rule them all? (Attempt)
    load_image(room_grid, &grafix_surf, &grafix_tex, "tile_array.png");

    // Make the cursor - more complicated
    cursor_surf = IMG_Load("cursor.png");
    Uint32 colorkey = SDL_MapRGB(cursor_surf->format, 127, 0, 127);
    SDL_SetColorKey( cursor_surf, SDL_TRUE, colorkey);
    cursor.cursor_tex = SDL_CreateTextureFromSurface(room_grid -> renderer, cursor_surf);
    SDL_FreeSurface (cursor_surf);
    
    
    // Run the meat of the program.
    while(running){
        
        editor_interactions(room_grid, &running, &editor_input);
        
        // Get the exact mouse coords and put them in editor_input
        SDL_GetMouseState(&editor_input.mouse_x, &editor_input.mouse_y);

        configure_mouse(excess, &editor_input, &cursor);

        edit = draw_edited_map(room_grid, &editor_input, edit, grafix_tex, &cursor);
    }
    
    load_menu_frame(room_grid);

    load_image(room_grid, &menu_surf, &menu_tex, "screen2.png");

    load_image(room_grid, &options_surf, &options_tex, "controls.png");
    
    highlight_area(room_grid, editor, menu_tex, options_tex);
    
}


Edit draw_edited_map(roomGrid *room_grid, editor_input *editor_input, Edit edit, SDL_Texture *grafix_tex, cursor *cursor)
{

	// If the mouse has been held down between events:
    if (editor_input->add == edit.previous && edit.previous == 1) 
    {
    	// Continue to use the original tile type:
        room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x] = edit.src_value; 
    }

    // If we get a NEW add signal:
    else if(editor_input->add == 1) 
    {   
        room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x]++; // Increment the tile type
        room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x] = room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x] % NUM_TILE_TYPES; 
        edit.src_value = room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x];
    } 
    
    if (editor_input->remove == 1)
    {
        room_grid->room_array[editor_input->mouse_tile_y][editor_input->mouse_tile_x] = BLANK;
    }
    
    // Update the room graphics
    for (int i = 0; i < ROOM_Y; ++i)
    {
        for (int j = 0; j < ROOM_X; ++j)
        {   
            // Where to put the tile
            room_grid -> rc_dest.x = (j * TILE_SIZE);              //the destination rects are set to i and j
            room_grid -> rc_dest.y = (i * TILE_SIZE);
            room_grid -> rc_dest.w = TILE_SIZE;
            room_grid -> rc_dest.h = TILE_SIZE;
            
            if (room_grid->room_array[i][j] == WALL)
            {   
                // If the array element is a 1, draw a wall
                rcsrc_set(0, 138, 32, 32, grafix_tex, room_grid);
                SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_src, &room_grid -> rc_dest);
            }

            else if ( room_grid->room_array[i][j] == BLANK)
            {   // If the element is a 0, draw a floor tile
                rcsrc_set(34, 138, 32, 32, grafix_tex, room_grid);
                SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_src, &room_grid -> rc_dest);
            }

            else if ( room_grid->room_array[i][j] == TERMINAL)
            {   // If the element is a 2, draw a red tile
                rcsrc_set(71, 138, 32, 32, grafix_tex, room_grid);
                SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_src, &room_grid -> rc_dest);
            }

            else if ( room_grid->room_array[i][j] == DESK)
            {   // If the element is a 2, draw a red tile
                rcsrc_set(140, 137, 32, 32, grafix_tex, room_grid);
                SDL_RenderCopy(room_grid -> renderer, grafix_tex, &room_grid -> rc_src, &room_grid -> rc_dest);
            }

        }
    }

    SDL_RenderCopy(room_grid -> renderer, cursor->cursor_tex, &cursor->cursor_src, &cursor->cursor_dst);
    
    // Update the screen with the latest render 
    SDL_RenderPresent(room_grid -> renderer);
    SDL_RenderClear(room_grid -> renderer); // Clear the renderer

    edit.previous = editor_input->add;

    return edit;   
}

void configure_mouse(int excess, editor_input *editor_input, cursor *cursor)
{
    // Round the coords to the nearest multiple of TILE_SIZE:
    excess = editor_input->mouse_x % TILE_SIZE;
    editor_input->mouse_x = editor_input->mouse_x - excess;
    
    excess = editor_input->mouse_y % TILE_SIZE;
    editor_input->mouse_y = editor_input->mouse_y - excess;

    // Which tile 'element' are we in:
    editor_input->mouse_tile_x = editor_input->mouse_x / TILE_SIZE;
    editor_input->mouse_tile_y = editor_input->mouse_y / TILE_SIZE;
   
    // cursor details
    cursor->x = editor_input->mouse_x;
    cursor->y = editor_input->mouse_y;
    
    // Where to get the image from (relative)
    cursor->cursor_src.y = 0;
    cursor->cursor_src.x = 0;
    cursor->cursor_src.w = TILE_SIZE;
    cursor->cursor_src.h = TILE_SIZE;
    
    // Where to put it (relative)
    cursor->cursor_dst.y = cursor->y;
    cursor->cursor_dst.x = cursor->x;
    cursor->cursor_dst.w = TILE_SIZE;
    cursor->cursor_dst.h = TILE_SIZE;
}

void editor_interactions(roomGrid *room_grid, bool *running, editor_input *editor_input)
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event))  // If there is an event
    {
        switch (event.type)
        {
            case SDL_QUIT:	// General SDL Quit signal
                exit(0);
            break;
                
            // Keydowns: save and quit
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
            	{
                	case SDLK_q:
                    	*running = false; // Quit with 'Q' key
                    break;
                    
	                case SDLK_s:
	                    save(room_grid);  // Save with 'S'
	                break;
                    
               		default:
                	break;
            	}
            break;
                
            // Mouse Click: Add or remove a tile
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
            	{
                	case SDL_BUTTON_LEFT:
	                    editor_input -> add = 1;
	                break;
	                    
	                case SDL_BUTTON_RIGHT:
	                    editor_input -> remove = 1;
	                break;
	                    
	                default:
	                break;
            	}
            break;
                
            // "Unclick": Reset the add/remove flags on key release
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
	            {
	                case SDL_BUTTON_LEFT:
	                    editor_input -> add = 0;
	                break;
	                    
	                case SDL_BUTTON_RIGHT:
	                    editor_input -> remove = 0;
	                break;
	                    
	                default:
	                    break;
	            }
            break;
        }
    }
}


void initialise_level_editor_map(int **map_array)
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

// draw correct part of background image each time (a rectangular box around the written options)
void highlight_area(roomGrid *room_grid, int current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex){
    
   SDL_Rect tile_src, tile_drc;

   // Draw original background.
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
        // Draw controls screen
        SDL_RenderCopy(room_grid -> renderer, options_tex, NULL, NULL);
        SDL_RenderPresent(room_grid -> renderer);;
    }  
}

void cycle_options(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS])
{
    
    SDL_Event event;
    bool menu_running = true;
    int current_selection = new_game; // Fie menu defaults to new_game

    SDL_Surface *menu_surf = NULL, *options_surf = NULL;
    SDL_Texture *menu_tex = NULL, *options_tex = NULL;

    load_image(room_grid, &menu_surf, &menu_tex, "screen2.png"); // Yellow text

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

                        menu_space_press(room_grid, &current_selection, menu_tex, options_tex, &menu_running, argv, argc, instructions_list);
                
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

void menu_space_press(roomGrid *room_grid, int *current_selection, SDL_Texture *menu_tex, SDL_Texture *options_tex, bool *menu_running, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS])
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

        image_drawing_tool(room_grid, argv, argc, instructions_list);
        load_menu_frame(room_grid);
        highlight_area(room_grid, *current_selection, menu_tex, options_tex);

    } 
}


void image_drawing_tool(roomGrid *room_grid, char *argv[], int argc, char *instructions_list[NUM_INSTRUCTIONS])
{

    if(argc == NUM_ARGS) {

        print_instruction(room_grid, instructions_list, 64, 66);

        Run_interpreter(room_grid, argv, instructions_list); 
        // Run_interpreter is external

        room_grid->refresh_counter = 0;
        room_grid->skip_checker = off;
        look_for_action(room_grid);
    }
    else {

        print_instruction(room_grid, instructions_list, 62, 64);

    }
}


