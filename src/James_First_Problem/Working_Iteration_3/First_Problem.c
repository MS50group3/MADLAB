/*
 * First_Problem.c
 *
 *  Created on: 7 Nov 2014
 *      Author: James
 */

#include<stdio.h>
#include "Interaction_Functions.h"

int main(int argc, char *argv[])
{
	//Window in which everything occurs.
	SDL_Simplewin sw;

	//List of instructions to be used for printing.
	char *instructions_list[NUM_INSTRUCTIONS_ONE + NUM_INSTRUCTIONS_TWO];

	//Used for looping through the instructions.
	int i;

	//Used to check if the answer is wrong or right.
	wrong_right correct_indicator = incorrect;

	//Address of the background for the input entry.
	char *background_address = "Instructions/code_entry.bmp";

	//Character string for the right answer.
	char *correct_answer = "fan < too hot";

	//Initialises window
	James_SDL_Init(&sw);

	//Finds the list of instructions 
	get_instructions(instructions_list);

	//Prints the first list of instructions.
	for(i = 0; i < NUM_INSTRUCTIONS_ONE; ++i){
		print_text(&sw, instructions_list[i]);
	}

	//Now we go to the input screen for the text.
	do{
		input_screen(&sw, &correct_indicator, background_address, correct_answer);
	}while(correct_indicator != correct);

	//Prints the follow up set of instructions.
	for(i = NUM_INSTRUCTIONS_ONE; i < NUM_INSTRUCTIONS_ONE + NUM_INSTRUCTIONS_TWO; ++i){
		print_text(&sw, instructions_list[i]);
	}

	return(0);

}
