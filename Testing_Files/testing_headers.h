// PREPROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

///////////////////////////              Testing
#include "CUnit/Basic.h"
///////////////////////////

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
#define NUM_TILE_TYPES            4
#define NUM_DIRECTIONS            4
#define TERMINAL                  3


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

struct editor_input{
    int mouse_x; 
    int mouse_y;
    int add; 
    int remove;
};
typedef struct editor_input editor_input;

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

////////////////////////////                TESTING SPECIFIC

enum event {quit = 1, mousebutton = 2, keydown = 3};
typedef enum event event;

enum key {escape_key = 1, space_key = 2};
typedef enum key key;

//////////////////////////// 

//                                          FUNCTION PROTOTYPES

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name);

int close_CUnit(void);

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function);

void assert_test(int test, char *message);

void string_equal_test(char *string_one, char *string_two, char *message);

void test_makeRoom(void);

void initialise_working_room_components(roomGrid *room_grid, FILE *map_file);

void test_makeRoom_case(int **room_array_pointer, FILE *map_file);

void test_print_instruction(void);

void test_print_instruction_case(on_off problem_quitter);

void test_get_instructions(void);

void get_instructions_case(char *instructions_list, char *filename);

void test_print_instruction_to_screen(void);

void test_SDL_events(void);

void initialise_message(int event, int key);

void SDL_event_case(int event, int key);

void test_look_for_action(void);

void test_look_for_action_case(roomGrid *room_grid, on_off skip_checker, on_off problem_quitter);

void test_SDL_Quitchecker(void);

void SDL_Quitchecker_case(roomGrid *room_grid, fin_unfin fin);

void test_draw(void);

void test_draw_room(void);

void test_rcsrc_set(void);

void rcsrc_set_case(int x_coord, int y_coord, int width, int height, roomGrid *room_grid);

void test_rcobj_set(void);

void rcobj_set_case(int x_coord, int y_coord, int width, int height, int dest_x, int dest_y, roomGrid *room_grid);

void test_initialise_roomgrid_components(void);

void test_initialise_chicken(void);

void test_position_sprite(void);

void test_position_chicken(void);

void test_movement(void);

void movement_case(roomGrid *room_grid, int event, int key);

void test_sound_on_off(void);

void sound_on_off_case(roomGrid *room_grid, on_off pause);

void test_edge_detection(void);

void edge_detection_case(roomGrid *room_grid, int x_coord, int y_coord);

void test_possible(void);

void initialise_possible_components(roomGrid *room_grid);

void examine_possible_case(roomGrid *room_grid, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9);

void set_up_for_possible_case(roomGrid *room_grid, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9);

void possible_case(roomGrid *room_grid, int direction);

void test_move(void);

void examine_move(roomGrid *room_grid, int sprite_x_coord);

void move_case(roomGrid *room_grid, int direction);

void test_interactProbe(void);

void initialise_roomGrid_memory(roomGrid *room_grid);

void initialise_interactProbe_location(roomGrid *room_grid);

void examine_interactProbe_case(roomGrid *room_grid, on_off action);

void interactProbe_case(roomGrid *room_grid, int direction, on_off action);

void test_action(void);

int action_case(problem *prob_point, roomGrid *room_grid, progress *puzzle, bool puzz_1_seen, bool puzz_1_solved, bool puzz_3_solved, int probe);

void test_door_hinge_problem(void);

void door_hinge_problem_case(progress *puzzle, bool puzz_2_seen, bool player_a, bool player_b);

void test_find_weight_a(void);

void find_weight_a_case(progress *puzzle, bool puzzle_4_seen);

void test_find_weight_b(void);

void find_weight_b_case(progress *puzzle, bool puzzle_4_seen);

void test_hen_sequence(void);

void hen_sequence_iteration(Chicken *hen);

void test_initialise_problem(void);

void initialise_problem_case(problem *prob_point, char *correct_answer, int first_inst_start, int first_instr_end,
                             int num_chars_ans, int second_inst_end);

void test_permit_chicken(void);

void permit_chicken_case(Chicken *hen, int direction, int Chicken_x);

void examine_chicken_case(Chicken *hen, int Chicken_x);

void test_chicken_help(void);

void test_chicken_direction(void);

void examine_chicken_direction_case(Chicken *hen, int Chicken_x);

void chicken_direction_case(Chicken *hen, compass direction, int Chicken_x);

void test_chicken_edge_detection(void);

void chicken_edge_detection_case(Chicken *hen, int Chicken_x, int Chicken_y);

void test_eggfault(void);

void eggfault_case(Chicken *hen, roomGrid *room_grid, int sprite_x, int sprite_y, int hen_x, int hen_y);

void test_changeChickenDirection(void);

void changeChickenDirection_case(Chicken *hen, compass direction);

void test_problem_generator(void);

void test_free_room_array(void);

void test_input_screen(void);

void test_create_answer_for_checking(void);

void test_initialise_input_string(void);

void test_initialise_drcrect(void);

void test_check_user_variable_input(void);

void user_check_variable_input_case(roomGrid *room_grid, char c, int event);

void test_run_menu_screen(void);

void run_menu_screen_case(void);

void test_save(void);

void save_case(roomGrid *room_grid);

void test_level_editor(void);

void test_draw_edited_map(void);

void draw_edited_map_case(int input_add, int edit_previous, int input_remove, int map_array[ROOM_Y][ROOM_X], Edit edit, editor_input input);

void test_configure_mouse(void);

void test_initialise_level_editor_map(void);

void test_highlight_area(void);

void highlight_area_case(menu_options option);

void test_cycle_options(void);

void cycle_options_case(SDL_Event event, int current_selection);

void test_menu_space_press(void);

void menu_space_press_case(SDL_Event event, int current_selection);

