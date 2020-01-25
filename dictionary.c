// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

bool LOADED = false;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];  // Extra 1 Byte for null terminator
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
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
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
