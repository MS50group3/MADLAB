#include "MadLab_headers.h"

//                      PROBLEM FUNCTION DEFINITIONS                      

// List of instructions to be used for printing.
void print_instruction(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS], int start, int end)
{
    int i;
    rg->finished = unfinished;

    for (i = start; i < end; ++i){
        print_some_text(rg, instructions_list[i]);
    }

}


// Just a list of instructions to be printed.
void get_instructions(char *instructions_list[NUM_INSTRUCTIONS])
{
    //Opening scenes instructions
    instructions_list[0] = "MadLab";
    instructions_list[1] = "Where_am_I";
    instructions_list[2] = "looks_like";
    instructions_list[3] = "door_locked";
    instructions_list[4] = "shenanigans";
    instructions_list[5] = "neill_shenanigans";
    instructions_list[6] = "maybe_if_I";
    instructions_list[7] = "press_spacebar";
    instructions_list[8] = "find_neill";
    instructions_list[9] = "lets_go";

    //Neill's notes instructions
    instructions_list[10] = "neill_note";
	instructions_list[11] = "coding_stuff";
	instructions_list[12] = "door_jammed";
	instructions_list[13] = "room_too_hot";
	instructions_list[14] = "using_some_code";
	instructions_list[15] = "number";
	instructions_list[16] = "less_than_ten";
	instructions_list[17] = "but_if_we_have";
	instructions_list[18] = "greater_ten";
	instructions_list[19] = "number_eq_eq_ten";
  	instructions_list[20] = "number_is_ten";
  	instructions_list[21] = "useful_later";

    //First part of first problem instructions
	instructions_list[22] = "fan_on_wall";
	instructions_list[23] = "cool_down_room";
	instructions_list[24] = "control_panel";
	instructions_list[25] = "neill_notes";
	instructions_list[26] = "change_temp";

    //Second part of first problem instrucions.
	instructions_list[27] = "that_worked";
	instructions_list[28] = "room_cooling";
}


// Used to print sets of instructions to the screen.
void print_some_text(roomGrid *rg, char *instruction)
{
    rg->refresh_counter = 0;
    rg->skip_checker = off;
    SDL_Surface* text_one = NULL;
    SDL_Texture* image;

    // The following few lines are used to create a filename to get the .bmp to print to screen.
    char prefix[LENGTH_PREFIX] = "Instructions/";
    char extension[LENGTH_EXTENSION] = ".bmp";
    char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1);

    strcpy(filename, prefix);
    strcat(filename, instruction);
    strcat(filename, extension);

    // Loads image in and checks it.
    text_one = SDL_LoadBMP(filename);
    image = SDL_CreateTextureFromSurface(rg -> renderer, text_one);

    if (text_one == NULL){
        printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    }

    // Update the surface and apply the image.
    SDL_RenderCopy(rg -> renderer, image, NULL, NULL);
    SDL_RenderPresent(rg -> renderer);

    // Wait the sleep time and free the malloc for the filename.
    look_for_action(rg);

    free(filename);
}

//Looks for actions relating to skipping or quitting.
void James_SDL_Events(roomGrid *rg)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)){

       switch (event.type){

            case SDL_QUIT:
                rg -> finished = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                rg -> skip_checker = 1;
                break;
            case SDL_KEYDOWN:
                rg -> skip_checker = 1;
                break;
        }
    }
}

//The refresh counter is used to delay a certain time whilst looking for exits.
void look_for_action(roomGrid *rg)
{
    do
    {
        ++(rg -> refresh_counter);
        SDL_Delay(SLEEP_TIME);
        SDL_QuitChecker(rg);
    }
    while(rg -> refresh_counter < NUM_REFRESHES && !rg -> skip_checker);
}


void SDL_QuitChecker(roomGrid *rg)
{
    James_SDL_Events(rg);
    if (rg -> finished){
        exit(1);
    }
}

void neill_notes(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS])
{
    rg -> finished = 0;

    //Prints the instructions for the Neill's Notes cutscene.
    print_instruction(rg, instructions_list, 10, 22);
}

