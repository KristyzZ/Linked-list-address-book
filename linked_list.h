#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Person {
    char name[50];
    char surname[50];
    char email[80];
    char number[30];
    struct Person *next;
} Person;

void insert(Person **head, Person* new_person);
Person *create_person(char *name, char *surname, char *email, char *number);

void load_from_csv(Person **head);
void load_to_csv(Person *new_person);
void save_all_to_csv(Person *head);

void display(Person *head);
void insert_with_position(Person **head, Person* new_person, int position);
void delete_with_position(Person **head, int position);

#endif