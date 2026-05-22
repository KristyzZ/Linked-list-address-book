#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "linked_list.h"

Person *list = NULL;

void cleanup(void)
{
    save_all_to_csv(list);
    delete_all(&list);
}

void signal_handler(int signal)
{
    printf("Received signal: %d\n", signal);

    cleanup();

    exit(0);
}

void read_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
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

int get_pos(void){
    char buffer[20];
    int position;

    printf("Enter position: ");

    read_string(buffer, sizeof(buffer));

    position = atoi(buffer);

    return position;
}

int main() 
{
    signal(SIGINT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGQUIT,signal_handler);

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

        char buffer[20];

        read_string(buffer, sizeof(buffer));

        choice = atoi(buffer);

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
            read_string(query, sizeof(query));
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