#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linked_list.h"

#define SUCCESS 0
#define ERROR_EMPTY_LIST 1
#define ERROR_INVALID_POSITION 2
#define ERROR_DISPLAY_FAILED 3
#define ERROR_NULL_POINTER 4
#define ERROR_NO_RECORD 5

void print_node(Person *head, int position)
{
    printf("\nPosition #%d\n", position);
    printf("Name: %s\n", head->name);
    printf("Surname: %s\n", head->surname);
    printf("Email: %s\n", head->email);
    printf("Number: %s\n", head->number);
}

int search(Person *head, const char *query)
{
    int found = 0;
    int position = 1;
    while (head != NULL){
        if (
            strcmp(head->name, query) == 0 || 
            strcmp(head->surname, query) == 0 || 
            strcmp(head->email, query) == 0 || 
            strcmp(head->number, query) == 0
        ){
            print_node(head, position);
            found = 1;
        }
        head = head->next;
        position++;
    }
    
    if (!found) {
        return ERROR_NO_RECORD;
    }

    return SUCCESS;
}

int find_by_position(Person *head, int position)
{
    for (int i = 1; head != NULL && i < position; i++){
        head = head->next;
    }

    if (head == NULL) {
        return ERROR_INVALID_POSITION;
    }

    print_node(head, position);
    
    return SUCCESS;
}

int delete_all(Person **head)
{
    if (head == NULL) {
        return ERROR_NULL_POINTER;
    }

    Person *current = *head;

    while (current != NULL){
        Person *temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
    return SUCCESS;
}

int delete_with_position(Person **head, int position)
{
    if (*head == NULL) {
        return ERROR_EMPTY_LIST;
    }

    Person *temp = *head;

    if (position <= 1){
        *head = (*head)->next;
        free(temp);
        return SUCCESS;
    }

    Person *previous = NULL;

    for (int i = 1; temp != NULL && i < position; i++) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL){
        return ERROR_INVALID_POSITION;
    }

    previous->next = temp->next;
    free(temp);

    return SUCCESS;
}

int display(Person *head)
{
    if (head == NULL){
        return ERROR_DISPLAY_FAILED;
    }

    int position = 1;

    while (head != NULL) {
        print_node(head, position);

        head = head->next;
        position++;
    }

    return SUCCESS;
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

Person *create_person(const char *name, const char *surname, const char *email, const char *number)
{
    Person *new_person = malloc(sizeof(Person));

    if (new_person == NULL){
        perror("malloc");
        return NULL;
    }

    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    strcpy(new_person->email, email);
    strcpy(new_person->number, number);
    new_person->next = NULL;

    return new_person;
}
