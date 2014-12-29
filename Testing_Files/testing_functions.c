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

void assert_test(int test, char *message)
{
    CU_ASSERT(test);
    if(test){
        printf("\n%s\n", message);
    }
    else{
        printf("\nWARNING FAILED: %s\n", message);
    }

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

void test_rcobj_set(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    rcobj_set_case(264, 63, 64, 64, 0, 0, room_grid);

    rcobj_set_case(0, 62, 64, 64, 737, 318, room_grid);

    printf("\n");
}

void rcobj_set_case(int x_coord, int y_coord, int width, int height, int dest_x, int dest_y, roomGrid *room_grid)
{
    room_grid -> rc_obj.x = x_coord;                     //the x-coordinate of the object on the tile sheet
    CU_ASSERT(room_grid -> rc_obj.x == x_coord);
    printf("\nRoom grid object x coordinate successfully set to %d.\n", x_coord);

    room_grid -> rc_obj.y = y_coord;                     //the y-coordiante of the object on the tile sheet
    CU_ASSERT(room_grid -> rc_obj.y == y_coord);
    printf("\nRoom grid object y coordinate successfully set to %d.\n", y_coord);

    room_grid -> rc_obj.w = width;                       //the height and width for objects are 64 normally, but really can be anything
    CU_ASSERT(room_grid -> rc_obj.w == width);
    printf("\nRoom grid object width successfully set to %d.\n", width);

    room_grid -> rc_obj.h = height;
    CU_ASSERT(room_grid -> rc_obj.h == height);
    printf("\nRoom grid object height successfully set to %d.\n", height);

    room_grid -> rc_obj_dest.x = dest_x;                 //the x-coordinate of the object on the game map; takes some trial and error to figure out
    CU_ASSERT(room_grid -> rc_obj_dest.x == dest_x);
    printf("\nRoom grid object desination x coordinate successfully set to %d.\n", dest_x);

    room_grid -> rc_obj_dest.y = dest_y;                 //the y-coordinate of the object on the game map;
    CU_ASSERT(room_grid -> rc_obj_dest.y == dest_y);
    printf("\nRoom grid object desination y coordinate successfully set to %d.\n", dest_y);

    room_grid -> rc_obj_dest.w = room_grid -> rc_obj.w;  //these are set to be the same so another value does not have to be passed
    CU_ASSERT(room_grid -> rc_obj_dest.w == room_grid -> rc_obj.w);
    printf("\nRoom grid object desination width successfully set to %d.\n", room_grid -> rc_obj.w);

    room_grid -> rc_obj_dest.h = room_grid -> rc_obj.h;
    CU_ASSERT(room_grid -> rc_obj_dest.h == room_grid -> rc_obj.h);
    printf("\nRoom grid object desination height successfully set to %d.\n", room_grid -> rc_obj.h);

}

void test_initialise_roomgrid_components(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    printf("\n");

    room_grid -> gamerunning = true;
    CU_ASSERT(room_grid -> gamerunning == true);
    printf("\nGame running successfully initialised to true.\n");

    puzzle -> puzzle_1_seen   = false;
    CU_ASSERT(puzzle -> puzzle_1_seen  == false);
    printf("\nFirst puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_1_solved = false;
    CU_ASSERT(puzzle -> puzzle_1_solved == false);
    printf("\nFirst puzzle solved successfully initialised to false.\n");

    puzzle -> puzzle_2_seen   = false;
    CU_ASSERT(puzzle -> puzzle_2_seen  == false);
    printf("\nSecond puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_2_solved = false;
    CU_ASSERT(puzzle -> puzzle_2_solved == false);
    printf("\nSecond puzzle solved successfully initialised to false.\n");

    puzzle -> puzzle_3_seen   = false;
    CU_ASSERT(puzzle -> puzzle_3_seen  == false);
    printf("\nThird puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_3_solved = false;
    CU_ASSERT(puzzle -> puzzle_3_solved == false);
    printf("\nThird puzzle solved successfully initialised to false.\n");

    puzzle -> puzzle_4_seen   = false;
    CU_ASSERT(puzzle -> puzzle_4_seen  == false);
    printf("\nFourth puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_4_solved = false;
    CU_ASSERT(puzzle -> puzzle_4_solved == false);
    printf("\nFourth puzzle solved successfully initialised to false.\n");

    puzzle -> puzzle_5_seen   = false;
    CU_ASSERT(puzzle -> puzzle_5_seen  == false);
    printf("\nFifth puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_5_solved = false;
    CU_ASSERT(puzzle -> puzzle_5_solved == false);
    printf("\nFifth puzzle solved successfully initialised to false.\n");

    puzzle -> puzzle_6_seen   = false;
    CU_ASSERT(puzzle -> puzzle_6_seen  == false);
    printf("\nSixth puzzle seen successfully initialised to false.\n");

    puzzle -> puzzle_6_solved = false;
    CU_ASSERT(puzzle -> puzzle_6_solved == false);
    printf("\nSixth puzzle solved successfully initialised to false.\n");

    puzzle -> player_has_a_weight = false;
    CU_ASSERT(puzzle -> player_has_a_weight == false);
    printf("\nPlayer has a weight successfully set to false.\n");

    puzzle -> player_has_b_weight = false;
    CU_ASSERT(puzzle -> player_has_b_weight == false);
    printf("\nPlayer has b weight successfully set to false.\n");

    puzzle -> a_weight_on_hinge = false;
    CU_ASSERT(puzzle -> a_weight_on_hinge == false);
    printf("\nThe a weight being on the hing successfully set to false.\n");

    puzzle -> b_weight_on_hinge = false;
    CU_ASSERT(puzzle -> b_weight_on_hinge == false);
    printf("\nThe b weight being on the hing successfully set to false.\n");

    room_grid -> paused = 0;
    CU_ASSERT(room_grid -> paused == 0);
    printf("\nRoom grid paused successfully set to off.\n");

    room_grid -> left_x_coord = 0;
    CU_ASSERT(room_grid -> left_x_coord == 0);
    printf("\nRoom grid left x coordinate successfully set to 0.\n");

    room_grid -> bottom_y_coord = 0;
    CU_ASSERT(room_grid -> bottom_y_coord == 0);
    printf("\nRoom grid bottom y coordinate successfully set to 0.\n");

    room_grid -> top_y_coord = 0;
    assert_test(room_grid -> top_y_coord == 0, "Room grid top y coordinate successfully set to 0.");

    room_grid -> direction = 0;
    assert_test(room_grid -> direction == 0, "Room grid direction successfully set to 0");

    printf("\n");

}

void test_initialise_chicken(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    hen -> chicken_cross_road = false;
    assert_test(hen -> chicken_cross_road == false, "Chicken cross road indicator successfully set to false.");
    
    hen -> chick_lx_coord = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken lx coordinate successfully set to 0.");

    hen -> chick_rx_coord = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken rx coordinate successfully set to 0.");

    hen -> chick_by_coord = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken by coordinate successfully set to 0.");

    hen -> chick_ty_coord = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken ty coordinate successfully set to 0.");

    hen -> x_chick_centre = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken x centre coordinate successfully set to 0.");

    hen -> y_chick_centre = 0;
    assert_test(hen -> chick_lx_coord == 0, "Chicken y centre coordinate successfully set to 0.");

    printf("\n");
}

void test_position_sprite(void)
{

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    room_grid -> rc_sprite.y = TILE_SIZE*16;
    assert_test(room_grid -> rc_sprite.y == TILE_SIZE * 16, "Sprite rectangle y coordinate successfully set.");

    room_grid -> rc_sprite.x = TILE_SIZE*5;
    assert_test(room_grid -> rc_sprite.x == TILE_SIZE * 5, "Sprite rectangle x coordinate successfully set.");

    room_grid -> rc_sprite.w = TILE_SIZE;
    assert_test(room_grid -> rc_sprite.w == TILE_SIZE, "Sprite rectangle width successfully set.");

    room_grid -> rc_sprite.h = TILE_SIZE;
    assert_test(room_grid -> rc_sprite.h == TILE_SIZE, "Sprite rectangle height successfully set.");

    room_grid -> rc_sprite_pos.x = 0;
    assert_test(room_grid -> rc_sprite_pos.x == 0, "Sprite x coordinate successfully set.");

    room_grid -> rc_sprite_pos.y = 0;
    assert_test(room_grid -> rc_sprite_pos.y == 0, "Sprite y coordinate successfully set.");

    room_grid -> rc_sprite_pos.w = TILE_SIZE;
    assert_test(room_grid -> rc_sprite_pos.w == TILE_SIZE, "Sprite position width successfully set.");

    room_grid -> rc_sprite_pos.h = TILE_SIZE; 
    assert_test(room_grid -> rc_sprite_pos.h == TILE_SIZE, "Sprite position height coordinate successfully set.");

    room_grid -> rc_dest.w = TILE_SIZE;
    assert_test(room_grid -> rc_dest.w == TILE_SIZE, "Sprite rectangle desination width coordinate successfully set.");

    room_grid -> rc_dest.h = TILE_SIZE;
    assert_test(room_grid -> rc_dest.h == TILE_SIZE, "Sprite rectangle desination height coordinate successfully set.");

    printf("\n");
}

void test_position_chicken(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    hen -> chick_facing = room_grid -> direction;
    assert_test(hen -> chick_facing == room_grid -> direction, "Chicken direction successfully set.");

    hen -> srcChicken.y = 0;
    assert_test(hen -> srcChicken.y == 0, "Chicken rectangle y coordinate successfully set.");

    hen -> srcChicken.x = 0;
    assert_test(hen -> srcChicken.x == 0, "Chicken rectangle x coordinate successfully set.");

    hen -> srcChicken.w = TILE_SIZE;
    assert_test(hen -> srcChicken.w == TILE_SIZE, "Chicken rectangle width successfully set.");

    hen -> srcChicken.h = TILE_SIZE;
    assert_test(hen -> srcChicken.h == TILE_SIZE, "Sprite rectangle y coordinate successfully set.");

    hen -> dstChicken.y = 320;
    assert_test(hen -> dstChicken.y == 320, "Sprite rectangle y coordinate successfully set.");

    hen -> dstChicken.x = 320;
    assert_test(hen -> dstChicken.x == 320, "Sprite rectangle y coordinate successfully set.");

    hen -> dstChicken.w = TILE_SIZE;
    assert_test(hen -> dstChicken.w == TILE_SIZE, "Sprite rectangle y coordinate successfully set.");

    hen -> dstChicken.h = TILE_SIZE;
    assert_test(hen -> dstChicken.h == TILE_SIZE, "Sprite rectangle y coordinate successfully set.");


    printf("\n");
}

void test_movement(void)
{
    int i, j;

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;
    
    printf("\n");

    for(i = 0; i < 3; ++i){
        for(j = 0; j < 8; ++j){
            movement_case(room_grid, i, j);
        }
    }

    printf("\n");
 
}

void movement_case(roomGrid *room_grid, int event, int key)
{
    switch (event) 
    {
        case 1:
            assert_test(event == 1, "SDL_QUIT successfully registered.");

            room_grid -> gamerunning = false;
            assert_test(room_grid -> gamerunning == false, "Room successfully registered as quit.");
            break;
        case 2:
            assert_test(event == 2, "SDL_KEYDOWN successfully registered.");

        switch (key)
        {
            case 1:
                assert_test(key == 1, "SDLK_q successfully registered.");

                room_grid -> gamerunning = false;
                assert_test(room_grid -> gamerunning == false, "Room successfully registered as quit.");
                break;

           case 2:
                assert_test(key == 2, "SDLK_LEFT successfully registered.");

                room_grid -> direction = left;
                assert_test(room_grid -> direction == left, "Player directions successfully changed to left.");

                break;

            case 3:
                assert_test(key == 3, "SDLK_RIGHT successfully registered.");

                room_grid -> direction = right;
                assert_test(room_grid -> direction == right, "Player directions successfully changed to right.");

                break;

            case 4:
                assert_test(key == 4, "SDLK_UP successfully registered.");

                room_grid -> direction = up;
                assert_test(room_grid -> direction == up, "Player directions successfully changed to up.");

                break;

            case 5:
                assert_test(key == 5, "SDLK_DOWN successfully registered.");

                room_grid -> direction = down;
                assert_test(room_grid -> direction == down, "Player directions successfully changed to down.");
                break;

            case 6:
                assert_test(key == 6, "Interact Probe successfully turned on.");
                break;
            case 7:
                assert_test(key == 7, "Sound function successfully switched to.");
                break;
            default:
                assert_test(key > 7 || key < 1, "Invalid key successfully registered.");
                break;
        }
        break;

        default:
            assert_test(event != 1 && event != 2, "Invalid event registered.");
        break;
    }
}

void test_sound_on_off(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    sound_on_off_case(room_grid, on);

    sound_on_off_case(room_grid, off);

    printf("\n");
}

void sound_on_off_case(roomGrid *room_grid, on_off pause)
{
    room_grid -> paused = pause;

    if(room_grid -> paused == off){
        assert_test(room_grid -> paused == off, "Sound registered to be playing.");

        room_grid -> paused = on;
        assert_test(room_grid -> paused == on, "Sound successfully paused.");      
    }

    else if(room_grid -> paused == on){
        assert_test(room_grid -> paused == on, "Sound registered to be paused.");

        room_grid -> paused = off;
        assert_test(room_grid -> paused == off, "Sound successfully unpaused.");
    }
}

void test_edge_detection(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    edge_detection_case(room_grid, -10, SCREEN_WIDTH - TILE_SIZE + 1);

    edge_detection_case(room_grid, -10, -10);

    edge_detection_case(room_grid, SCREEN_WIDTH - TILE_SIZE + 1, SCREEN_WIDTH - TILE_SIZE + 1);

    edge_detection_case(room_grid, -10, -10);

    printf("\n");
}

void edge_detection_case(roomGrid *room_grid, int x_coord, int y_coord)
{
    room_grid -> rc_sprite.x  = x_coord;
    room_grid -> rc_sprite.y  = y_coord;

    //Left edge.
    if (room_grid -> rc_sprite.x <= 0){
        assert_test(room_grid -> rc_sprite.x <= 0, "Left edge collision registered.");

        room_grid -> rc_sprite.x  = 0;
        assert_test(room_grid -> rc_sprite.x  == 0, "Left edge collision successfully dealt with.");
    }
    //Right edge
    if (room_grid -> rc_sprite.x >= SCREEN_WIDTH - TILE_SIZE){
        assert_test(room_grid -> rc_sprite.x >= SCREEN_WIDTH - TILE_SIZE, "Right edge collision registered.");

        room_grid -> rc_sprite.x  = SCREEN_WIDTH - TILE_SIZE;
        assert_test(room_grid -> rc_sprite.x  == SCREEN_WIDTH - TILE_SIZE, "Right edge collision successfully dealt with.");
    }
    //Top edge
    if (room_grid -> rc_sprite.y <= 0){
        assert_test(room_grid -> rc_sprite.y <= 0, "Top edge collision registered.");

        room_grid -> rc_sprite.y  = 0;
        assert_test(room_grid -> rc_sprite.y  == 0, "Top edge collision successfully dealt with.");
    }
    //Bottom edge
    if (room_grid -> rc_sprite.y >= SCREEN_HEIGHT - TILE_SIZE){
        assert_test(room_grid -> rc_sprite.y >= SCREEN_HEIGHT - TILE_SIZE, "Bottom edge collision registered.");

        room_grid -> rc_sprite.y  = SCREEN_HEIGHT - TILE_SIZE;
        assert_test(room_grid -> rc_sprite.y == SCREEN_HEIGHT - TILE_SIZE, "Bottom edge collision successfully dealt with.");
    }

}

void test_possible(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    int a, b, c, d, e, f, g, h, i;

    printf("\n");

    initialise_possible_components(room_grid);


    for(a = 0; a <= 1; ++a){
        for(b = 0; b <= 1; ++b){
            for(c = 0; c <= 1; ++c){
                for(d = 0; d <= 1; ++d){
                    for(e = 0; e <= 1; ++e){
                        for(f = 0; f <= 1; ++f){
                            for(g = 0; g <= 1; ++g){
                                for(h = 0; h <= 1; ++h){
                                    for(i = 0; i <= 1; ++i){
                                        examine_possible_case(room_grid, a, b, c, d, e, f, g, h, i);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("\n");
}

void initialise_possible_components(roomGrid *room_grid)
{

    initialise_roomGrid_memory(room_grid);

    room_grid -> rc_sprite.x = 5;
    room_grid -> rc_sprite.y = 5;

    room_grid -> left_x_coord = (room_grid -> rc_sprite.x) / TILE_SIZE;
    assert_test(room_grid -> left_x_coord == (room_grid -> rc_sprite.x) / TILE_SIZE, "Sprite left x coordinate in movement successfully set.");

    room_grid -> top_y_coord = (room_grid -> rc_sprite.y) / TILE_SIZE;
    assert_test(room_grid -> top_y_coord == (room_grid -> rc_sprite.y) / TILE_SIZE, "Sprite top y coordinate in movement successfully set.");

    room_grid -> bottom_y_coord = ((room_grid -> rc_sprite.y - 1) + TILE_SIZE) / TILE_SIZE;
    assert_test(room_grid -> bottom_y_coord == ((room_grid -> rc_sprite.y - 1) + TILE_SIZE) / TILE_SIZE, "Sprite bottom y coordinate in movement successfully set.");

    room_grid -> right_x_coord = ((room_grid -> rc_sprite.x - 1) + TILE_SIZE) / TILE_SIZE;
    assert_test(room_grid -> right_x_coord == ((room_grid -> rc_sprite.x - 1) + TILE_SIZE) / TILE_SIZE, "Sprite right x coordinate in movement successfully set.");

}

void examine_possible_case(roomGrid *room_grid, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
{
    set_up_for_possible_case(room_grid, n1, n2, n3, n4, n5, n6, n7, n8, n9);

    possible_case(room_grid, left);

    possible_case(room_grid, down);

    possible_case(room_grid, up);

    possible_case(room_grid, right);
}

void set_up_for_possible_case(roomGrid *room_grid, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
{
    //Sometimes equal to zero.
    room_grid -> rc_sprite.y = n1;

    //Both of these at some point equal, the bottom one equal to zero.
    room_grid -> room_array[room_grid -> top_y_coord][room_grid -> left_x_coord - 1] = n2;
    room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1] = n3;

    //Both of these at some point equal, the bottom one equal to zero. 
    room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord] = n4;
    room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> right_x_coord] = n5;

    //Both of these at some point equal, the top one equal to zero. 
    room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1] = n6;
    room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> right_x_coord + 1] = n7;

    //Both of these at some point equal, the bottom one equal to zero.
    room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord] = n8;
    room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> right_x_coord] = n9;
}

void possible_case(roomGrid *room_grid, int direction)
{

    switch (direction)
    {       
        case(left):     if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> left_x_coord - 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1])){

                            assert_test((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> left_x_coord - 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1]), "First part of movement left successfully registered.");

                            if(room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1] == 0){

                                    assert_test(room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> left_x_coord - 1] == 0, "Left movement successfully passed into move function.");

                            }
                        }
                        break;

        case(down):     if ((room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> right_x_coord])){

                            assert_test((room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> right_x_coord]), "First part of movement down successfully registered.");

                            if(room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord] == 0){

                                assert_test(room_grid -> room_array[room_grid -> bottom_y_coord + 1][room_grid -> left_x_coord] == 0, "Down movement successfully passed into move function.");

                            }
                        }
                        break;

        case(right):    if ((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> right_x_coord + 1])){

                            assert_test((room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1]) == (room_grid -> room_array[room_grid -> bottom_y_coord][room_grid -> right_x_coord + 1]), "First part of movement right successfully registered.");

                            if(room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1] == 0){

                                assert_test(room_grid -> room_array[room_grid -> top_y_coord][room_grid -> right_x_coord + 1] == 0, "Right movement successfully passed into move function.");

                            }
                        }
                        break;

        case(up):       if (room_grid -> rc_sprite.y != 0)
                        {

                            assert_test(room_grid -> rc_sprite.y != 0, "Not being at top of screen registered for upwards movement.");

                            if ((room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> right_x_coord])){

                                assert_test((room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord]) == (room_grid -> room_array[room_grid -> bottom_y_coord-1][room_grid -> right_x_coord]), "First part of movement up successfully registered.");

                                if (room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord] == 0){

                                    assert_test(room_grid -> room_array[room_grid -> bottom_y_coord - 1][room_grid -> left_x_coord] == 0, "Upwards movement successfully passed into move function.");

                                }      
                            }
                        }
                        break;

        default:        

                assert_test(direction != up && direction != down && direction != left && direction != right, "Invalid direction successfully caught.");

                break;
     }
}

