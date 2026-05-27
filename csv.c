#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

#define DELIMITER ","


void load_to_csv(Person *new_person)
{
    char path[512];
    const char *home = getenv("HOME");

    if(home == NULL){
        perror("Failed to open file");
        return;
    }

    snprintf(path, sizeof(path), "%s/addresses.csv", home);
    
    FILE *file = fopen(path, "a");

    if (file == NULL) {
        printf("addresses.csv not found. Continuing without default records.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s\n", new_person->name, new_person->surname, new_person->email, new_person->number);

    fclose(file);
}

void load_from_csv(Person **head)
{
    char path[512];
    const char *home = getenv("HOME");

    if(home == NULL){
        perror("Failed to open file");
        return;
    }

    snprintf(path, sizeof(path), "%s/addresses.csv", home);
    
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("addresses.csv not found. Continuing without default records.\n");
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, DELIMITER);
        char *surname = strtok(NULL, DELIMITER);
        char *email = strtok(NULL, DELIMITER);
        char *number = strtok(NULL, DELIMITER);
        
        if (name && surname && email && number){
            Person *new_person = create_person(name, surname, email, number);
            insert(head, new_person);
        }
    }
    fclose(file);
}

void save_all_to_csv(Person *head)
{
    char path[512];
    const char *home = getenv("HOME");

    if (home == NULL) {
        perror("Failed to find path");
        return;
    }

    snprintf(path, sizeof(path), "%s/addresses.csv", home);

    FILE *file = fopen(path, "w");

    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", head->name, head->surname, head->email, head->number);
        head = head->next;
    }

    fclose(file);
}
