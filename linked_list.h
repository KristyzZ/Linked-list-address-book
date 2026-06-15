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
Person *create_person(const char *name, const char *surname, const char *email, const char *number);

int display(Person *head);
void insert_with_position(Person **head, Person* new_person, int position);
int delete_with_position(Person **head, int position);
int delete_all(Person **head);

int find_by_position(Person *head, int position);
int search(Person *head, const char *query);
void print_node(Person *head, int position);

const char *get_error_message(int error_code);

#endif