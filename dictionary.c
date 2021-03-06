// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h" // Contains definition of struct node
#include "hash.h"
#include "utils.h"


bool LOADED = false;

// Total number of words in the dictionary
unsigned int SIZE = 0;

// Number of buckets in hash table
const unsigned int N = 10000;

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

// Hashes (case insensitively) a null terminated byte string to a (32-bit) unsigned integer
unsigned int hash(const char* data)
{
    // Make a lowecase copy of <data>
    unsigned int len = strlen(data);
    char* str = malloc(sizeof(char) * (len + 1));
    for(int i = 0; data[i]; i++)
    {
      str[i] = tolower(data[i]);
    }
    str[len] = 0;

    // Hash the lowercase copy of <data>: <str>
    // Hash all (len) bytes i.e. characters of str
    unsigned int hashCode = SuperFastHash(str, len) % N;
    // printf("%u\n", hashCode);

    // Free
    free(str);
    return hashCode;
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
