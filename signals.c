#include <stdio.h>
#include <stdlib.h>

#include "signals.h"

volatile sig_atomic_t signal_received = 0;

void cleanup(Person *list)
{
    save_all_to_csv(list);
    delete_all(&list);
}

void signal_handler(int signal)
{
    signal_received = signal;
}
