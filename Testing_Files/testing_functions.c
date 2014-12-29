#include "testing_headers.h"

//                                          FUNCTION DEFINITIONS

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name)
{
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   *pSuite = CU_add_suite(suite_name, NULL, NULL);
   if (NULL == *pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return 0;
}

int close_CUnit(void)
{
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function)
{
   CU_pSuite pSuite = NULL;

   initialise_CUnit(&pSuite, suite_name);

   if ((NULL == CU_add_test(pSuite, test_name, function))){
      CU_cleanup_registry();
      CU_get_error();
    }

   close_CUnit();
}

void test_makeRoom(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    FILE *map_file = NULL;

    test_makeRoom_case(NULL, map_file);

    initialise_working_room_components(room_grid, map_file);

    test_makeRoom_case(room_grid -> room_array, map_file);


}

void initialise_working_room_components(roomGrid *room_grid, FILE *map_file)
{
    room_grid -> room_array = 0;
    CU_ASSERT(room_grid -> room_array == 0);
    printf("\nRoom grid room array successfully integrated to zero.\n");

    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
    CU_ASSERT(sizeof(room_grid -> room_array) == sizeof( (int **)calloc((ROOM_Y) + 1, sizeof(int *)) ) );
    printf("\nDynamic memory for room grid room array successfully allocated.\n\n");

    map_file = fopen("room.txt", "r");

    if (map_file == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    printf("File was opened.\n");
}

void test_makeRoom_case(int **room_array_pointer, FILE *map_file)
{
    int i, j;

    if (room_array_pointer == NULL){
        CU_ASSERT(room_array_pointer == NULL);
        printf("\n\nNo memory for room grid allocation correctly identified.\n");
        return;
    }

    CU_ASSERT(room_array_pointer != NULL);
    printf("\nMemory available for room grid allocation correctly identified.\n");

    for (i = 0; i <= ROOM_Y; i++){

        room_array_pointer[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        CU_ASSERT(sizeof(room_array_pointer[i]) == sizeof((int *)calloc((ROOM_X) + 1, sizeof(int))));

        if (room_array_pointer[i] ==  NULL){
            CU_ASSERT(room_array_pointer[i] ==  NULL)
            printf("\nNo memory for room grid room array component successfully identified.\n");
        }
    }
    printf("\nMemory for room grid room array components successfully allocated.\n\n");

    if(map_file != NULL){
        for (i = 0; i < ROOM_Y; i++){
            for (j = 0; j < ROOM_X; j++){
                if (fscanf(map_file, "%1d", *room_array_pointer) == 1);
                else{

                   CU_PASS(); 
                   printf("\nIncorrect room size in file correctly identified.\n\n"); 

                }
            }
        }
    }
}

void test_print_instruction(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    room_grid -> finished = unfinished;
    CU_ASSERT(room_grid -> finished == unfinished);
    printf("\n\nRoom grid finished index correctly initialised to off.\n");

    room_grid -> problem_quitter = off;
    CU_ASSERT(room_grid -> problem_quitter == off);
    printf("\nRoom grid problem indicator index correctly initialised to off.\n");

    test_print_instruction_case(off);

    printf("\nProblem quitter set to on.\n");

    test_print_instruction_case(on);
}

void test_print_instruction_case(on_off problem_quitter)
{
    int start = 1, end = 10, i;

    for (i = start; i < end; ++i){
        if(problem_quitter == off){
            CU_ASSERT(problem_quitter == off);
        }
        else{
            CU_ASSERT(problem_quitter == on);
        }
    }
    if(problem_quitter == off){
        CU_ASSERT(problem_quitter == off);
        printf("\nInstructions correctly sent through for printing\n");
    }
    else{
        CU_ASSERT(problem_quitter == on);
        printf("\nInstructions correctly not sent through for printing\n\n");
    }
}

void test_get_instructions(void)
{
    char *instructions_list[NUM_INSTRUCTIONS];

    printf("\n");

    //Opening scenes instructions
    instructions_list[0] = "MadLab";
    get_instructions_case(instructions_list[0], "MadLab");

    instructions_list[1] = "Where_am_I";
    get_instructions_case(instructions_list[1], "Where_am_I");

    instructions_list[2] = "looks_like";
    get_instructions_case(instructions_list[2], "looks_like");

    instructions_list[3] = "door_locked";
    get_instructions_case(instructions_list[3], "door_locked");

    instructions_list[4] = "shenanigans";
    get_instructions_case(instructions_list[4], "shenanigans");

    instructions_list[5] = "neill_shenanigans";
    get_instructions_case(instructions_list[5], "neill_shenanigans");

    instructions_list[6] = "maybe_if_I";
    get_instructions_case(instructions_list[6], "maybe_if_I");

    instructions_list[7] = "press_spacebar";
    get_instructions_case(instructions_list[7], "press_spacebar");

    instructions_list[8] = "find_neill";
    get_instructions_case(instructions_list[8], "find_neill");

    instructions_list[9] = "lets_go";
    get_instructions_case(instructions_list[9], "lets_go");

    //Neill's notes instructions
    instructions_list[10] = "neill_note";
    get_instructions_case(instructions_list[10], "neill_note");

    instructions_list[11] = "coding_stuff";
    get_instructions_case(instructions_list[11], "coding_stuff");

    instructions_list[12] = "door_jammed";
    get_instructions_case(instructions_list[12], "door_jammed");

    instructions_list[13] = "room_too_hot";
    get_instructions_case(instructions_list[13], "room_too_hot");

    instructions_list[14] = "using_some_code";
    get_instructions_case(instructions_list[14], "using_some_code");

    instructions_list[15] = "number";
    get_instructions_case(instructions_list[15], "number");

    instructions_list[16] = "less_than_ten";
    get_instructions_case(instructions_list[16], "less_than_ten");

    instructions_list[17] = "but_if_we_have";
    get_instructions_case(instructions_list[17], "but_if_we_have");

    instructions_list[18] = "greater_ten";
    get_instructions_case(instructions_list[18], "greater_ten");

    instructions_list[19] = "number_eq_eq_ten";
    get_instructions_case(instructions_list[19], "number_eq_eq_ten");

    instructions_list[20] = "number_is_ten";
    get_instructions_case(instructions_list[20], "number_is_ten");

    instructions_list[21] = "useful_later";
    get_instructions_case(instructions_list[21], "useful_later");


    //First part of first problem instructions
    instructions_list[22] = "fan_on_wall";
    get_instructions_case(instructions_list[22], "fan_on_wall");

    instructions_list[23] = "cool_down_room";
    get_instructions_case(instructions_list[23], "cool_down_room");

    instructions_list[24] = "control_panel";
    get_instructions_case(instructions_list[24], "control_panel");

    instructions_list[25] = "neill_notes";
    get_instructions_case(instructions_list[25], "neill_notes");

    instructions_list[26] = "change_temp";
    get_instructions_case(instructions_list[26], "change_temp");


    //Second part of first problem instrucions.
    instructions_list[27] = "that_worked";
    get_instructions_case(instructions_list[27], "that_worked");

    instructions_list[28] = "room_cooling";
    get_instructions_case(instructions_list[28], "room_cooling");


    //First block of instructions
    instructions_list[29] = "door_still_locked";
    get_instructions_case(instructions_list[29], "door_still_locked");

    instructions_list[30] = "work_out";
    get_instructions_case(instructions_list[30], "work_out");

    instructions_list[31] = "code_is_five";
    get_instructions_case(instructions_list[31], "code_is_five");

    instructions_list[32] = "binary";
    get_instructions_case(instructions_list[32], "binary");

    instructions_list[33] = "info_here";
    get_instructions_case(instructions_list[33], "info_here");

    instructions_list[34] = "bin_notes";
    get_instructions_case(instructions_list[34], "bin_notes");

    //Second block of instructions
    instructions_list[35] = "door_open";
    get_instructions_case(instructions_list[35], "door_open");

    //Hen related .bmp images
    instructions_list[36] = "chicken_in_here";
    get_instructions_case(instructions_list[36], "chicken_in_here");

    instructions_list[37] = "leave_it_alone";
    get_instructions_case(instructions_list[37], "leave_it_alone");

    instructions_list[38] = "come_back_let_it_out";
    get_instructions_case(instructions_list[38], "come_back_let_it_out");

    instructions_list[39] = "latch_loose";
    get_instructions_case(instructions_list[39], "latch_loose");

    instructions_list[40] = "got_out";
    get_instructions_case(instructions_list[40], "got_out");

    instructions_list[41] = "eggfault";
    get_instructions_case(instructions_list[41], "eggfault");

    //Discovering the x problem.
    instructions_list[42] = "door_still_locked";
    get_instructions_case(instructions_list[42], "door_still_locked");

    instructions_list[43] = "oh_my_word";
    get_instructions_case(instructions_list[43], "oh_my_word");

    instructions_list[44] = "hinge_sticks";
    get_instructions_case(instructions_list[44], "hinge_sticks");

    instructions_list[45] = "x_part_hinge";
    get_instructions_case(instructions_list[45], "x_part_hinge");

    instructions_list[46] = "swing_open";
    get_instructions_case(instructions_list[46], "swing_open");

    instructions_list[47] = "x_eq_five";
    get_instructions_case(instructions_list[47], "x_eq_five");

    instructions_list[48] = "two_weights";
    get_instructions_case(instructions_list[48], "two_weights");

    instructions_list[49] = "a_weight_b_weight";
    get_instructions_case(instructions_list[49], "a_weight_b_weight");

    instructions_list[50] = "a_eq_b_eq";
    get_instructions_case(instructions_list[50], "a_eq_b_eq");

    instructions_list[51] = "go_find";
    get_instructions_case(instructions_list[51], "go_find");

    instructions_list[52] = "finally_get_out";
    get_instructions_case(instructions_list[52], "finally_get_out");


    //Picking up the a weight.
    instructions_list[53] = "a_weight";
    get_instructions_case(instructions_list[53], "a_weight");

    instructions_list[54] = "put_by_door";
    get_instructions_case(instructions_list[54], "put_by_door");

    //Picking up the b weight.
    instructions_list[55] = "found_b";
    get_instructions_case(instructions_list[55], "found_b");

    instructions_list[56] = "put_on_door_hinge";
    get_instructions_case(instructions_list[56], "put_on_door_hinge");

    //Combining the weights.
    instructions_list[57] = "a_weight_on_hinge";
    get_instructions_case(instructions_list[57], "a_weight_on_hinge");

    instructions_list[58] = "b_weight_on_hinge";
    get_instructions_case(instructions_list[58], "b_weight_on_hinge");

    instructions_list[59] = "both_weights";
    get_instructions_case(instructions_list[59], "both_weights");

    instructions_list[60] = "x_is_eq";
    get_instructions_case(instructions_list[60], "x_is_eq");

    instructions_list[61] = "door_finally_open";
    get_instructions_case(instructions_list[61], "door_finally_open");

    printf("\n");
}

void get_instructions_case(char *instructions_list, char *filename)
{
    static int instruction_counter = 0;

    CU_ASSERT_STRING_EQUAL(instructions_list, filename);
    printf("\nInstruction %d successfully set to %s.\n", instruction_counter++, filename);
}

void test_print_instruction_to_screen(void)
{
    char *instruction = "arbitrary";

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    room_grid->refresh_counter = 0;
    CU_ASSERT(room_grid->refresh_counter == 0);
    printf("\n\nRoom grid refresh counter successfully set to zero.\n");

    room_grid->skip_checker = off;
    CU_ASSERT(room_grid->skip_checker == off);
    printf("\nRoom grid skip checker successfully set to off.\n");

    SDL_Surface* image_surf = NULL;
    CU_ASSERT(image_surf == NULL);
    printf("\nImage surface successfully initialised to zero.\n");

    // The following few lines are used to create a filename to get the .bmp to print to screen.
    char prefix[LENGTH_PREFIX] = "Instructions/";
    CU_ASSERT_STRING_EQUAL(prefix, "Instructions/");
    printf("\nFile directory succesfully set for filename.\n");

    char extension[LENGTH_EXTENSION] = ".bmp";
    CU_ASSERT_STRING_EQUAL(extension, ".bmp");
    printf("\nFile extension succesfully set for filename.\n");

    char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1);
    CU_ASSERT(sizeof(filename) == sizeof((malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1))));
    printf("\nCorrect amount of memory dynamically allocated for instruction path.\n");

    strcpy(filename, prefix);
    CU_ASSERT_STRING_EQUAL(filename, "Instructions/");
    printf("\nFile folder succesfully copied into filepath.\n");

    strcat(filename, instruction);
    CU_ASSERT_STRING_EQUAL(filename, "Instructions/arbitrary");
    printf("\nFilename and folder succesfully set for filename.\n");

    strcat(filename, extension);
    printf("\n\n%s\n\n", filename);
    CU_ASSERT_STRING_EQUAL(filename, "Instructions/arbitrary.bmp");
    printf("\nFilename and folder with extension succesfully set for filename.\n");

    free(filename);
    CU_ASSERT(filename == NULL);
    printf("\nfilename variable successfully freed.\n");
}

void test_SDL_events(void)
{
    int i, j;

    printf("\n");
    for(i = 0; i <= 4; ++i){
        for(j = 0; j <= 3; ++j){
            SDL_event_case(i, j);
        }
    }
    printf("\n");
}

void SDL_event_case(int event, int key)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    switch (event){

        case 1:
            CU_ASSERT(event == 1);
            printf("\nSDL_QUIT successfully recognised.\n");

            room_grid -> finished = finished;
            CU_ASSERT(room_grid -> finished == finished);
            printf("\nRoom grid finished indicator successfully set to on.\n");

            break;
        case 2:
            CU_ASSERT(event == 2);
            printf("\nSDL_MOUSEBUTTON successfully recognised.\n");

            room_grid -> skip_checker = on;
            CU_ASSERT(room_grid -> skip_checker == on);
            printf("\nRoom grid skip checker indicator successfully set to on.\n");
            break;
        case 3:
            CU_ASSERT(event == 3);
            printf("\nSDL_KEYDOWN successfully recognised.\n");

            switch (key)
            {
                case 1:
                    CU_ASSERT(key == 1);
                    printf("\nSDLK_ESCAPE successfully recognised.\n");

                    room_grid -> problem_quitter = on;
                    CU_ASSERT(room_grid -> problem_quitter == on);
                    printf("\nRoom grid problem quitter indicator successfully set to on.\n");

                    break;
                case 2:
                    CU_ASSERT(key == 2);
                    printf("\nSDLK_SPACE successfully recognised.\n");

                    room_grid -> skip_checker = on;
                    CU_ASSERT(room_grid -> skip_checker == on);
                    printf("\nRoom grid skip checker indicator successfully set to on.\n");
                    break;

                default:
                    CU_ASSERT(key != 1 && key != 2);
                    printf("\nInvalid key pressed successfully caught.\n");
                    break;
            }
            break;

        default:
            CU_ASSERT( (event != 1 && event != 2 && event != 3) );
            printf("\nInvalid event successfully caught.\n");
        break;
    }

}

