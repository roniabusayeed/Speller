// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

bool LOADED = false;

// Total number of words in the dictionary
unsigned int SIZE = 0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];  // Extra 1 Byte for null terminator
    struct node *next;
}
node;


// Prototypes

// Counts the number of nodes in a linked list
unsigned int count_list(node* list);

// Frees a linked-list (Iteratively)
void destroy(node* list);


// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initially the word is not yet found because we are not done searching the hashtable.
    bool found = false;

    // Finding the right bucket in hashtable.
    unsigned int idx = hash(word);

    // Traverse the linked list to find a word match. Search no more if found a match.
    for (node* temp = table[idx]; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            found = true;
            break;
        }
    }

    // Result
    return found;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int a = 0;
    int b = 0;

    // Hash only if the length of string is at least 2. Otherwise hash to 0.
    if (word && strlen(word) > 1)
    {
        a = toupper(word[0]) - 65;
        b = toupper(word[1]) - 65;
    }
    return 26 * a + b;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
   // Putting empty list in all the buckets of hashtable.
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file for reading
    FILE* ptr = fopen(dictionary, "r");
    if(ptr == NULL)
    {
        // Failure
        return false;
    }

    // Temporary word
    char* word = malloc(sizeof(char) * (LENGTH + 1));  // Extra 1 Byte for null terminator
    if (word == NULL)
    {
        // Failure
        return false;
    }

    while(fscanf(ptr, "%s", word) != EOF)
    {
        int idx = hash(word);   // This is where in the hash table the word goes.

        // Make a node and insert into the hashtable in the hashed idx.
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Failure
            return false;
        }

        strcpy(n->word, word);
        n->next = table[idx];
        table[idx] = n;

        // This loop iterates the same number of times SIZE should be.
        SIZE++;
    }

    // Free temporary word
    free(word);

    // Done working with the file
    fclose(ptr);

    // Success
    LOADED = true;
    return true; 
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(!LOADED)
    {
        return 0;
        // Returning SIZE directly would also work, 'cause it's if nothing's loaded it's default
        // value is 0
    }
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;

    // I don't think there will be a case where it's unsuccessful. But sure I'll look!
}

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