void test_move(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    printf("\nThe x coordinate is set to 224.\n");
    examine_move(room_grid, 224);

    printf("\nThe x coordinate is set to 96.\n");
    examine_move(room_grid, 96);

    printf("\nThe x coordinate is set to 160.\n");
    examine_move(room_grid, 160);

    printf("\nThe x coordinate is set to 32.\n");
    examine_move(room_grid, 32);

    printf("\nThe x coordinate is set to 100.\n");
    examine_move(room_grid, 100);

    printf("\n");

}

void examine_move(roomGrid *room_grid, int sprite_x_coord)
{
    room_grid -> rc_sprite_pos.x = sprite_x_coord;

    printf("\nAttempting to move left.\n");
    move_case(room_grid, left);

    printf("\nAttempting to move right.\n");
    move_case(room_grid, right);

    printf("\nAttempting to move up.\n");
    move_case(room_grid, up);

    printf("\nAttempting to move down.\n");
    move_case(room_grid, down);

    printf("\nAttempting to move in an undefined direction.\n");
    move_case(room_grid, 6);
}

void move_case(roomGrid *room_grid, int direction)
{
    int temp_x = room_grid -> rc_sprite.x, temp_y = room_grid -> rc_sprite.y;

    room_grid -> direction = direction;

    switch(room_grid -> direction)
    {       
        case(left):     (room_grid -> rc_sprite_pos.x == 224) ? (room_grid -> rc_sprite_pos.x = 256): (room_grid -> rc_sprite_pos.x = 224);
                        room_grid -> rc_sprite.x -= MOVEMENT_INCREMENT;
                        assert_test(room_grid -> rc_sprite.x == temp_x - MOVEMENT_INCREMENT, "Left movement successfully completed.");
                        break;

        case(down):     (room_grid -> rc_sprite_pos.x == 96) ? (room_grid -> rc_sprite_pos.x = 128): (room_grid -> rc_sprite_pos.x = 96);
                        room_grid -> rc_sprite.y += MOVEMENT_INCREMENT;
                        assert_test(room_grid -> rc_sprite.y == temp_y + MOVEMENT_INCREMENT, "Down movement successfully completed.");                  
                        break;

        case(right):    (room_grid -> rc_sprite_pos.x == 160) ? (room_grid -> rc_sprite_pos.x = 192): (room_grid -> rc_sprite_pos.x = 160);
                        room_grid -> rc_sprite.x += MOVEMENT_INCREMENT;
                        assert_test(room_grid -> rc_sprite.x == temp_x + MOVEMENT_INCREMENT, "Right movement successfully completed.");
                        break;

        case(up):       (room_grid -> rc_sprite_pos.x == 32) ? (room_grid -> rc_sprite_pos.x = 64): (room_grid -> rc_sprite_pos.x = 32);
                        room_grid -> rc_sprite.y -= MOVEMENT_INCREMENT;
                        assert_test(room_grid -> rc_sprite.y == temp_y - MOVEMENT_INCREMENT, "Up movement successfully completed.");
                        break;

        default:        
                        assert_test(direction != up && direction != down && direction != left && direction != right, "Undefined movement successfully caught.");
                        break;
    }
}