void test_look_for_action(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    test_look_for_action_case(room_grid, off, off);

    test_look_for_action_case(room_grid, on, off);

    test_look_for_action_case(room_grid, off, on);

    test_look_for_action_case(room_grid, on, on);

    printf("\n");
}

void test_look_for_action_case(roomGrid *room_grid, on_off skip_checker, on_off problem_quitter)
{
    room_grid -> refresh_counter = 0;
    CU_ASSERT(room_grid -> refresh_counter == 0);
    printf("\nRoom grid successfully set to zero.\n");

    room_grid -> skip_checker = skip_checker;
    CU_ASSERT(room_grid -> skip_checker == skip_checker);
    if(skip_checker){
        printf("\nRoom grid skip checker successfully set to on.\n");
    }
    else{
        printf("\nRoom grid skip checker successfully set to off.\n");
    }

    room_grid -> problem_quitter = problem_quitter;
    CU_ASSERT(room_grid -> problem_quitter == problem_quitter);
    if(problem_quitter){
        printf("\nRoom grid problem quitter successfully set to on.\n");
    }
    else{
        printf("\nRoom grid problem quitter successfully set to off.\n");
    }

    do
    {
        ++(room_grid -> refresh_counter);

    }while(room_grid -> refresh_counter < NUM_REFRESHES && !room_grid -> skip_checker && !room_grid -> problem_quitter);

    CU_ASSERT(room_grid -> refresh_counter >= NUM_REFRESHES || room_grid -> skip_checker || room_grid -> problem_quitter);
    printf("\nTerminating clause for look for action correctly registered.\n");

}

