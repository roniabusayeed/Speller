#include "utils.h"
#include <stddef.h>
#include <stdlib.h>


// Counts the number of nodes in a linked-list
unsigned int count_list(node* list)
{
    unsigned int counter = 0;

    // Traverse the linked-list
    for(node* temp = list; temp != NULL; temp = temp->next)
    {
        counter++;
    }

    return counter;
}

// Frees a linked-list (Iteratively)
void destroy(node* list)
{
    // While there is at least one node in the linked-list
    while (list)
    {
        // Save the rest of the list first
        node* temp = list->next;

        //  Free the first node
        free(list);

        // Rest of the list is now a new (shorter) list
        list = temp;
    }
}
