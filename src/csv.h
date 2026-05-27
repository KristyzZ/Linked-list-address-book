#ifndef CSV_H
#define CSV_H

#include "linked_list.h"

void load_to_csv(Person *new_person);
void load_from_csv(Person **head);
void save_all_to_csv(Person *head);

#endif