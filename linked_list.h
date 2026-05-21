#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Person {
    char name[50];
    char surname[50];
    char email[80];
    char phone[30];
    struct Person *next;
} Person;


#endif