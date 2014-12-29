#include "testing_headers.h"

//                                          MAIN FUNCTION

int main(int aroom_gridc, char *argv[])
{
    set_up_test("Make Room Suite", "Test of makeRoom()", test_makeRoom);

    set_up_test("Print Instruction Suite", "Test of print_instruction()", test_print_instruction);

    set_up_test("Get Instructions Suite", "Test of get_instructions()", test_get_instructions);

    set_up_test("Print Instruction to Screen Suite", "Test of print_instruction_to_screen()", test_print_instruction_to_screen);

    set_up_test("SDL Events Suite", "Test of SDL_Events()", test_SDL_events);

    set_up_test("Look for Action Suite", "Test of look_for_action()", test_look_for_action);

    set_up_test("SDL Quit Checker Suite", "Test of SDL_Quitchecker()", test_SDL_Quitchecker);

    set_up_test("Draw Suite", "Test of draw()", test_draw);

    set_up_test("Draw Room Suite", "Test of draw_room()", test_draw_room);

    set_up_test("Rectangle Source Set Suite", "Test of rcsrc_set()", test_rcsrc_set);

    set_up_test("Rectangle Object Set Suite", "Test of rcobj_set()", test_rcobj_set);

    set_up_test("Initialise Room Grid Components Suite", "Test of initialise_roomgrid_components()", test_initialise_roomgrid_components);

    set_up_test("Initialise Chicken Suite", "Test of initialise_chicken()", test_initialise_chicken);

    set_up_test("Position Sprite Suite", "Test of position_sprite()", test_position_sprite);

    set_up_test("Position Chicken Suite", "Test of position_chicken()", test_position_chicken);

    set_up_test("Movement Suite", "Test of movement()", test_movement);

    set_up_test("Sound Suite", "Test of sound_on_off()", test_sound_on_off);

    set_up_test("Edge Detection Suite", "Test of edge_detection()", test_edge_detection);

    set_up_test("Possible Suite", "Test of possible()", test_possible);

    set_up_test("Move Suite", "Test of move()", test_move);

    set_up_test("Interact Probe Suite", "Test of interactProbe()", test_interactProbe);

    set_up_test("Action Suite", "Test of action()", test_action);

    set_up_test("Door Hinge Problem Suite", "Test of door_hinge_problem()", test_door_hinge_problem);

    set_up_test("Find a Weight Suite", "Test of find_weight_a()", test_find_weight_a);

    set_up_test("Find b Weight Suite", "Test of find_weight_b()", test_find_weight_b);

    set_up_test("Hen Sequence Suite", "Test of hen_sequence()", test_hen_sequence);

    set_up_test("Initialise Problem Suite", "Test of initialise_problem()", test_initialise_problem);

    set_up_test("Permit Chicken Suite", "Test of permit_chicken()", test_permit_chicken);

    return(0);
}