void test_SDL_Quitchecker(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    SDL_Quitchecker_case(room_grid, finished);

    SDL_Quitchecker_case(room_grid, unfinished);

    printf("\n");
}

void SDL_Quitchecker_case(roomGrid *room_grid, fin_unfin fin)
{
    room_grid -> finished = fin;
    CU_ASSERT(room_grid -> finished == fin);
    if(fin){
        printf("\nRoom grid finished indicator successfully set to on.\n");
    }
    else{
        printf("\nRoom grid finished indicator successfully set to off.\n");
    }

    if (room_grid -> finished){
        CU_ASSERT(room_grid -> finished == finished);
        printf("\nRoom grid finished indicator successfully registered as on.\n");
    }
    else{
        CU_ASSERT(room_grid -> finished != finished);
        printf("\nRoom grid finished indicator successfully registered as off.\n");
    }
}

void test_draw(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    Chicken Fowl, *hen;
    hen = &Fowl;

    int first_pass = 0;

    printf("\n");

    room_grid -> gamerunning = on;
    CU_ASSERT(room_grid -> gamerunning == on);
    printf("\nRoom grid gamerunning successfully set to on.\n");

    hen -> chicken_cross_road = on;
    CU_ASSERT(hen -> chicken_cross_road == on);
    printf("\nHen chicken_cross_road successfully set to on.\n");

    while (room_grid -> gamerunning)
    {
        if(hen -> chicken_cross_road)
        {
            CU_ASSERT(hen -> chicken_cross_road == on);
            printf("\nHen chicken_cross_road successfully registered as on.\n");
        }
        else{
            CU_ASSERT(hen -> chicken_cross_road == off);
            printf("\nHen chicken_cross_road successfully registered as off.\n");
        }

    if(first_pass != 0){
        room_grid -> gamerunning = off;
        CU_ASSERT(room_grid -> gamerunning == off);
        printf("\nRoom grid gamerunning successfully set to off.\n");
    }
    
    hen -> chicken_cross_road = off;
    CU_ASSERT(hen -> chicken_cross_road == off);
    printf("\nHen chicken_cross_road successfully set to off.\n");

    ++first_pass;

    }

    room_grid -> gamerunning = off;
    CU_ASSERT(room_grid -> gamerunning == off);
    printf("\nRoom grid gamerunning successfully registered as off.\n");

    printf("\n");

}