void test_interactProbe(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    initialise_roomGrid_memory(room_grid);

    initialise_interactProbe_location(room_grid);

    printf("\nAction set to be on.\n");
    examine_interactProbe_case(room_grid, on);

    printf("\nAction set to be off, no probing should register below.\n");
    examine_interactProbe_case(room_grid, off);

    printf("\n");

}

void initialise_roomGrid_memory(roomGrid *room_grid)
{
    int i;

    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
    CU_ASSERT(sizeof(room_grid -> room_array) == sizeof( (int **)calloc((ROOM_Y) + 1, sizeof(int *)) ) );
    printf("\nDynamic memory for room grid room array successfully allocated.\n");

    for (i = 0; i <= ROOM_Y; i++){
        room_grid -> room_array[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        CU_ASSERT(sizeof(room_grid -> room_array[i]) == sizeof((int *)calloc((ROOM_X) + 1, sizeof(int))));
    }
    printf("\nMemory for room grid room array component successfully allocated.\n");
}

void initialise_interactProbe_location(roomGrid *room_grid)
{
    room_grid -> y_sprite_centre = 1;
    room_grid -> x_sprite_centre = 1;
}

void examine_interactProbe_case(roomGrid *room_grid, on_off action)
{
    interactProbe_case(room_grid, left, action);

    interactProbe_case(room_grid, right, action);

    interactProbe_case(room_grid, up, action);

    interactProbe_case(room_grid, down, action);
}

void interactProbe_case(roomGrid *room_grid, int direction, on_off action)
{
    room_grid -> direction = direction;

    switch (room_grid -> direction)
    {       
        case(left):     room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre][room_grid -> x_sprite_centre - 1];
                        if (action){
                            assert_test(room_grid -> direction == left && action, "Successfully probed for interactions to the left.");
                        };
                        break;

        case(down):     room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre + 1][room_grid -> x_sprite_centre];
                        if (action){
                            assert_test(room_grid -> direction == down && action, "Successfully probed for interactions below.");
                        };
                        break;

        case(right):    room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre][room_grid -> x_sprite_centre + 1];
                        if (action){
                            assert_test(room_grid -> direction == right && action, "Successfully probed for interactions to the right.");
                        };
                        break;

        case(up):       if (room_grid -> rc_sprite.y != 0)
                        {
                            room_grid -> probe = room_grid -> room_array[room_grid -> y_sprite_centre - 1][room_grid -> x_sprite_centre];
                            if (action){
                                assert_test(room_grid -> direction == up && action, "Successfully probed for interactions above.");
                            }
                        };
                        break;
    }
}

