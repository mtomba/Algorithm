/********************************************************************
 *
 * Singly linked list implementation
 *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define list_info printf
#define TRUE    1
#define FALSE   0
typedef unsigned char bool;

/*
 * List data structure
 */
typedef struct _list_element_t_ {
    struct _list_element_t_ *next;
    unsigned int data;
} list_t;

/*
 * Create a list of size (n) elements
 */
bool list_create (list_t **head, unsigned int size)
{
    int i;
    unsigned int data;
    unsigned int iseed;
    list_t *element = NULL;
    list_t *prev_element = NULL;

    iseed = (unsigned int) time(NULL);

    srand(iseed);

    for (i = 0; i < size; i++) {
        element = (list_t*) malloc(sizeof(list_t));
        if (!element) {
            list_info("Error in creating element %d of the list\n", i);
            return (FALSE);
        }

        /* Lets fill up the blanks */
        data = rand() % 200;
        element->data = data;
        element->next = NULL;

        /*
         * If we have a valid previous element, set its next to the
         * current element.
         */
        if (prev_element) {
            prev_element->next = element;
        }
        prev_element = element;

        /*
         * If this is the first element, then update the head pointer.
         */
        if (i == 0) {
            *head = element;
        }
    }

    return (TRUE);
}

/*
 * Print all data in the list
 */
void list_print (list_t *head)
{
    #define LIST_WIDTH  10
    int counter = 0;
    list_t *elem = head;

    while (elem != NULL) {
        if (counter == 0) {
            list_info("\n");
        }
        list_info("%d", elem->data);

        if (elem->next) {
            list_info(" --> ");
        }
        elem = elem->next;

        counter++;

        if (!(counter % LIST_WIDTH)) {
            list_info("\n");
        }
    }

    if (counter) {
        list_info("\n\n");
    }
}

/*
 * Sort the list in ascending order
 */
void list_sort_ascending (list_t **head)
{
    /*
     * To be added later
     */
}

int main (void)
{
    #define MAX_NUM_OF_ELEMENTS 8
    list_t *list_head = NULL;
    
    /* Create our list */
    if (!list_create(&list_head, MAX_NUM_OF_ELEMENTS)) {
        list_info("Cannot create linked list\n");
        return (1);
    }

    list_info("Original List:");
    list_print(list_head);


    list_info("Sorted List:");
    list_print(list_head);

    return (0);
}
