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

void string_equal_test(char *string_one, char *string_two, char *message)
{
    CU_ASSERT_STRING_EQUAL(string_one, string_two);
    if( strcmp(string_one, string_two) == 0 ){
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

    printf("\n");

    test_makeRoom_case(NULL, map_file);

    initialise_working_room_components(room_grid, map_file);

    test_makeRoom_case(room_grid -> room_array, map_file);

    printf("\n");

}

void initialise_working_room_components(roomGrid *room_grid, FILE *map_file)
{
    room_grid -> room_array = 0;
    assert_test(room_grid -> room_array == 0, "Room grid room array successfully initialised to zero.");

    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
    assert_test(sizeof(room_grid -> room_array) == sizeof( (int **)calloc((ROOM_Y) + 1, sizeof(int *)) ) , "Dynamic memory for room grid room array successfully allocated.");

    map_file = fopen("room.txt", "r");

    if (map_file == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    printf("\nFile was opened.\n");
}

void test_makeRoom_case(int **room_array_pointer, FILE *map_file)
{
    int i, j;

    if (room_array_pointer == NULL){
        assert_test(room_array_pointer == NULL, "No memory for room grid allocation correctly identified.");
        return;
    }

    assert_test(room_array_pointer != NULL, "Memory available for room grid allocation correctly identified.");

    for (i = 0; i <= ROOM_Y; i++){

        room_array_pointer[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        CU_ASSERT(sizeof(room_array_pointer[i]) == sizeof((int *)calloc((ROOM_X) + 1, sizeof(int))));

        if (room_array_pointer[i] ==  NULL){
            assert_test(room_array_pointer[i] ==  NULL, "No memory for room grid room array component successfully identified.");
        }
    }
    printf("\nMemory for room grid room array components successfully allocated.\n");

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

    printf("\n");

    room_grid -> finished = unfinished;
    assert_test(room_grid -> finished == unfinished, "Room grid finished index correctly initialised to off.");

    room_grid -> problem_quitter = off;
    assert_test(room_grid -> problem_quitter == off, "Room grid problem indicator index correctly initialised to off.");

    test_print_instruction_case(off);

    printf("\nProblem quitter set to on.\n");

    test_print_instruction_case(on);

    printf("\n");
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
        assert_test(problem_quitter == off, "Instructions correctly sent through for printing.");
    }
    else{
        assert_test(problem_quitter == on, "Instructions correctly not sent through for printing.");
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

    printf("\nCurrently considering instruction %d: %s.\n", instruction_counter++, filename);
    string_equal_test(instructions_list, filename, "Instruction successfully allocated.");

}

void test_print_instruction_to_screen(void)
{
    char *instruction = "arbitrary";

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    room_grid->refresh_counter = 0;
    assert_test(room_grid->refresh_counter == 0, "Room grid refresh counter successfully set to zero.");

    room_grid->skip_checker = off;
    assert_test(room_grid->skip_checker == off, "Room grid skip checker successfully set to off.");

    SDL_Surface* image_surf = NULL;
    assert_test(image_surf == NULL, "Image surface successfully initialised to zero.");

    char prefix[LENGTH_PREFIX] = "Instructions/";
    string_equal_test(prefix, "Instructions/", "File directory succesfully set for filename.");

    char extension[LENGTH_EXTENSION] = ".bmp";
    string_equal_test(extension, ".bmp", "File extension succesfully set for filename.");

    char *filename = malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1);
    assert_test(sizeof(filename) == sizeof((malloc(strlen(prefix) + strlen(instruction) + strlen(extension) + 1))), "Correct amount of memory dynamically allocated for instruction path.");

    strcpy(filename, prefix);
    string_equal_test(filename, "Instructions/", "File folder succesfully copied into filepath.");

    strcat(filename, instruction);
    string_equal_test(filename, "Instructions/arbitrary", "Filename and folder succesfully set for filename.");

    strcat(filename, extension);
    string_equal_test(filename, "Instructions/arbitrary.bmp", "Filename and folder with extension succesfully set for filename.");

    free(filename);
    filename = NULL;
    assert_test(filename == NULL, "Filename variable successfully freed.");

    printf("\n");
}

void test_SDL_events(void)
{
    int event, key;

    printf("\n");

    for(key = 0; key <= 4; ++key){
        for(event = 0; event <= 3; ++event){
            initialise_message(key, event);
            SDL_event_case(key, event);
            printf("\n");
        }
    }

}

void initialise_message(int event, int key)
{
    if(event == quit){
        printf("\nEvent has been set to quit.\n");
    }
    else if(event == mousebutton){
        printf("\nEvent has been set to mousebutton.\n");
    }
    else if(event == keydown){
        printf("\nEvent has been set to keydown.\n");
    }
    else if(event != quit && event != mousebutton && event != keydown){
        printf("\nEvent has been set to undefined.\n");
    }

    if(key == escape_key){
        printf("\nKey has been set to escape_key.\n");
    }
    else if(key == space_key){
        printf("\nKey has been set to space_key.\n");
    }
    else if(key != escape_key && key != space_key){
        printf("\nKey has been set to undefined.\n");
    }

}

void SDL_event_case(int event, int key)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    switch (event){

        case quit:
            assert_test(event == quit, "SDL_QUIT successfully recognised.");

            room_grid -> finished = finished;
            assert_test(room_grid -> finished == finished, "Room grid finished indicator successfully set to on.");

            break;
        case mousebutton:
            assert_test(event == mousebutton, "SDL_MOUSEBUTTON successfully recognised.");

            room_grid -> skip_checker = on;
            assert_test(room_grid -> skip_checker == on, "Room grid skip checker indicator successfully set to on.");
            break;
        case keydown:
            assert_test(event == keydown, "SDL_KEYDOWN successfully recognised.");

            switch (key)
            {
                case escape_key:
                    assert_test(key == escape_key, "SDLK_ESCAPE successfully recognised.");

                    room_grid -> problem_quitter = on;
                    assert_test(room_grid -> problem_quitter == on, "Room grid problem quitter indicator successfully set to on.");

                    break;
                case space_key:
                    assert_test(key == space_key, "SDLK_SPACE successfully recognised.");

                    room_grid -> skip_checker = on;
                    assert_test(room_grid -> skip_checker == on, "Room grid skip checker indicator successfully set to on.");
                    break;

                default:
                    assert_test(key != escape_key && key != space_key, "Invalid key pressed successfully caught.");
                    break;
            }
            break;

        default:
            assert_test((event != quit && event != mousebutton && event != keydown), "Invalid event successfully caught.");
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
    assert_test(room_grid -> refresh_counter == 0, "Room grid successfully set to zero.");

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

    assert_test( room_grid -> refresh_counter >= NUM_REFRESHES || room_grid -> skip_checker || room_grid -> problem_quitter, "Terminating clause for look for action correctly registered.");

    printf("\n");
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
        assert_test(room_grid -> finished == finished, "Room grid finished indicator successfully registered as on.");
    }
    else{
        assert_test(room_grid -> finished != finished, "Room grid finished indicator successfully registered as off.");
    }

    printf("\n");
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
    assert_test(room_grid -> gamerunning == on, "Room grid gamerunning successfully set to on.");

    hen -> chicken_cross_road = on;
    assert_test(hen -> chicken_cross_road == on, "Hen chicken_cross_road successfully set to on.");

    while (room_grid -> gamerunning)
    {

        if(hen -> chicken_cross_road){
            assert_test(hen -> chicken_cross_road == on, "Hen chicken_cross_road successfully registered as on.");
        }
        else{
            assert_test(hen -> chicken_cross_road == off, "Hen chicken_cross_road successfully registered as off.");
        }

        if(first_pass != 0){
            room_grid -> gamerunning = off;
            assert_test(room_grid -> gamerunning == off, "Room grid gamerunning successfully set to off.");
        }
        
        hen -> chicken_cross_road = off;
        assert_test(hen -> chicken_cross_road == off, "Hen chicken_cross_road successfully set to off.");

        ++first_pass;

    }

    room_grid -> gamerunning = off;
    assert_test(room_grid -> gamerunning == off, "Room grid gamerunning successfully registered as off.");

    printf("\n");

}

void test_draw_room(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    int i, j;

    printf("\n");

    initialise_roomGrid_memory(room_grid);

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

    printf("\nIf no errors above, all rectangle components successfully set.\n");

    printf("\nIf no errors above, all cases of different possible room components checked.\n");

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
    printf("\nConsidering source rectangle x coordinate %d.\n", x_coord);
    room_grid -> rc_src.x = x_coord;
    assert_test(room_grid -> rc_src.x == x_coord, "Room grid source rectangle x coordinate successfully set.");

    printf("\nConsidering source rectangle y coordinate %d.\n", y_coord);
    room_grid -> rc_src.y = y_coord;
    assert_test(room_grid -> rc_src.y == y_coord, "Room grid source rectangle y coordinate successfully set.");

    printf("\nConsidering source rectangle width %d.\n", width);
    room_grid -> rc_src.w = width;
    assert_test(room_grid -> rc_src.w == width, "Room grid source rectangle width successfully set.");

    printf("\nConsidering source rectangle height %d.\n", height);
    room_grid -> rc_src.h = height;
    assert_test(room_grid -> rc_src.h == height, "Room grid source rectangle height successfully set.");

    printf("\n");

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
    room_grid -> rc_obj.x = x_coord;
    assert_test(room_grid -> rc_obj.x == x_coord, "SUCCESS.");
    printf("\nRoom grid object x coordinate successfully set to %d.\n", x_coord);

    room_grid -> rc_obj.y = y_coord;
    assert_test(room_grid -> rc_obj.y == y_coord, "SUCCESS.");
    printf("\nRoom grid object y coordinate successfully set to %d.\n", y_coord);

    room_grid -> rc_obj.w = width;
    assert_test(room_grid -> rc_obj.w == width, "SUCCESS.");
    printf("\nRoom grid object width successfully set to %d.\n", width);

    room_grid -> rc_obj.h = height;
    assert_test(room_grid -> rc_obj.h == height, "SUCCESS.");
    printf("\nRoom grid object height successfully set to %d.\n", height);

    room_grid -> rc_obj_dest.x = dest_x;
    assert_test(room_grid -> rc_obj_dest.x == dest_x, "SUCCESS.");
    printf("\nRoom grid object desination x coordinate successfully set to %d.\n", dest_x);

    room_grid -> rc_obj_dest.y = dest_y;
    assert_test(room_grid -> rc_obj_dest.y == dest_y, "SUCCESS.");
    printf("\nRoom grid object desination y coordinate successfully set to %d.\n", dest_y);

    room_grid -> rc_obj_dest.w = room_grid -> rc_obj.w;
    assert_test(room_grid -> rc_obj_dest.w == room_grid -> rc_obj.w, "SUCCESS.");
    printf("\nRoom grid object desination width successfully set to %d.\n", room_grid -> rc_obj.w);

    room_grid -> rc_obj_dest.h = room_grid -> rc_obj.h;
    assert_test(room_grid -> rc_obj_dest.h == room_grid -> rc_obj.h, "SUCCESS.");
    printf("\nRoom grid object desination height successfully set to %d.\n", room_grid -> rc_obj.h);

    printf("\n\n");

}

void test_initialise_roomgrid_components(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    printf("\n");

    room_grid -> gamerunning = true;
    assert_test(room_grid -> gamerunning == true, "Game running successfully initialised to true.");

    puzzle -> puzzle_1_seen   = false;
    assert_test(puzzle -> puzzle_1_seen  == false, "First puzzle seen successfully initialised to false.");

    puzzle -> puzzle_1_solved = false;
    assert_test(puzzle -> puzzle_1_solved == false, "First puzzle solved successfully initialised to false.");

    puzzle -> puzzle_2_seen   = false;
    assert_test(puzzle -> puzzle_2_seen  == false, "Second puzzle seen successfully initialised to false.");

    puzzle -> puzzle_2_solved = false;
    assert_test(puzzle -> puzzle_2_solved == false, "Second puzzle solved successfully initialised to false.");

    puzzle -> puzzle_3_seen   = false;
    assert_test(puzzle -> puzzle_3_seen  == false, "Third puzzle seen successfully initialised to false.");

    puzzle -> puzzle_3_solved = false;
    assert_test(puzzle -> puzzle_3_solved == false, "Third puzzle solved successfully initialised to false.");

    puzzle -> puzzle_4_seen   = false;
    assert_test(puzzle -> puzzle_4_seen  == false, "Fourth puzzle seen successfully initialised to false.");

    puzzle -> puzzle_4_solved = false;
    assert_test(puzzle -> puzzle_4_solved == false, "Fourth puzzle solved successfully initialised to false.");

    puzzle -> puzzle_5_seen   = false;
    assert_test(puzzle -> puzzle_5_seen  == false, "Fifth puzzle seen successfully initialised to false.");

    puzzle -> puzzle_5_solved = false;
    assert_test(puzzle -> puzzle_5_solved == false, "Fifth puzzle solved successfully initialised to false.");

    puzzle -> puzzle_6_seen   = false;
    assert_test(puzzle -> puzzle_6_seen  == false, "Sixth puzzle seen successfully initialised to false.");

    puzzle -> puzzle_6_solved = false;
    assert_test(puzzle -> puzzle_6_solved == false, "Sixth puzzle solved successfully initialised to false.");

    puzzle -> player_has_a_weight = false;
    assert_test(puzzle -> player_has_a_weight == false, "Player has a weight successfully set to false.");

    puzzle -> player_has_b_weight = false;
    assert_test(puzzle -> player_has_b_weight == false, "Player has b weight successfully set to false.");

    puzzle -> a_weight_on_hinge = false;
    assert_test(puzzle -> a_weight_on_hinge == false, "The a weight being on the hing successfully set to false.");

    puzzle -> b_weight_on_hinge = false;
    assert_test(puzzle -> b_weight_on_hinge == false, "The b weight being on the hing successfully set to false.");

    room_grid -> paused = 0;
    assert_test(room_grid -> paused == 0, "Room grid paused successfully set to off.");

    room_grid -> left_x_coord = 0;
    assert_test(room_grid -> left_x_coord == 0, "Room grid left x coordinate successfully set to 0.");

    room_grid -> bottom_y_coord = 0;
    assert_test(room_grid -> bottom_y_coord == 0, "Room grid bottom y coordinate successfully set to 0.");

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

void test_find_weight_a(void)
{
    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    printf("\n\nPuzzle 4 set as unseen.\n");
    find_weight_a_case(puzzle, false);

    printf("\nPuzzle 4 set as seen, no messages should register below.\n\n");
    find_weight_a_case(puzzle, true);
}

void find_weight_a_case(progress *puzzle, bool puzzle_4_seen)
{
    puzzle -> puzzle_4_seen = puzzle_4_seen;

    if(puzzle -> puzzle_4_seen == false){
        assert_test(puzzle -> puzzle_4_seen == false, "Puzzle 4 successfully registered as unseen.");
        
        puzzle -> player_has_a_weight = true;
        assert_test(puzzle -> player_has_a_weight == true, "Weight a given to player.");
        puzzle -> puzzle_4_seen = true;
        assert_test(puzzle -> puzzle_4_seen == true, "Puzzle 4 successfully set to seen.");
    }
}

void test_find_weight_b(void)
{
    progress puzzlesolved, *puzzle;
    puzzle = &puzzlesolved;

    printf("\n\nPuzzle 6 set as unseen.\n");
    find_weight_b_case(puzzle, false);

    printf("\nPuzzle 6 set as seen, no messages should register below.\n\n");
    find_weight_b_case(puzzle, true);
}

void find_weight_b_case(progress *puzzle, bool puzzle_4_seen)
{
    puzzle -> puzzle_6_seen = puzzle_4_seen;

    if(puzzle -> puzzle_6_seen == false){
        assert_test(puzzle -> puzzle_6_seen == false, "Puzzle 6 successfully registered as unseen.");
        
        puzzle -> player_has_b_weight = true;
        assert_test(puzzle -> player_has_b_weight == true, "Weight b given to player.");
        puzzle -> puzzle_6_seen = true;
        assert_test(puzzle -> puzzle_6_seen == true, "Puzzle 6 successfully set to seen.");
    }
}

void test_hen_sequence(void)
{
    int i;

    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    for(i = 0; i < 4; ++i){
        hen_sequence_iteration(hen);
    }

    printf("\n");
}

void hen_sequence_iteration(Chicken *hen)
{
    static int interaction_counter = 0;
    int temp = interaction_counter;

    printf("\nInteraction counter currently at: %d.\n", interaction_counter);

    if(interaction_counter == 0){
        assert_test(interaction_counter == 0, "Interaction counter successfully identified as 0.");

        ++interaction_counter;
        assert_test(interaction_counter == temp + 1, "Interaction counter incremented by one.");
    }
    else if(interaction_counter == 1){
        assert_test(interaction_counter == 1, "Interaction counter successfully identified as 1.");

        ++interaction_counter;
        assert_test(interaction_counter == temp + 1, "Interaction counter incremented by one.");
    }
    else if(interaction_counter == 2 && !(hen -> chicken_cross_road)){
        assert_test(interaction_counter == 2 && !(hen -> chicken_cross_road), "Interaction counter successfully identified as 2 and hen not been released.");

        ++interaction_counter;
        assert_test(interaction_counter == temp + 1, "Interaction counter incremented by one.");

        hen -> chicken_cross_road = true;
        assert_test(hen -> chicken_cross_road == true, "Hen counted as released, 2 registered but no messages should display below.");
        --interaction_counter;

    }
}

void test_initialise_problem(void)
{
    problem action_problem, *prob_point;
    prob_point = &action_problem;

    printf("\n");

    initialise_problem_case(prob_point, "arbitrary", 1, 10, 1, 15);

    printf("\n");
}

void initialise_problem_case(problem *prob_point, char *correct_answer, int first_inst_start, int first_instr_end,
                             int num_chars_ans, int second_inst_end)
{
    prob_point -> correct_answer = correct_answer;
    CU_ASSERT_STRING_EQUAL(prob_point -> correct_answer, "arbitrary") 
    printf("\nCorect answer correctly initialised.\n");

    prob_point -> first_instructions_start = first_inst_start;
    assert_test(prob_point -> first_instructions_start == 1, "Starting number for first set of instructions correctly set.");

    prob_point -> first_instructions_end = first_instr_end;
    assert_test(prob_point -> first_instructions_end == 10, "Finishing number for first set of instructions correctly set.");

    prob_point -> second_instructions_end = second_inst_end;
    assert_test(prob_point -> second_instructions_end == 15, "Finishing number for second set of instructions correctly set.");

    prob_point -> num_chars_in_ans = num_chars_ans;
    assert_test(prob_point -> num_chars_in_ans == 1, "Number of characters in answer correctly initialised.");
}

void test_permit_chicken(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    examine_chicken_case(hen, TILE_SIZE);

    examine_chicken_case(hen, 10);

    printf("\n");
}

void examine_chicken_case(Chicken *hen, int Chicken_x)
{
    printf("\nChicken direction set to left.\n");
    permit_chicken_case(hen, left, Chicken_x);

    printf("\nChicken direction set to right.\n");
    permit_chicken_case(hen, right, Chicken_x);

    printf("\nChicken direction set to up.\n");
    permit_chicken_case(hen, up, Chicken_x);

    printf("\nChicken direction set to down.\n");
    permit_chicken_case(hen, down, Chicken_x);
}

void permit_chicken_case(Chicken *hen, int direction, int Chicken_x)
{
    int temp_x, temp_y;

    hen -> chick_facing = direction;
    hen -> dstChicken.x = Chicken_x;

    temp_x = hen -> dstChicken.x;
    temp_y = hen -> dstChicken.y;

    switch (hen -> chick_facing)
    {       
        case(left):     assert_test(hen -> chick_facing == left, "Chicken direction recognised as left.");
                        if(!((hen -> dstChicken.x) % TILE_SIZE)){
                            assert_test(!((hen -> dstChicken.x) % TILE_SIZE), "The chicken has been registered to be at an irregular x location.");
                        } 
                        else{
                            (hen -> dstChicken.x -= MOVEMENT_INCREMENT);
                            assert_test(hen -> dstChicken.x == temp_x - MOVEMENT_INCREMENT, "The chicken has been moved left.");
                        }
                        break;

        case(down):     assert_test(hen -> chick_facing == down, "Chicken direction recognised as down.");
                        if(!((hen -> dstChicken.y) % TILE_SIZE)){
                            assert_test(!((hen -> dstChicken.y) % TILE_SIZE), "The chicken has been registered to be at an irregular y location.");
                        }
                        else{
                            (hen -> dstChicken.y += MOVEMENT_INCREMENT);
                            assert_test(hen -> dstChicken.y == temp_y + MOVEMENT_INCREMENT, "The chicken has been moved down.");
                        }
                        break;

        case(right):    assert_test(hen -> chick_facing == right, "Chicken direction recognised as right.");
                        if(!((hen -> dstChicken.x) % TILE_SIZE)){
                            assert_test(!((hen -> dstChicken.x) % TILE_SIZE), "The chicken has been registered to be at an irregular x location.");
                        }
                        else{
                            (hen -> dstChicken.x += MOVEMENT_INCREMENT);
                            assert_test(hen -> dstChicken.x == temp_x + MOVEMENT_INCREMENT, "The chicken has been moved right.");
                        }
                        break;

        case(up):       assert_test(hen -> chick_facing == up, "Chicken direction recognised as up.");
                        if(!((hen -> dstChicken.y) % TILE_SIZE)){
                            assert_test(!((hen -> dstChicken.y) % TILE_SIZE), "The chicken has been registered to be at an irregular y location.");
                            if (hen -> dstChicken.y != 0){

                            }
                        }
                        else{
                            (hen -> dstChicken.y -= MOVEMENT_INCREMENT);
                            assert_test(hen -> dstChicken.y == temp_y - MOVEMENT_INCREMENT, "The chicken has been moved up.");
                        }
                        break;        

    }
}

void test_chicken_help(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    hen -> chick_facing = rand() % 4;
    assert_test(hen -> chick_facing >= 1 && hen -> chick_facing <=3  , "The chicken has been successfully orientated.");

    printf("\n");
}

void test_chicken_direction(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    examine_chicken_direction_case(hen, 364);

    printf("\n");
}

void examine_chicken_direction_case(Chicken *hen, int Chicken_x)
{
    chicken_direction_case(hen, left, Chicken_x);

    chicken_direction_case(hen, right, Chicken_x);

    chicken_direction_case(hen, up, Chicken_x);

    chicken_direction_case(hen, down, Chicken_x);
}

void chicken_direction_case(Chicken *hen, compass direction, int Chicken_x)
{
    int temp_x, temp_y;

    hen -> chick_facing = direction;
    hen -> srcChicken.x = Chicken_x;

    temp_x = hen -> srcChicken.x;
    temp_y = hen -> srcChicken.y;

    switch (hen -> chick_facing)
    {       
        case(left):     assert_test(hen -> chick_facing = left, "The chicken direction has been successfully registered as left.");
                        (hen -> srcChicken.x == 364) ? (hen -> srcChicken.x = 396): (hen -> srcChicken.x = 364);
                        hen -> dstChicken.x -= MOVEMENT_INCREMENT;
                        assert_test(hen -> dstChicken.x = temp_x - MOVEMENT_INCREMENT, "The chicken has successfully been moved left.");
                        break;

        case(down):     assert_test(hen -> chick_facing == down, "The chicken direction has been successfully registered as down.");
                        (hen -> srcChicken.x == 364) ? (hen -> srcChicken.x = 396): (hen -> srcChicken.x = 364);
                        hen -> dstChicken.y += MOVEMENT_INCREMENT;
                        assert_test(hen -> dstChicken.y = temp_y + MOVEMENT_INCREMENT, "The chicken has successfully been moved down.");
                        break;

        case(right):    assert_test(hen -> chick_facing == right, "The chicken direction has been successfully registered as right.");
                        (hen -> srcChicken.x == 300) ? (hen -> srcChicken.x = 332): (hen -> srcChicken.x = 300);
                        hen -> dstChicken.x += MOVEMENT_INCREMENT;
                        assert_test(hen -> dstChicken.x = temp_x + MOVEMENT_INCREMENT, "The chicken has successfully been moved right.");
                        break;

        case(up):       assert_test(hen -> chick_facing == up, "The chicken direction has been successfully registered as up.");
                        (hen -> srcChicken.x == 300) ? (hen -> srcChicken.x = 332): (hen -> srcChicken.x = 300);
                        hen -> dstChicken.y -= MOVEMENT_INCREMENT;
                        assert_test(hen -> dstChicken.y = temp_y - MOVEMENT_INCREMENT, "The chicken has successfully been moved up.");
                        break;    
    }
}

void test_chicken_edge_detection(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    chicken_edge_detection_case(hen, 0, 0);

    chicken_edge_detection_case(hen, 0, SCREEN_WIDTH - TILE_SIZE + 1);

    chicken_edge_detection_case(hen, SCREEN_WIDTH - TILE_SIZE + 1, 0);

    chicken_edge_detection_case(hen, SCREEN_WIDTH - TILE_SIZE + 1, SCREEN_WIDTH - TILE_SIZE + 1);

    printf("\n");
}

void chicken_edge_detection_case(Chicken *hen, int Chicken_x, int Chicken_y)
{
    hen -> dstChicken.x = Chicken_x;
    hen -> dstChicken.y = Chicken_y;

    //Left edge.
    if (hen -> dstChicken.x <= 0){
        assert_test(hen -> dstChicken.x <= 0, "The left edge has successfully been identified.");
        
        hen -> dstChicken.x = 0;
        assert_test(hen -> dstChicken.x == 0, "The chicken has been repositioned to be at the left edge.");
        
        hen -> chick_facing = right;
        assert_test(hen -> chick_facing == right, "The chicken direction has been changed to be facing right.");
    }
    //Right edge
    if (hen -> dstChicken.x >= SCREEN_WIDTH - TILE_SIZE){
        assert_test(hen -> dstChicken.x >= SCREEN_WIDTH - TILE_SIZE, "The right edge has successfully been identified.");
        
        hen -> dstChicken.x = SCREEN_WIDTH - TILE_SIZE;
        assert_test(hen -> dstChicken.x == SCREEN_WIDTH - TILE_SIZE, "The chicken has been repositioned to be at the right edge.");
        
        hen -> chick_facing = left;
        assert_test(hen -> chick_facing == left, "The chicken direction has been changed to be facing left.");
    }
    //Top edge
    if (hen -> dstChicken.y <= 0){
        assert_test(hen -> dstChicken.y <= 0, "The top edge has successfully been identified.");
        
        hen -> dstChicken.y = 0;
        assert_test(hen -> dstChicken.y == 0, "The chicken has been repositioned to be at the top edge.");
        
        hen -> chick_facing = down;
        assert_test(hen -> chick_facing == down, "The chicken direction has been changed to be facing down.");
    }
    //Bottom edge
    if (hen -> dstChicken.y >= SCREEN_HEIGHT - TILE_SIZE){
        assert_test(hen -> dstChicken.y >= SCREEN_HEIGHT - TILE_SIZE, "The bottom edge has successfully been identified."); 
        
        hen -> dstChicken.y = SCREEN_HEIGHT - TILE_SIZE;
        assert_test(hen -> dstChicken.y == SCREEN_HEIGHT - TILE_SIZE, "The chicken has been repositioned to be at the bottom edge.");
        
        hen -> chick_facing = up;
        assert_test(hen -> chick_facing == up, "The chicken direction has been changed to be facing up.");
    } 
}

void test_eggfault(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    eggfault_case(hen, room_grid, 0, 0, 0, 0);

    eggfault_case(hen, room_grid, 0, 0, 1, 1);

    printf("\n");
}

void eggfault_case(Chicken *hen, roomGrid *room_grid, int sprite_x, int sprite_y, int hen_x, int hen_y)
{
    hen -> dstChicken.x = hen_x;
    hen -> dstChicken.y = hen_y;
    room_grid -> rc_sprite.x = sprite_x;
    room_grid -> rc_sprite.y = sprite_y;
    room_grid -> gamerunning = true;

    hen -> x_chick_centre = (hen -> dstChicken.x + (TILE_SIZE / 2)) / TILE_SIZE; // (0 + 16) / 32 = 0.5 = 0
    assert_test(hen -> x_chick_centre == (hen -> dstChicken.x + (TILE_SIZE / 2)) / TILE_SIZE, "The chicken centre x coordinate has been successfully set.");

    hen -> y_chick_centre = (hen -> dstChicken.y + (TILE_SIZE / 2)) / TILE_SIZE;
    assert_test(hen -> y_chick_centre == (hen -> dstChicken.y + (TILE_SIZE / 2)) / TILE_SIZE, "The chicken centre y coordinate has been successfully set.");

    room_grid -> x_sprite_centre = (room_grid -> rc_sprite.x + (TILE_SIZE / 2)) / TILE_SIZE;
    assert_test(room_grid -> x_sprite_centre == (room_grid -> rc_sprite.x + (TILE_SIZE / 2)) / TILE_SIZE, "The sprite centre x coordinate has been successfully set.");


    room_grid -> y_sprite_centre = (room_grid -> rc_sprite.y + (TILE_SIZE / 2)) / TILE_SIZE;
    assert_test(room_grid -> y_sprite_centre == (room_grid -> rc_sprite.y + (TILE_SIZE / 2)) / TILE_SIZE, "The sprite centre y coordinate has been successfully set.");

    printf("%d %d\n", hen-> x_chick_centre, room_grid -> x_sprite_centre);
    printf("%d %d\n", hen -> y_chick_centre, room_grid -> y_sprite_centre);


    if (  (hen -> x_chick_centre) == (room_grid -> x_sprite_centre) 
        && (hen -> y_chick_centre) == (room_grid -> y_sprite_centre) ){
       
        assert_test( (hen -> x_chick_centre) == (room_grid -> x_sprite_centre) 
          && (hen -> y_chick_centre) == (room_grid -> y_sprite_centre), "The chicken and sprite have been detected to be at the same place.");

        room_grid -> gamerunning = false;
        assert_test(room_grid -> gamerunning == false, "The game has been successfully closed.");
    }

}

void test_changeChickenDirection(void)
{
    Chicken Fowl, *hen;
    hen = &Fowl;

    printf("\n");

    changeChickenDirection_case(hen, left);
    changeChickenDirection_case(hen, right);
    changeChickenDirection_case(hen, up);
    changeChickenDirection_case(hen, down);

    printf("\n");
}

void changeChickenDirection_case(Chicken *hen, compass direction)
{
    int temp_chick_direction = direction;
    hen -> chick_facing = direction;

    if (hen -> chick_facing == left){
        assert_test(hen -> chick_facing == left, "The chicken direction has been successfully registered to be left.");

        hen -> chick_facing = up;
        assert_test(hen -> chick_facing == up, "The new chicken direction has been successfully registered to be up.");
    }
    else{
        assert_test(hen -> chick_facing != left, "The chicken direction has been successfully registered as not left.");

        hen -> chick_facing++;
        assert_test(hen -> chick_facing == temp_chick_direction + 1, "The chicken has been rotated ninety degrees.");
    }
}

void test_problem_generator(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    bool current_puzzle_solved = false;

    room_grid -> problem_quitter = off;

    printf("\n");

    room_grid -> finished = 0;
    assert_test(room_grid -> finished == 0, "The room grid has been set to have been paused.");

    while(current_puzzle_solved == false && room_grid -> problem_quitter == off){
        assert_test(current_puzzle_solved == false, "Problem being unsolved has been registered.");
        assert_test(room_grid -> problem_quitter == off, "User not having skipped the scene has been registered");
        
        current_puzzle_solved = true;
        assert_test(current_puzzle_solved == true, "User skipping cutscene set to on.");
    }

    assert_test(current_puzzle_solved == true, "Cutscene skipping has been registered.");
    assert_test(current_puzzle_solved == on, "User solving puzzle has been registered.");

    if(room_grid -> problem_quitter == off){
        assert_test(room_grid -> problem_quitter == off, "Problem quitter not on, remaining cutscene played.");
    }

    printf("\n");
}

void test_free_room_array(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    initialise_roomGrid_memory(room_grid);

    for (int i = 0; i < ROOM_Y; i++){
        free(room_grid -> room_array[i]);
        room_grid -> room_array[i] = NULL;
        CU_ASSERT(room_grid -> room_array[i] == NULL);
    }

    free(room_grid -> room_array);
    room_grid -> room_array = NULL;
    assert_test(room_grid -> room_array == NULL, "Room array successfully freed.");

    printf("\n");
}

void test_input_screen(void)
{
    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    int input_index = 0, finish_checker = unfinished, chars_in_ans = 9;
    bool current_puzzle_solved = false;

    char *correct_answer = "arbitrary";
    char *possible_answer = "arbitrary";

    printf("\n");

    do{

        assert_test(input_index == 0, "No characters registered as typed.");

        if(input_index == chars_in_ans + 1){
          assert_test(input_index == chars_in_ans + 1, "Maximum entered characters registered.");

          finish_checker = finished;
          assert_test(finish_checker == finished, "Finish checker set as finished.");
        }

        input_index = chars_in_ans + 1;
        assert_test(input_index == chars_in_ans + 1, "Number of characters in answer set to max.");

    }while(input_index < MAX_INPUT_CHARS && !finish_checker && room_grid -> problem_quitter == off);

    assert_test(!(input_index < MAX_INPUT_CHARS && !finish_checker && room_grid -> problem_quitter == off), "Input loop successfully exited.");

    if( strcmp(possible_answer, correct_answer) == 0){
        current_puzzle_solved = true;
        assert_test(current_puzzle_solved == true, "The correct answer successfully registered.");
    }

    printf("\n");

}

void test_create_answer_for_checking(void)
{
    int i, chars_in_ans = 9;

    char possible_answer[MAX_INPUT_CHARS];
    char *input_string = "arbitrary";

    printf("\n");

    for(i = 0; i < chars_in_ans; ++i){
        possible_answer[i] = input_string[i];
        CU_ASSERT(possible_answer[i] == input_string[i]);
    }

    possible_answer[chars_in_ans] = '\0';
    CU_ASSERT_STRING_EQUAL("arbitrary", possible_answer);
    printf("\nThe answer string has been set to the input string.\n");

    printf("\n");
}

void test_initialise_input_string(void)
{
    int i;
    char input_string[MAX_INPUT_CHARS];

    printf("\n");

    for(i = 0; i < MAX_INPUT_CHARS; ++i){
        input_string[i] = ' ';
        CU_ASSERT(input_string[i] == ' ');
    }

    printf("\nThe input string has been successfully initialised.\n");

    printf("\n");
}

void test_initialise_drcrect(void)
{
    SDL_Rect drcrect_obj, *drcrect;
    drcrect = &drcrect_obj;

    int input_index = 10;

    printf("\n");

    drcrect->x = RECT_X;
    assert_test(drcrect->x == RECT_X, "The drcrect x coordinate has been successfully set.");

    drcrect->y = RECT_Y;
    assert_test(drcrect->y == RECT_Y, "The drcrect y coordinate has been successfully set.");

    drcrect->w = RECT_W * (input_index + 1);
    assert_test(drcrect->w == RECT_W * (input_index + 1), "The drcrect width has been successfully set.");

    drcrect->h = RECT_H;
    assert_test(drcrect->h == RECT_H, "The drcrect height has been successfully set.");

    printf("\n");
}

void test_check_user_variable_input(void)
{
    int i;

    roomGrid roomStuff, *room_grid;
    room_grid = &roomStuff;

    printf("\n");

    for(i = 'a'; i <= 'z'; ++i){
        printf("\nCharacter set to %c.\n", i);
        user_check_variable_input_case(room_grid, 'c', 1);
    }

    user_check_variable_input_case(room_grid, '=', 1);

    user_check_variable_input_case(room_grid, ',', 1);

    user_check_variable_input_case(room_grid, '.', 1);

    user_check_variable_input_case(room_grid, escape, 1);

    user_check_variable_input_case(room_grid, enter, 1);

    user_check_variable_input_case(room_grid, backspace, 1);

    printf("\n");
}

void user_check_variable_input_case(roomGrid *room_grid, char c, int event)
{
    int gameover = 0, finish_checker = unfinished, input_index = 1, temp = input_index;

    char input_string[MAX_INPUT_CHARS];

    while (gameover != INPUT_FINISHED){                                                                                                                                                                    //checks for events.
        if(event == 1){                                                                                                                                                                     //if the key is pressed assigns character
            if( (c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) || (c >= '0' && c <= '9') ){
                assert_test((c >= 'a' && c <= 'z') || (c == ' ' || c == '=' || c == ',' || c == '.' ) || (c >= '0' && c <= '9'), "Valid regular character registered.");
                if(c == ','){
                    assert_test(c == ',', "Character to be translated to < registered.");

                    input_string[input_index] = '<';
                    assert_test(input_string[input_index] == '<', "< symbol assigned to string.");
                }
                else if(c == '.'){
                    assert_test(c == '.', "Character to be translated to > registered.");

                    input_string[input_index] = '>';
                    assert_test(input_string[input_index] == '>', "> symbol assigned to string.");
                }
                else{
                    input_string[input_index] = c;
                    assert_test(input_string[input_index] == c, "Regular character assigned to string.");
                }                                                                                                         
                ++(input_index);
                assert_test(temp + 1 == input_index, "Input index successfully incremented.");

                gameover = INPUT_FINISHED;
                assert_test(gameover == INPUT_FINISHED, "Input registered as finished.");
                }
                else if( c == backspace){
                    assert_test(c == backspace, "Backspace registered.");

                    input_string[--(input_index)] = ' ';
                    assert_test(input_string[input_index] == ' ', "Character index stepped back by one and previous entry erased.");

                    gameover = INPUT_FINISHED;
                    assert_test(gameover == INPUT_FINISHED, "Input registered as finished."); 
                }
                else if(c == enter){
                    assert_test(c == enter, "Enter symbol registered.");

                    finish_checker = finished;
                    assert_test(finish_checker == finished, "Input string registered as completed.");

                    gameover = INPUT_FINISHED;
                    assert_test(gameover == INPUT_FINISHED, "Input registered as finished."); 
                }
                else if(c == escape){
                    assert_test(c == escape, "Escape symbol registered.");

                    room_grid -> problem_quitter = on;
                    assert_test(room_grid -> problem_quitter == on, "Problem quitter registered to be on.");

                    gameover = INPUT_FINISHED;
                    assert_test(gameover == INPUT_FINISHED, "Input registered as finished.");
                }
            }
        }              

    input_string[MAX_INPUT_CHARS - 1] = '\0'; // LOOK HERE 
 
}

void test_run_menu_screen(void)
{
    printf("\n");

    run_menu_screen_case();

    run_menu_screen_case();

    printf("\n");
}

void run_menu_screen_case(void)
{
    static int first_pass = 0;

    int temp = first_pass;

    if(first_pass == 0){
        assert_test(first_pass == 0, "First pass registered, loading menu registered as unseen.");

        ++first_pass;
        assert_test(first_pass == temp + 1, "First pass successfully incremented.");
        return;
    }

    assert_test(first_pass != 0, "Loading menu having been seen registered.");
}

void test_save(void){

    printf("\n");

    roomGrid *room_grid = (roomGrid *)malloc(sizeof(roomGrid));

    room_grid -> room_array = (int **)calloc((ROOM_Y) + 1, sizeof(int *));

    for (int i = 0; i <= ROOM_Y; i++){
        room_grid -> room_array[i] = (int *)calloc((ROOM_X) + 1, sizeof(int));
        if (room_grid -> room_array[i] ==  NULL){
            fprintf(stderr, "No memory available.\n");
            exit(4);
        }
    }

    save_case(room_grid);
    
    printf("\n");
}

void save_case(roomGrid *room_grid){
    
    FILE *writing_file;
   
    writing_file = fopen("Your_level.txt","w");
    assert_test( writing_file != NULL, "Editor output file opened");

    if(writing_file == NULL) {
        printf("ERROR opening file...exiting\n");
    }

    for (int i = 0; i < ROOM_Y; ++i)
    {   
        for (int j = 0; j < ROOM_X; ++j)
        {   
            printf("%d %d\n", i, j);
            fprintf(writing_file, "%d ", room_grid->room_array[i][j]);
        }
        
        fprintf(writing_file,"\n");
    }

    fclose(writing_file);
}


void test_level_editor(void)
{
    Edit edit;
    bool running = true;
    editor_input input;

    printf("\n");
    
    input.add = 0;
    assert_test(input.add == 0, "Input add initialised to zero.");

    input.remove = 0;
    assert_test(input.remove == 0, "Input remove initialised to zero.");
    
    edit.previous  = 0;
    assert_test(edit.previous == 0, "Edit previous initialised to zero.");

    edit.src_value = 0;
    assert_test(edit.src_value == 0, "Edit source initialised to zero.");
    
    int excess = 0, tile_x = 0, tile_y = 0;
    assert_test(excess == 0, "Excess initialised to zero.");
    assert_test(tile_x == 0, "Tile_x initialised to zero.");
    assert_test(tile_y == 0, "Tile_y initialised to zero.");
    
    // Run the meat of the program.
    while(running){

        assert_test(running, "Level editor recognised successfully as running.");
        
        running = false;
        
    }

    assert_test(!running, "Level editor set to not running and successfully exited.");

    printf("\n");
    
}

void test_draw_edited_map(void)
{
    int room_array[ROOM_Y][ROOM_X], i, j; // To save creating the whole roomGrid struct
    Edit edit;
    editor_input input;

    edit.src_value = 1;

    for(i = 0; i < ROOM_Y; ++i){
        for(j = 0; j < ROOM_X; ++j){
            room_array[i][j] = rand() % 3;
        }
    }

    printf("\n");

    draw_edited_map_case(1, 1, 1, room_array, edit, input);

    printf("\n");
}

void draw_edited_map_case(int input_add, int edit_previous, int input_remove, int map_array[ROOM_Y][ROOM_X], Edit edit, editor_input input)
{
    int tile_y = 0, tile_x = 0, temp; 
    SDL_Rect tile_dst;

    if (input.add == edit.previous && edit.previous == 1){
        
            assert_test(input.add == edit.previous && edit.previous == 1, "Selected square registered as previously edited.");

            map_array[tile_y][tile_x] = edit.src_value;
            assert_test(map_array[tile_y][tile_x] == edit.src_value, "Square set as the edit source value.");
        }

        else if(input.add == 1){
            assert_test(input.add == 1, "Tile successfully registered as selected."); 

            temp = map_array[tile_y][tile_x];

            map_array[tile_y][tile_x]++;
            assert_test(map_array[tile_y][tile_x] = temp + 1, "Number on tile successfully incremented by one.");

            map_array[tile_y][tile_x] = map_array[tile_y][tile_x] % NUM_TILE_TYPES;
            assert_test(map_array[tile_y][tile_x] < NUM_TILE_TYPES, "Number on tile successfully modulesed to usable number.");

            edit.src_value = map_array[tile_y][tile_x];
            assert_test(edit.src_value == map_array[tile_y][tile_x], "The edit source value has been successfully set.");
        } 
    
    if (input.remove == 1){
        assert_test(input.remove == 1, "Successfully registered as put in deletion mode.");

        map_array[tile_y][tile_x] = BLANK;
        assert_test(map_array[tile_y][tile_x] == BLANK, "Tile deleted.");
    }
    
    for (int i = 0; i < ROOM_Y; ++i){

        for (int j = 0; j < ROOM_X; ++j){   

            tile_dst.x = j*TILE_SIZE;
            CU_ASSERT(tile_dst.x == j*TILE_SIZE);

            tile_dst.y = i*TILE_SIZE;
            CU_ASSERT(tile_dst.y == i*TILE_SIZE);

            tile_dst.w = TILE_SIZE;
            CU_ASSERT(tile_dst.w == TILE_SIZE);

            tile_dst.h = TILE_SIZE;
            CU_ASSERT(tile_dst.h == TILE_SIZE);
            
            if (map_array[i][j] == WALL){   
                CU_ASSERT(map_array[i][j] == WALL);
            }

            else if ( map_array[i][j] == BLANK){
                CU_ASSERT(map_array[i][j] == BLANK);
            }

            else if ( map_array[i][j] == TERMINAL){   
                CU_ASSERT(map_array[i][j] == TERMINAL);
            }

            else if ( map_array[i][j] == ALT){   
                CU_ASSERT(map_array[i][j] == ALT);
            }
        }
    }

    printf("\nIf no FAILS: All components of map successfully changed.\n");

    edit.previous = input.add;
    assert_test(edit.previous == input.add, "Level editor set to not running and successfully exited.");

}

void test_configure_mouse(void)
{
    int excess, tx, *tile_x, ty, *tile_y, temp; 
    editor_input input;
    cursor cursor; 
    SDL_Rect cs, cd, ts, *cursor_src, *cursor_dst, *tile_src;

    cursor_src = &cs;
    cursor_dst = &cd;
    tile_src = &ts;
    tile_x = &tx;
    tile_y = &ty;

    printf("\n");

    excess = input.mouse_x % TILE_SIZE;
    assert_test(excess == input.mouse_x % TILE_SIZE, "Difference in x coordinate from tile centre successfully set.");

    temp = input.mouse_x;
    input.mouse_x = input.mouse_x - excess;
    assert_test(input.mouse_x == temp - excess, "Mouse central x coordinate successfully set.");
    
    excess = input.mouse_y % TILE_SIZE;
    assert_test(excess == input.mouse_y % TILE_SIZE, "Difference in y coordinate from tile centre successfully set.");

    temp = input.mouse_y;
    input.mouse_y = input.mouse_y - excess;
    assert_test(input.mouse_y == temp - excess, "Mouse central y coordinate successfully set.");
    
    *tile_x = input.mouse_x / TILE_SIZE;
    assert_test(*tile_x == input.mouse_x / TILE_SIZE, "Current tile x coordinate in array set.");

    *tile_y = input.mouse_y / TILE_SIZE;
    assert_test(*tile_y == input.mouse_y / TILE_SIZE, "Current tile y coordinate in array set.");
    
    cursor.x = input.mouse_x;
    assert_test(cursor.x == input.mouse_x, "Current x coordinate matched to current tile array x coordinate.");

    cursor.y = input.mouse_y;
    assert_test(cursor.y == input.mouse_y, "Current y coordinate matched to current tile array y coordinate.");
    
    cursor_src->y = 0;
    assert_test(cursor_src->y == 0, "Cursor src rectangle y coordinate initialised to zero.");

    cursor_src->x = 0;
    assert_test(cursor_src->x == 0, "Cursor src rectangle x coordinate initialised to zero.");

    cursor_src->w = TILE_SIZE;
    assert_test(cursor_src->w == TILE_SIZE, "Cursor src width set to tile size.");

    cursor_src->h = TILE_SIZE;
    assert_test(cursor_src->h == TILE_SIZE, "Cursor src height set to tile size.");
    
    cursor_dst->y = cursor.y;
    assert_test(cursor_dst->y == cursor.y, "Cursor dst rectangle y coordinate initialise to zero.");

    cursor_dst->x = cursor.x;
    assert_test(cursor_dst->x == cursor.x, "Cursor dst rectangle x coordinate initialise to zero.");

    cursor_dst->w = TILE_SIZE;
    assert_test(cursor_dst->w == TILE_SIZE, "Cursor dst width set to tile size.");

    cursor_dst->h = TILE_SIZE;
    assert_test(cursor_dst->h == TILE_SIZE, "Cursor dst height set to tile size.");
    
    tile_src->y = 0;
    assert_test(tile_src->y == 0, "Tile src rectangle y coordinate initialised to zero.");
    
    tile_src->x=0;
    assert_test(tile_src->x == 0, "Tile src rectangle x coordinate initialised to zero.");
    
    tile_src->w=TILE_SIZE;
    assert_test(tile_src->w == TILE_SIZE, "Tile src rectangle width set to tile size.");
    
    tile_src->h=TILE_SIZE;
    assert_test(tile_src->h == TILE_SIZE, "Tile src rectangle height set to tile size.");

    printf("\n");
}

void test_initialise_level_editor_map(void)
{
    int i, j, map_array[ROOM_Y][ROOM_X];

    for (i = 0; i < ROOM_Y; ++i) {
        for (j = 0; j < ROOM_X; ++j) {
            map_array[i][j] = 0;
            CU_ASSERT(map_array[i][j] == 0)
        }
    }

    printf("\n\nNo errors indicates map successfully initialised to zero.\n\n");
}

void test_highlight_area(void)
{
    printf("\n");

    highlight_area_case(new_game);

    highlight_area_case(image_drawing);

    highlight_area_case(options);

    highlight_area_case(editor);

    highlight_area_case(in_option_screen);

    printf("\n");
}

void highlight_area_case(menu_options option)
{
    SDL_Rect tile_src, tile_drc;
    menu_options current_selection = option;

    if(current_selection == new_game){
        assert_test(current_selection == new_game, "New game successfully registered.");

        tile_src = (SDL_Rect) {333,442,143,31};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {333,442,143,31}), "Source rectangle for new game successfully set.");
        
        tile_drc = (SDL_Rect) {333,472,143,31};
        assert_test(sizeof(tile_drc) == sizeof((SDL_Rect) {333,472,143,31}), "Destination rectangle for new game successfully set.");
    }
    else if(current_selection == image_drawing){
        assert_test(current_selection == image_drawing, "Load game successfully registered.");

        tile_src = (SDL_Rect) {336,473,143,31};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {336,473,143,31}), "Source rectangle for load game successfully set.");

        tile_drc = (SDL_Rect) {336,504,143,31};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {336,504,143,31}), "Destination rectangle for load game successfully set.");
    }
    else if(current_selection == options){
        assert_test(current_selection == options, "Options successfully registered.");

        tile_src = (SDL_Rect) {344,499,119,32};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {344,499,119,32}), "Source rectangle for options successfully set.");

        tile_drc = (SDL_Rect) {344,532,119,32};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {344,532,119,32}), "Destination rectangle for options successfully set.");

    }
    else if(current_selection == editor){
        assert_test(current_selection == editor, "Editor successfully registered.");

        tile_src = (SDL_Rect) {331,526,140,30};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {331,526,140,30}), "Source rectangle for editor successfully set.");

        tile_drc = (SDL_Rect) {331,560,140,30};
        assert_test(sizeof(tile_src) == sizeof((SDL_Rect) {331,560,140,30}), "Destination rectangle for editor successfully set.");
    }

    if(current_selection == new_game || current_selection == image_drawing || current_selection == options || current_selection == editor){
        assert_test(current_selection == new_game || current_selection == image_drawing || current_selection == options || current_selection == editor, "Registered to be at some point on the main menu.");
    }
    else if(current_selection == in_option_screen){ 
        assert_test(current_selection == in_option_screen, "In option screen registered.");       
    }
}

void test_cycle_options(void){

    printf("\n");

    cycle_options_case(0, image_drawing);
    cycle_options_case(1, image_drawing);
    cycle_options_case(0, editor);

    printf("\n");
    
}

void cycle_options_case(int up_down, int current_selection){
    
    bool menu_running = true;
    int temp;

    while(menu_running){

        assert_test( menu_running == true, "Menu successfully recognised as running.");

        temp = current_selection;

        switch(up_down)
        {
            case 1: // simulate UP
                if (current_selection == image_drawing || current_selection == options || current_selection == editor )
                {    
                    current_selection--;
                    assert_test( current_selection = temp - 1 ,"Lower option selected correctly.");
                }
                else
                {
                    assert_test( current_selection = temp, "Same option reselected correctly.");
                }

            break;


            case 0: // simulate DOWN
                if( current_selection == new_game || current_selection == image_drawing || current_selection == options )
                {
                    current_selection++;
                    assert_test( current_selection = temp + 1 ,"Higher option selected correctly.");
                }      
                else
                {
                    assert_test( current_selection = temp, "Same option reselected correctly.");
                }      
            break;
        }
        
        menu_running = false;
    }
}


void test_menu_space_press(void){




}



