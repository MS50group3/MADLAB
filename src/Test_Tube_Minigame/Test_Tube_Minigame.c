/*
 *
 *  Created on: 7 Nov 2014
 *      Author: James
 */

 #define NUM_QUESTIONS 10
 #define QUESTION_ANSWER 2

#include<stdio.h>
#include "Interaction_Functions.h"

void get_questions_answers(char *question_answer_array[NUM_QUESTIONS][QUESTION_ANSWER]);

int main(int argc, char *argv[])
{
	//Window in which everything occurs.
	SDL_Simplewin sw;

	//Array holding questions and answers.
	char *question_answer_array[NUM_QUESTIONS][QUESTION_ANSWER];

	//Initialises window
	James_SDL_Init(&sw);

	get_questions_answers(question_answer_array);

	return(0);

}

void get_questions_answers(char *question_answer_array[NUM_QUESTIONS][QUESTION_ANSWER])
{

}
