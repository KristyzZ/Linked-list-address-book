#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


#define DELIMITER ","

void delete_with_position(Person **head, int position)
{
    if (*head == NULL) {
        printf("Address book is empty.\n");
        return;
    }

    Person *temp = *head;

    if (position <= 1){
        *head = (*head)->next;
        free(temp);
        printf("Record deleted.\n");
        return;
    }

    Person *previous = *head;

    for (int i = 1; temp != NULL && i < position; i++) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL){
        printf("Invalid position.\n");
    }

    previous->next = temp->next;
    free(temp);
    printf("Record deleted.\n");
}

void display(Person *head)
{
    if (head == NULL){
        printf("List is empty\n");
        return;
    }

    int position = 1;

    while (head != NULL) {
        printf("\nPosition #%d\n", position);
        printf("Name: %s\n", head->name);
        printf("Surname: %s\n", head->surname);
        printf("Email: %s\n", head->email);
        printf("Number: %s\n", head->number);

        head = head->next;
        position++;
    }
}

void insert(Person **head, Person* new_person)
{
    Person *current = *head;

    if (*head == NULL){
        *head = new_person;
        return;
    }

    while (current->next != NULL){
        current = current->next;
    }

    current->next = new_person;
}

void insert_with_position(Person **head, Person* new_person, int position)
{
   if (position <= 1 || *head == NULL){
        new_person->next = *head;
        *head = new_person;
        return;
    }

    Person *current = *head;

    for (int i = 1; i < position - 1; i++) {
        current = current->next;
    }

    new_person->next = current->next;
    current->next = new_person;
}

Person *create_person(char *name, char *surname, char *email, char *number)
{
    Person *new_person = malloc(sizeof(Person));

    if (new_person == NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    strcpy(new_person->email, email);
    strcpy(new_person->number, number);
    new_person->next = NULL;

    return new_person;
}
void load_to_csv(Person *new_person)
{
    char path[512];
    char *home = getenv("HOME");

    if(home == NULL){
        printf("Could not find home directory.\n");
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
    char *home = getenv("HOME");

    if(home == NULL){
        printf("Could not find home directory.\n");
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
    char *home = getenv("HOME");

    if (home == NULL) {
        printf("Could not find home directory.\n");
        return;
    }

    snprintf(path, sizeof(path), "%s/addresses.csv", home);

    FILE *file = fopen(path, "w");

    if (file == NULL) {
        printf("Could not open addresses.csv for writing.\n");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", head->name, head->surname, head->email, head->number);
        head = head->next;
    }

    fclose(file);
}