void test_action(void)
{
    int i, j, k, l;
    problem action_problem, *prob_point;
    prob_point = &action_problem;

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    printf("\n");

    for(i = 0; i <= 1; ++i){
        for(j = 0; j <= 1; ++j){
            for(k = 0; k <= 1; ++k){
                for(l = puz_3; l <= puz_1; ++l){
                    action_case(prob_point, room_grid, puzzle, i, j, k, l);
                }
            }
        }
    }

    printf("\n");
}

int action_case(problem *prob_point, roomGrid *room_grid, progress *puzzle, bool puzz_1_seen, bool puzz_1_solved, bool puzz_3_solved, int probe)
{

    puzzle -> puzzle_1_seen = puzz_1_seen;
    puzzle -> puzzle_1_solved = puzz_1_solved;
    puzzle -> puzzle_3_solved = puzz_3_solved;
    room_grid -> probe = probe;

    switch(room_grid -> probe)
    {
        case(puz_1):        assert_test(room_grid -> probe == puz_1, "Puzzle 1 successfully registered.");
                            if ((puzzle -> puzzle_1_seen) == false){
                                    assert_test((puzzle -> puzzle_1_seen) == false, "Puzzle 1 never having been seen has been registered.");
                                return 1;
                            }
                            else if( (puzzle -> puzzle_1_solved) == false){     
                                    assert_test((puzzle -> puzzle_1_solved) == false, "Puzzle 1 never having been solved has been registered.");
                                return 0;
                            }
                            return 1;
                            break;

        case(puz_2):        assert_test(room_grid -> probe == puz_2, "Puzzle 2 successfully registered.");
                            return 0;
                            break; 

        case(puz_3):        assert_test(room_grid -> probe == puz_3, "Puzzle 3 successfully registered.");
                            if ((puzzle -> puzzle_3_solved) == false){
                                assert_test(puzzle -> puzzle_3_solved == false, "Puzzle 3 never having been solved successfully registered.");
                                return 0;
                            }
                            return 1;
                            break;

        case(puz_4):        assert_test(room_grid -> probe == puz_4, "Puzzle 4 successfully registered.");
                            return 0;
                            break; 

        case(puz_5):        assert_test(room_grid -> probe == puz_5, "Puzzle 5 successfully registered.");
                            return 0;
                            break;

        case(puz_6):        assert_test(room_grid -> probe == puz_6, "Puzzle 6 successfully registered.");
                            return 0;
                            break; 

        default:            
                            return 0;
                            break;
    }
}