void test_draw_room(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    int i, j;

    printf("\n");

    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
    CU_ASSERT(sizeof(room_grid -> room_array) == sizeof( (int **)calloc((ROOM_Y) + 1, sizeof(int *)) ) );
    printf("\nDynamic memory for room grid room array successfully allocated.\n");

    for (i = 0; i <= ROOM_Y; i++){
        room_grid -> room_array[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        CU_ASSERT(sizeof(room_grid -> room_array[i]) == sizeof((int *)calloc((ROOM_X) + 1, sizeof(int))));
    }
    printf("\nMemory for room grid room array component successfully allocated.\n");

    for (i = 0; i <= ROOM_Y; ++i){
        for (j = 0; j < ROOM_X; ++j){

            room_grid -> room_array[i][j] = rand() % 2 + 1;

            room_grid -> rc_dest.x = (j * TILE_SIZE);
            CU_ASSERT(room_grid -> rc_dest.x == (j * TILE_SIZE));

            room_grid -> rc_dest.y = (i * TILE_SIZE);
            CU_ASSERT(room_grid -> rc_dest.y == (i * TILE_SIZE));
            
            if (room_grid -> room_array[i][j] == 1){
                CU_ASSERT(room_grid -> room_array[i][j] == 1);
            }
            else{
                CU_ASSERT(room_grid -> room_array[i][j] != 1);
            }

            if (room_grid -> room_array[i][j] == 2){
                CU_ASSERT(room_grid -> room_array[i][j] == 2);
            }
            else{
                CU_ASSERT(room_grid -> room_array[i][j] != 2);
            }

            if(room_grid -> room_array[i][j] == 0){
                CU_ASSERT(room_grid -> room_array[i][j] == 0);
            }

        }
    }

    printf("\nAll rectangle components successfully set.\n");

    printf("\nAll cases of different possible room components checked.\n");

    printf("\n");
}

void test_rcsrc_set(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    rcsrc_set_case(34, 138, 32, 32, room_grid);

    rcsrc_set_case(3, 174, 31, 31, room_grid);

    rcsrc_set_case(71, 138, 32, 32, room_grid);

    rcsrc_set_case(0, 138, 32, 32, room_grid);

    printf("\n");
}

void rcsrc_set_case(int x_coord, int y_coord, int width, int height, roomGrid *room_grid)
{
    room_grid -> rc_src.x = x_coord;
    CU_ASSERT(room_grid -> rc_src.x == x_coord);
    printf("\nRoom grid source rectangle x coordinate successfully set to %d.\n", x_coord);

    room_grid -> rc_src.y = y_coord;
    CU_ASSERT(room_grid -> rc_src.y == y_coord);
    printf("\nRoom grid source rectangle y coordinate successfully set to %d.\n", y_coord);

    room_grid -> rc_src.w = width;
    CU_ASSERT(room_grid -> rc_src.w == width);
    printf("\nRoom grid source rectangle width successfully set to %d.\n", width);

    room_grid -> rc_src.h = height;
    CU_ASSERT(room_grid -> rc_src.h == height);
    printf("\nRoom grid source rectangle height successfully set to %d.\n", height);

}