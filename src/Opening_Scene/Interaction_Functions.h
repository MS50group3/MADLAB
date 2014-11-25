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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SDL_8BITCOLOUR 256
#define SLEEP_TIME 100
#define NUM_INSTRUCTIONS 10
#define LENGTH_EXTENSION 5
#define LENGTH_PREFIX 14
#define NUM_REFRESHES 50

//									---Structures---

// All info required for windows / renderer & event loop
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Surface *surface;
};
typedef struct SDL_Simplewin SDL_Simplewin;

// 									---Functions---

void James_SDL_Init(SDL_Simplewin *sw);
void James_SDL_Events(SDL_Simplewin *sw, int *skip_checker);
void James_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void print_some_text(SDL_Simplewin *sw, char *instruction);
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS]);
void look_for_action(int *refresh_counter, SDL_Simplewin *sw, int *skip_checker);
void SDL_QuitChecker(SDL_Simplewin *sw, int *skip_checker);