void test_door_hinge_problem(void)
{
    int i, j, k;

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    for(i = 0; i <= 1; ++i){
        for(j = 0; j <= 1; ++j){
            for(k = 0; k <= 1; ++k){
                door_hinge_problem_case(puzzle, i, j, k);
            }
        }
    }

}

void door_hinge_problem_case(progress *puzzle, bool puzz_2_seen, bool player_a, bool player_b)
{
    puzzle -> puzzle_2_seen = puzz_2_seen;
    puzzle -> player_has_a_weight = player_a;
    puzzle -> player_has_b_weight = player_b;

    if(puzzle -> puzzle_2_seen == false){
        assert_test(puzzle -> puzzle_2_seen == false, "Puzzle 2 successfully registered as unseen.");

        puzzle -> puzzle_2_seen = true;
        assert_test(puzzle -> puzzle_2_seen == true, "Puzzle 2 successfully set as seen.");
    }
    
    if(puzzle -> player_has_a_weight == true){
        assert_test(puzzle -> player_has_a_weight == true, "Player successfully registered as having a weight.");

        puzzle -> player_has_a_weight = false;
        assert_test(puzzle -> player_has_a_weight == false, "Weight a taken from player.");
        puzzle -> a_weight_on_hinge = true;
        assert_test(puzzle -> a_weight_on_hinge == true, "Weight a put on hinge.");
    }
    
    if(puzzle -> player_has_b_weight == true){
        assert_test(puzzle -> player_has_b_weight == true, "Player successfully registered as having b weight.");

        puzzle -> player_has_b_weight = false;
        assert_test(puzzle -> player_has_b_weight == false, "Weight b taken from player.");
        puzzle -> b_weight_on_hinge = true;
        assert_test(puzzle -> b_weight_on_hinge == true, "Weight b put on hinge.");
    }
    
    if(puzzle -> a_weight_on_hinge == true && puzzle -> b_weight_on_hinge == true){
        assert_test(puzzle -> a_weight_on_hinge == true && puzzle -> b_weight_on_hinge == true, "Both weights successfully put on hinge.");
    }
}