#ifndef __INPUT_H__
#define __INPUT_H__

void process_movement_flags(void);
void process_inventory_substate(int key);
void process_map_substate(int key);
void process_game_state(int key);

void process_input(void);

#endif