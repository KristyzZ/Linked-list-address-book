#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER ","


struct Person {
    char name[30];
    char surname[30];
    char email[30];
    char number[30];
    struct Person *next;
};

struct Person* create_address_node(char *address_line);
struct Person* create_node(char *name, char *surname, char *email, char *number);
void add_to_list(struct Person **list, struct Person *node);
void print_list(struct Person *list);
void delete_list(struct Person **list);
void load_addresses(FILE *file, struct Person **list);
void display_file(struct Person *list);
void add_to_list(struct Person **list, struct Person *person);
void add_new_person(FILE *file);
void read_file(char *file_path, struct Person **list);


FILE *open_file(char *file, char *mode);

int main(void)
{
    char address_file_path[30] = "addresses.csv";
    struct Person *list = NULL;
    FILE *address_file = NULL;

    read_file(address_file_path, &list);

    address_file = open_file(address_file_path, "a");

    add_new_person(address_file);

    fclose(address_file);

    read_file(address_file_path, &list);

    return 0;
}

void read_file(char *file_path, struct Person **list)
{
    FILE *address_file = open_file(file_path, "r");

    load_addresses(address_file, list);
    display_file(*list);

    fclose(address_file);
}

void append_file(char *file_path)
{
    FILE *address_file = open_file(file_path, "a");

    add_new_person(address_file);

    fclose(address_file);
}
FILE *open_file(char *file, char *mode)
{
    FILE *address_file = fopen(file, mode);

    if(address_file == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    return address_file;
}

void load_addresses(FILE *file, struct Person **list)
{
    char line[128];
    while (fgets(line, sizeof(line), file)){
        struct Person *person = NULL;
        if(strcmp(line, "\n") == 0) {
            continue;
        }
        person = create_address_node(line);
        if (person != NULL){
            add_to_list(list, person);
        }
    }
}

struct Person* create_address_node(char *address_line)
{
    struct Person *person = NULL;
    char *name;
    char *surname;
    char *email;
    char *number;

    name = strtok(address_line, DELIMITER);
    surname = strtok(NULL, DELIMITER);
    email = strtok(NULL, DELIMITER);
    number = strtok(NULL, DELIMITER);

    person = create_node(name, surname, email, number);

    return person;
}

struct Person* create_node(char *name, char *surname, char *email, char *number)
{
    struct Person *person = malloc(sizeof(struct Person));
    if(person == NULL) {
        return NULL;
    }

    strcpy(person->name, name);
    strcpy(person->surname, surname);
    strcpy(person->email, email);
    strcpy(person->number, number);
    person->next = NULL;

    return person;  
}

void add_to_list(struct Person **list, struct Person *person)
{
    struct Person *temp = *list;
    if (temp == NULL){
        *list = person;
        return;
    }

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = person;
}

void display_file(struct Person *list)
{
    struct Person *temp = list;
    while(temp != NULL){
        printf("%s %s %s %s", temp->name, temp->surname, temp->email, temp->number);
        temp = temp->next;
    }
}

void add_new_person(FILE *file)
{
    char name[30];
    char surname[30];
    char email[30];
    char number[30];

    printf("Enter Name:\n");
    scanf("%s", name);
    printf("Enter Surname:\n");
    scanf("%s", surname);
    printf("Enter Email:\n");
    scanf("%s", email);
    printf("Enter Number:\n");
    scanf("%s", number);

    fprintf(file, "%s,%s,%s,%s\n",
        name,
        surname,
        email,
        number);
    
    return;
}

/*
    Add new address to the book (to the end)

    Add new address indicating the position where to put it

    Delete address indicating its position in the book

    Delete whole address book

    Find address by position

    Find addressess by name, surname, email or phone number
*/