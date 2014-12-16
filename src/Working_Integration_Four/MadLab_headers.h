#include "MadLab_headers.h"

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

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum on_off {off, on};
typedef enum on_off on_off;

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

//FUNCTIONS FOR MOVEMENT

void initialise_SDL_component(SDL_Window *window, roomGrid *rg);

void makeRoom(roomGrid *rg, FILE *fp);

void draw(roomGrid *rg, progress *pz, Mix_Chunk *mus, char *instructions_list[NUM_INSTRUCTIONS]);

void run(roomGrid *rg, progress *pz);

void possible(roomGrid *rg, progress *pz);

int action(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS]);

void interactProbe(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS]);

void move(roomGrid *rg, progress *pz);

void position_sprite(roomGrid *rg);

void movement(roomGrid *rg, progress *pz, char *instructions_list[NUM_INSTRUCTIONS]);

void collision_detection(roomGrid *rg);

void draw_room(SDL_Surface *background, SDL_Surface *sprite, SDL_Texture *backtex, SDL_Texture *spritetex, 
               roomGrid *rg);

void initialise_roomgrid_components(roomGrid *rg, progress *pz);

void rcsrc_set(int x_coord, int y_coord, int width, int height, SDL_Texture *backtex, roomGrid *rg);

void printArray(roomGrid *rg, progress *pz);

void freeArray(roomGrid *rg);

//FUNCTIONS FOR PROBLEMS

void James_SDL_Events(roomGrid *rg);

void look_for_action(roomGrid *rg);

void SDL_QuitChecker(roomGrid *rg);

void print_instruction(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS], int start, int end);

void print_some_text(roomGrid *rg, char *instruction);

void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);

void neill_notes(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS]);

void first_problem(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS]);

void input_screen(roomGrid *rg, wrong_right *correct_indicator);

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS]);

void initialise_input_string(char input_string[MAX_INPUT_CHARS]);

void initialise_drcrect(SDL_Rect *drcrect, int input_index);

void check_user_variable_input(roomGrid *rg, char *input_string, int *input_index, int *finish_checker);