void first_problem(roomGrid *rg, char *instructions_list[NUM_INSTRUCTIONS])
{
    rg -> finished = 0;
    wrong_right correct_indicator = incorrect;

    //Prints first part of the instructions.
    print_instruction(rg, instructions_list, 22, 27);

    //Now we go to the input screen for the text.
    do{
        input_screen(rg, &correct_indicator);
    }while(correct_indicator != correct);

    //Prints second part of the instructions.
    print_instruction(rg, instructions_list, 27, 29);

}

//Used to read in and print out the person's input.
void input_screen(roomGrid *rg, wrong_right *correct_indicator)
{
    SDL_Texture* image, *image_one;
    SDL_Surface *text, *text_one;
    SDL_Rect drcrect;
    char input_string[MAX_INPUT_CHARS], possible_answer[MAX_INPUT_CHARS];
    int input_index = 0, finish_checker = unfinished;

    //clear_screen(sw);
    initialise_input_string(input_string);
    initialise_drcrect(&drcrect, input_index);

    text_one = SDL_LoadBMP( "Instructions/code_entry.bmp" );
    if( text_one == NULL )
    {
      printf( "Unable to load image %s! SDL Error: %s\n", "bla", SDL_GetError() );
    }

    image_one = SDL_CreateTextureFromSurface(rg->renderer, text_one);
    TTF_Font *font = TTF_OpenFont("opendisplay.ttf", 200);

    if(font == NULL){
        printf("\nCouldn't load text.\n");
    }

    SDL_Color fg = { 0, 0, 0, 0};

    do{

        check_user_variable_input(rg, input_string, &input_index, &finish_checker);

        text = TTF_RenderText_Solid(font, input_string, fg) ;
        image = SDL_CreateTextureFromSurface(rg->renderer, text);

        SDL_RenderClear(rg->renderer);
        SDL_RenderCopy(rg->renderer, image_one, NULL, NULL);
        SDL_RenderCopy(rg->renderer, image, NULL, &drcrect);
        SDL_RenderPresent(rg->renderer);

        if(input_index == CHARS_IN_ANS + 1){
          finish_checker = finished;
        }

    }while(input_index < MAX_INPUT_CHARS && !finish_checker);

    create_answer_for_checking(possible_answer, input_string);

    if( strcmp(possible_answer, "fan < too hot") == 0){
        *correct_indicator = correct;
    }
}

void create_answer_for_checking(char possible_answer[MAX_INPUT_CHARS], char input_string[MAX_INPUT_CHARS])
{
  int i;

  for(i = 0; i < CHARS_IN_ANS; ++i){
        possible_answer[i] = input_string[i];
    }

  possible_answer[CHARS_IN_ANS] = '\0';
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

void check_user_variable_input(roomGrid *rg, char *input_string, int *input_index, int *finish_checker)
{
  //To identify event.
  SDL_Event event;

  int gameover = 0;

  while (gameover != INPUT_FINISHED){                                                                 //to make screen stay on.
    while( SDL_PollEvent( &event ) ){                                                                 //checks for events.
      if(event.type == SDL_KEYDOWN){                                                                  //checks for key being pressed
        char c = event.key.keysym.sym;                                                                //if the key is pressed assigns character
        if( (c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) ){
              if(c == ','){
                input_string[*input_index] = '<';
              }
              else if(c == '.'){
                input_string[*input_index] = '>';
              }
              else{
                input_string[*input_index] = c;
              }                                                                                        //puts all pressed characters in an array.
              ++(*input_index);                                                                        //adds one to the index.
              gameover = INPUT_FINISHED;
        }
        else if( c == '\b'){
          input_string[--(*input_index)] = ' ';
          gameover = INPUT_FINISHED; 
        }
        else if(c == '\r'){
          *finish_checker = finished;
          gameover = INPUT_FINISHED; 
        }
      }
    }
  }              

  input_string[MAX_INPUT_CHARS] = '\0';                                                               //concludes string

}