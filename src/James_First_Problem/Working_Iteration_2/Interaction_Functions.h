/*
 * Interaction_Functions.h
 *
 *  Created on: 7 Nov 2014
 *      Author: James
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SDL_8BITCOLOUR 256
#define SLEEP_TIME 100
#define NUM_INSTRUCTIONS_ONE 5
#define NUM_INSTRUCTIONS_TWO 2
#define LENGTH_EXTENSION 5
#define LENGTH_PREFIX 14
#define NUM_REFRESHES 50
#define MAX_INPUT_CHARS 20
#define INPUT_FINISHED 100000000
#define CHARS_IN_ANS 13

#define RECT_X 190
#define RECT_Y 325
#define RECT_W 700
#define RECT_H 150

//									---Structures---

// All info required for windows / renderer & event loop
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Surface *surface;
};
typedef struct SDL_Simplewin SDL_Simplewin;

enum wrong_right {correct, incorrect};
typedef enum wrong_right wrong_right;

enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum on_off {off, on};
typedef enum on_off on_off;

// 									---Functions---

void James_SDL_Init(SDL_Simplewin *sw);
void James_SDL_Events(SDL_Simplewin *sw, int *skip_checker);
void James_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void print_text(SDL_Simplewin *sw, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS_ONE + NUM_INSTRUCTIONS_TWO]);
void look_for_action(int *refresh_counter, SDL_Simplewin *sw, int *skip_checker);
void SDL_QuitChecker(SDL_Simplewin *sw, int *skip_checker);
void input_screen(SDL_Simplewin *sw, wrong_right *correct_indicator);
void initialise_input_string(char input_string[MAX_INPUT_CHARS]);
void initialise_drcrect(SDL_Rect *drcrect, int input_index);
void check_user_variable_input(SDL_Simplewin *sw, char *input_string, int *input_index, int *finish_checker);
void clear_screen(SDL_Simplewin *sw);
void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS]);