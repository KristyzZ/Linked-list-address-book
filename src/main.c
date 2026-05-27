#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "linked_list.h"

#define DELIMITER ","
#define SUCCESS 0
#define ERROR_EMPTY_LIST 1
#define ERROR_INVALID_POSITION 2
#define ERROR_DISPLAY_FAILED 3
#define ERROR_NULL_POINTER 4
#define ERROR_NO_RECORD 5

int get_pos(void);
Person *input_person(void);
void read_string(char *buffer, int size);
void signal_handler(int signal);
void cleanup(Person *list);
void print_menu();
void load_to_csv(Person *new_person);
void load_from_csv(Person **head);
void save_all_to_csv(Person *head);
const char *get_error_message(int error_code);

volatile sig_atomic_t signal_received = 0;

int main() 
{
    signal(SIGINT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGQUIT,signal_handler);

    Person *list = NULL;

    int choice;

    load_from_csv(&list);

    do{
        if (signal_received) {
            printf("\nReceived signal: %d\n", signal_received);
            cleanup(list);
            exit(EXIT_SUCCESS);
        }

        print_menu();
        char buffer[20];

        read_string(buffer, sizeof(buffer));

        choice = atol(buffer);

        if (choice == 1){
            int result = display(list);
            printf("Error: %s\n", get_error_message(result));
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

            int result = delete_with_position(&list, position);
            printf("Error: %s\n", get_error_message(result));
            save_all_to_csv(list);
        }
        else if (choice == 5){
            int result = delete_all(&list);
            printf("Error: %s\n", get_error_message(result));
        }
        else if (choice == 6){
            int position = get_pos();

            int result = find_by_position(list, position);
            printf("Error: %s\n", get_error_message(result));
        }
        else if (choice == 7){
            char query[50];

            printf("Enter query:");
            read_string(query, sizeof(query));
            int result = search(list, query);

            printf("Error: %s\n", get_error_message(result));
        }
        else if (choice == 0){
            printf("Program closed.\n");
        }
        else {
            printf("Invalid Choice");
        }
    } while (choice != 0);

    cleanup(list);

    return SUCCESS;
}

void load_to_csv(Person *new_person)
{
    char path[512];
    const char *home = getenv("HOME");

    if(home == NULL){
        perror("Failed to open file");
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
    const char *home = getenv("HOME");

    if(home == NULL){
        perror("Failed to open file");
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
    const char *home = getenv("HOME");

    if (home == NULL) {
        perror("Failed to find path");
        return;
    }

    snprintf(path, sizeof(path), "%s/addresses.csv", home);

    FILE *file = fopen(path, "w");

    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", head->name, head->surname, head->email, head->number);
        head = head->next;
    }

    fclose(file);
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

void cleanup(Person *list)
{
    save_all_to_csv(list);
    delete_all(&list);
}

void signal_handler(int signal)
{
    signal_received = signal;
}

void read_string(char *buffer, int size) 
{
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

int get_pos(void)
{
    char buffer[20];
    int position;

    printf("Enter position: ");

    read_string(buffer, sizeof(buffer));

    position = atol(buffer);

    return position;
}

const char *get_error_message(int error_code)
{
    switch (error_code) {
        case SUCCESS:
            return "Success";

        case ERROR_EMPTY_LIST:
            return "Address book is empty";

        case ERROR_INVALID_POSITION:
            return "Invalid position";

        case ERROR_DISPLAY_FAILED:
            return "Display failed";

        case ERROR_NULL_POINTER:
            return "Null pointer error";

        case ERROR_NO_RECORD:
            return "No matching record found";

        default:
            return "Unknown error";
    }
}