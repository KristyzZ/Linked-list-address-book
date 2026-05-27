#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "linked_list.h"

#include "csv.h"
#include "menu.h"
#include "utils.h"
#include "signals.h"

#define SUCCESS 0




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
            print_error(result);
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
            print_error(result);
            save_all_to_csv(list);
        }
        else if (choice == 5){
            int result = delete_all(&list);
            print_error(result);
        }
        else if (choice == 6){
            int position = get_pos();

            int result = find_by_position(list, position);
            print_error(result);
        }
        else if (choice == 7){
            char query[50];

            printf("Enter query:");
            read_string(query, sizeof(query));
            int result = search(list, query);

            print_error(result);
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





