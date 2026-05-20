#include <stdio.h>
#include <stdlib.h>


struct Person {
    char name[30];
    char surname[30];
    char email[30];
    char number[30];
    struct Person *next;
};

void add_to_list(struct Person **list, struct Person *node);
void print_list(struct Person *list);
void delete_list(struct Person **list);
void load_addresses(FILE *file, struct Person **list);
void display_file(struct Person *list);


FILE *open_file(char *file, char *mode);

int main(void)
{
    char address_file_path[30] = "addresses.csv";
    struct Person *list = NULL;
    FILE *address_file = NULL;

    address_file = open_file(address_file_path, "r");

    load_addresses(address_file, &list);

    display_file(list);

    fclose(address_file);

    return 0;
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
        add_to_list(list, person);
    }
}

struct Person* create_address_node(char *address_line){

}

void display_file(struct Person *list)
{
    struct Person *temp = list;
    while(temp != NULL){
        printf("%s %s %s %s", temp->name, temp->surname, temp->email, temp->number);
        temp = temp->next;
    }
}

/*
    Display all records in the address book

    Add new address to the book (to the end)

    Add new address indicating the position where to put it

    Delete address indicating its position in the book

    Delete whole address book

    Find address by position

    Find addressess by name, surname, email or phone number
*/