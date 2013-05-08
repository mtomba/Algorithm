/********************************************************************/
/*                                                                  */
/* Singly linked list implementation                                */
/*                                                                  */
/********************************************************************/

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
bool list_create_dynamic (list_t **head, unsigned int size)
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
            /*
             * TODO: Free up allocated buffers before returning
             */
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
 * Create a list of size (n) elements
 */
bool list_create_static (list_t **head,
                         unsigned int size,
                         unsigned int number_list[])
{
    int i;
    list_t *element = NULL;
    list_t *prev_element = NULL;

    for (i = 0; i < size; i++) {
        element = (list_t*) malloc(sizeof(list_t));
        
        if (!element) {
            list_info("Error in creating element %d of the list\n", i);
            /*
             * TODO: Free up allocated buffers before returning
             */
            return (FALSE);
        }

        /* Lets fill up the blanks */
        element->data = number_list[i];
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

/*
 * Search for the element containing 'data'
 */
list_t* list_find (list_t *head, unsigned int data)
{
    list_t *elem;

    elem = head;
    while (elem) {
        if (elem->data == data) {
            return (elem);
        }
        elem = elem->next;
    }

    return (NULL);
}

/*
 * Insert an element - pointed to by 'to_be_inserted' -
 * in the list, following the element 'preceding_elem'
 */
bool list_insert_element (list_t **head,
                          list_t *preceding_elem,
                          list_t *to_be_inserted)
{
    list_t *elem;

    /*
     * 'preceding_elem' can be NULL which means that
     * we want to insert the elemenet at the head of
     * the list. Hence why a NULL check is not required
     */
    if (!head || !*head || !to_be_inserted) {
        list_info("\nInvalid head or data pointer\n");
        return (FALSE);
    }

    elem = *head;
    if (!preceding_elem) {
        /* We want to make this new element the new head */
        to_be_inserted->next = *head;
        *head = to_be_inserted;
        return (TRUE);
    }

    while (elem) {
        if (elem == preceding_elem) {
            to_be_inserted->next = elem->next;
            elem->next = to_be_inserted;
            return (TRUE);
        }
        elem = elem->next;
    }

    return (FALSE);
}

/*
 * Remove an element - pointed to by 'to_be_removed' -
 * from the list
 */
bool list_remove_element (list_t **head, list_t *to_be_removed)
{
    list_t *elem;

    if (!head || !*head || !to_be_removed) {
        list_info("\nInvalid head or data pointer\n");
        return (FALSE);
    }

    elem = *head;
    if (*head == to_be_removed) {
        *head = elem->next;
        free(elem);
        return (TRUE);
    }

    while (elem) {
        if (elem->next == to_be_removed) {
            elem->next = to_be_removed->next;
            free(to_be_removed);
            return (TRUE);
        }

        elem = elem->next;
    }

    return (FALSE);
}

int main (void)
{
    #define NUM_OF_ELEMENTS 8
    list_t *list_head = NULL;
    list_t *temp = NULL;
    list_t *element = NULL;
    unsigned int numbers[] = { 3, 17, 22, 38, 45, 54, 61, 79 };
    unsigned int lookup;

    #ifdef LIST_DYNAMIC
    /* Create our dynamic list */
    if (!list_create_dynamic(&list_head, NUM_OF_ELEMENTS)) {
        list_info("Cannot create linked list\n");
        return (1);
    }
    #else

    /* Create a static list */
    if (!list_create_static(&list_head, NUM_OF_ELEMENTS, numbers)) {
        list_info("Cannot create linked list\n");
        return (1);
    }
    #endif

    list_info("\nOriginal List:");
    list_print(list_head);

    /*
     * Lets try the list_find routine to lookup a number
     */
    lookup = 45;
    list_info("Looking for '%d' in the list\n", lookup);
    temp = list_find(list_head, lookup);
    if (temp) {
        list_info("\nElement '%d' found at %x\n", temp->data, temp);
    } else {
        list_info("\nElement '%d' NOT found\n", lookup);
    }

    /*
     * And lets try to remove the element with the lookup number
     */
    list_info("Lets remove '%d' from the list\n", lookup);
    if (list_remove_element(&list_head, temp)) {
        list_info("Succesfully removed '%d' from the list\n", lookup);

    } else {
        list_info("Failed to remove '%d' from the list\n", lookup);
    }
    temp = NULL;

    list_info("\nUpdated List:");
    list_print(list_head);

    /* Lets insert a new element in the middle of the list */
    lookup = 22;
    list_info("\nLets add a new element after '%d'\n", lookup);

    temp = list_find(list_head, lookup);
    if (temp) {
        list_info("\nElement '%d' found at %x\n", temp->data, temp);
    } else {
        list_info("\nElement '%d' NOT found\n", lookup);
    }

    /* Create a new element */
    element = (list_t*) malloc(sizeof(list_t));
    if (!element) {
        list_info("Error in creating element to be inserted\n");
        return (FALSE);
    }
    element->data = 29;
    element->next = NULL;

    if (!list_insert_element(&list_head, temp, element)) {
        list_info("Failed to insert element into the list\n");
    }

    list_info("\nUpdated List:");
    list_print(list_head);

    /* Lets insert a new element in the head of the list */
    list_info("\nLets add a new element in the beginning of the list\n");

    /* Create a new element */
    element = (list_t*) malloc(sizeof(list_t));
    if (!element) {
        list_info("Error in creating element to be inserted\n");
        return (FALSE);
    }
    element->data = 1;
    element->next = NULL;

    if (!list_insert_element(&list_head, NULL, element)) {
        list_info("Failed to insert element into the list\n");
    }

    list_info("\nUpdated List:");
    list_print(list_head);

    return (0);
}
