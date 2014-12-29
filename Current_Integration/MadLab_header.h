// PREPROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Testing
#include "CUnit/Basic.h"
//

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

enum menu_options{new_game = 1, load_game = 2, options = 3,  editor = 4, in_option_screen = 7};
typedef enum menu_options menu_options;

enum special_buttons{enter = '\r', backspace = '\b', escape = 27};
typedef enum special_buttons special_buttons;

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
Edit draw_edited_map(int map_array[ROOM_Y][ROOM_X], input input, int tile_x, int tile_y, SDL_Texture *tile_tex, SDL_Rect tile_src, SDL_Rect tile_dst, 
                     roomGrid *room_grid, SDL_Texture *cursor_tex, SDL_Rect cursor_src, SDL_Rect cursor_dst, SDL_Texture *back_tex, SDL_Texture *red_tex, Edit edit);

//TESTING FUNCTIONS

void test_makeRoom(void);