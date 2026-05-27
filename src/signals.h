#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

#include "linked_list.h"
#include "csv.h"

extern volatile sig_atomic_t signal_received;

void signal_handler(int signal);
void cleanup(Person *list);

#endif