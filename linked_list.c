#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"




// void load_from_csv()
// {
//     char path[512];
//     char *home = getenv("HOME");

//     if(home == NULL){
//         printf("Could not find home directory.\n");
//         return;
//     }

//     sprintf(path, sizeof(path), "%s/addresses.csv", home);
    
//     FILE *file = fopen(path, "r");

//     if (file == NULL) {
//         printf("addresses.csv not found. Continuing without default records.\n");
//         return;
//     }

//     char line[256];

//     while (fgets(line, sizeof(line), file)) {
//         line[strcspn(line, "\n")] = '\0';

// }