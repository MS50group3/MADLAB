/*
 * Interaction_Demo.c
 *
 *  Created on: 7 Nov 2014
 *      Author: James
 */

// 									---Main---

#include<stdio.h>
#include<stdlib.h>
#include <SDL.h>
#include "Interaction_Functions.h"

int main(int argc, char *argv[])
{
	//Window in which everything occurs.
	SDL_Simplewin sw;

	//List of instructions to be used for printing.
	char *instructions_list[NUM_INSTRUCTIONS];

	//Used for looping through the instructions.
	int i;

	James_SDL_Init(&sw);

	get_instructions(instructions_list);

	for(i = 0; i < NUM_INSTRUCTIONS; ++i){
		print_some_text(&sw, instructions_list[i]);
	}

	return(0);
}
