#ifndef __ITEM_USE_H__
#define __ITEM_USE_H__

#include "globals.h"

void heal_player(int percentage);
bool identify_item(bool log);
int identify_all();
bool decurse_item(bool log);
int decurse_all();
void teleport_player();
void expose_map();

void use_potion_action(int id);
void use_scroll_action(int id);

#endif
