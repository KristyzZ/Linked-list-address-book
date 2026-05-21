#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

Person *input_person(void)
{
    char name[30];
    char surname[30];
    char email[30];
    char number[30];

    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter surname: ");
    scanf("%s", surname);

    printf("Enter email: ");
    scanf("%s", email);

    printf("Enter phone number: ");
    scanf("%s", number);

    return create_person(name, surname, email, number);
}

int main() 
{
    Person *list = NULL;
    int choice;

    load_from_csv(&list);

    do{
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

        scanf("%d", &choice);
        getchar();

        if (choice == 1){
            display(list);
        }
        else if (choice == 2){
            Person *new_person = input_person();
            insert(&list, new_person);
            load_to_csv(new_person);
        }
        else if (choice == 3){
            int position;

            printf("Enter position:");
            scanf("%d", &position);

            Person *new_person = input_person();
            insert_with_position(&list, new_person, position);
            save_all_to_csv(list);
        }
        else if (choice == 4){
            int position;

            printf("Enter position:");
            scanf("%d", &position);

            delete_with_position(&list, position);
            save_all_to_csv(list);
        }
        else if (choice == 5){
            //delete_all();
        }
        else if (choice == 6){
            //find_by_position();
        }
        else if (choice == 7){
            //search();
        }
        else if (choice == 0){
            //exit
            printf("Program closed.\n");
        }
        else {
            printf("Invalid Choice");
        }
    } while (choice != 0);

    return 0;
}

/*
Delete address indicating its position in the book

Delete whole address book

Find address by position

Find addressess by name, surname, email or phone number
*/