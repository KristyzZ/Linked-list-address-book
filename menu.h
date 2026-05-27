#ifndef MENU_H
#define MENU_H

#include "linked_list.h"
#include "utils.h"

void print_menu(void);
int get_pos(void);
Person *input_person(void);
void print_error(int result);

#endif