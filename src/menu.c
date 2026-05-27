#include <stdio.h>
#include <stdlib.h>

#include "menu.h"


int get_pos(void)
{
    char buffer[20];
    int position;

    printf("Enter position: ");

    read_string(buffer, sizeof(buffer));

    position = atol(buffer);

    return position;
}

Person *input_person(void)
{
    char name[100];
    char surname[100];
    char email[100];
    char number[100];

    printf("Enter name: ");
    read_string(name, sizeof(name));


    printf("Enter surname: ");
    read_string(surname, sizeof(surname));


    printf("Enter email: ");
    read_string(email, sizeof(email));


    printf("Enter phone number: ");
    read_string(number, sizeof(name));


    return create_person(name, surname, email, number);
}

void print_menu()
{
    printf("\n===== ADDRESS BOOK MENU =====\n");
    printf("1. Display all records\n");
    printf("2. Add new address to the end\n");
    printf("3. Add new address at position\n");
    printf("4. Delete address by position\n");
    printf("5. Delete whole address book\n");
    printf("6. Find address by position\n");
    printf("7. Search by name, surname, email or phone\n");
    printf("0. Exit\n");
    printf("Choose: ");
}

void print_error(int result)
{
    if (get_error_message(result) != 0){
    printf("Error: %s\n", get_error_message(result));
    }
}
