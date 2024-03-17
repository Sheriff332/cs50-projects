// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 2];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26*26 + 26;

// Hash table
node *table[N];

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hashval= hash(word);
    node* n = table[hashval];
    if (n==NULL){return false;}
    char* tmpstr = n->word;
    for (;tmpstr != NULL; n = n->next, tmpstr = n->word)
    {
        if (strlen(tmpstr) != strlen(word)) {continue;}
        int i,j;
        for (i=0, j=strlen(tmpstr); i<j; i++)
        {
            if (toupper(tmpstr[i]) != toupper(word[i])) {break;}
            if (i==j-1) {return true;}
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashvalue=0;
    if (strlen(word)>2)
    {
     hashvalue = 26*(toupper(word[0]) - 'A') + toupper(word[1]) - 'A' + 26;
    }
    else {hashvalue =toupper(word[0]) - 'A';}
    return hashvalue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    char *s=malloc((LENGTH + 2)* sizeof(char)); // Buffer to store each word from the file
    if (s == NULL)
    {
        fclose(file);
        printf("Memory allocation failed.\n");
        return false;
    }
    node* new_node = NULL;
    while (fgets(s, LENGTH +2, file) != NULL) // Read each line from the file
    {
        // Remove newline character if present
        char *newline = strchr(s, '\n');
        if (newline != NULL)
        {
            *newline = '\0';
        }

        // Allocate memory for the new node and check for allocation failure
        new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            free(s);
            printf("Memory allocation failed.\n");
            return false;
        }

        // Copy the word into the node and update the hash table
        strcpy(new_node->word, s);
        unsigned int index = hash(s);

        // Handle collision by appending to linked list
        new_node->next = table[index];
        table[index] = new_node;
        dict_size++;
    }

    fclose(file);
    free(s);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i=0;
    for (i=0;i<N;i++)
    {
        node* cursor = table[i];
        if (cursor==NULL){continue;}
        node* tmp = cursor;
        while (cursor->next != NULL)
        {
            cursor = cursor ->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
