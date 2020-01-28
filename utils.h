#ifndef SPELLER_UTILS
#define SPELLER_UTILS


#include "dictionary.h"

// Counts the number of nodes in a linked list
unsigned int count_list(node* list);

// Frees a linked-list (Iteratively)
void destroy(node* list);

#endif // SPELLER_UTILS