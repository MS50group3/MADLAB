#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Typedefs necessary for external declaration of room_grid:
enum fin_unfin {unfinished, finished};
typedef enum fin_unfin fin_unfin;

enum compass{up = 0, right = 1, down = 2, left = 3};
typedef enum compass compass;

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

#define NUM_INSTRUCTIONS         68

/* External declaration of room grid */
extern roomGrid room_grid; 

/* External declaration of only shared function between madlab and interpreter */
extern void Run_interpreter(roomGrid *room_grid, char *argv[], 
	char *instructions_list[NUM_INSTRUCTIONS]);

