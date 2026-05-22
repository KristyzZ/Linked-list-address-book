#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "linked_list.h"

Person *global_list = NULL;

void signal_handler(int signal)
{
    printf("Received signal: %d\n", signal);

    cleanup();

    exit(0);
}

void cleanup(void)
{
    save_all_to_csv(global_list);
    delete_all(&global_list);
}

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

int get_pos(void){
    int position;

    printf("Enter position:");
    scanf("%d", &position);

    return position;
}

int main() 
{
    signal(SIGINT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGQUIT,signal_handler);

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
            int position = get_pos();

            Person *new_person = input_person();
            insert_with_position(&list, new_person, position);
            save_all_to_csv(list);
        }
        else if (choice == 4){
            int position = get_pos();

            delete_with_position(&list, position);
            save_all_to_csv(list);
        }
        else if (choice == 5){
            delete_all(&list);
        }
        else if (choice == 6){
            int position = get_pos();

            find_by_position(list, position);
        }
        else if (choice == 7){
            char query[50];

            printf("Enter query:");
            scanf("%s", query);
            search(list, query);
        }
        else if (choice == 0){
            printf("Program closed.\n");
        }
        else {
            printf("Invalid Choice");
        }
    } while (choice != 0);

    cleanup();

    return 0;
}

/*
Find addressess by name, surname, email or phone number
*/