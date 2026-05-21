#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int main() 
{

    int choice;
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

        if (choice == 1){
            //display();
        }
        else if (choice == 2){
            //insert();
        }
        else if (choice == 3){
            //insert_with_position();
        }
        else if (choice == 4){
            //delete_with_position();
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
Display all records in the address book

Add new address to the book (to the end)

Add new address indicating the position where to put it

Delete address indicating its position in the book

Delete whole address book

Find address by position

Find addressess by name, surname, email or phone number
*/