/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

/* Node in the trie */
typedef struct node
{
    bool word_end;
    struct node* children[27];
} node;

/* Globals */
int num_words = 0;
node* root = malloc(sizeof(node));

/**
 * Returns true if the char is valid for trie
 */
bool isValid(char letter)
{
	if (letter < 'A')
	{
		// it might be ' or newline		
		return (letter == '\n' || letter == '\'');
	}
	if (letter > 'Z')
	{
		// check if it's a lowercase letter
		return (letter >= 'a' && letter <= 'z');
	}
}

/**
 * If char is uppercase converts lowercase otherwise retains state
 */
 char toLower(char letter)
 {
 	if (letter >= 'A' && letter <= 'Z')
 	{
 		letter += ('a' - 'A');
 	}
 	return letter;
 }

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// Open dictionary
	FILE* file = fopen(dictionary, "r");
	
	// Ensure that found the dictionary
	if (file == NULL)
	{
		printf("Couldn't find dictionary!\n");
		return false;
	}
		
	// temporary storage 
	char buffer;
	
	// current position in trie
	node* current = root;
	
	// iterate through the dictionary one char at a time
	while (fread(buffer, sizeof(char), 1, file))
	{
		// ensure that that the char is valid
		if (isValid(buffer))
		{
			// convert uppercase to lowercase
			buffer = toLower(buffer);
			
			// if dict char == /n 
			
				// mark current node as word_end
			
				// increment total words
			
				// reset current to root
			
			// else 
				
				// 
	
		}
	}
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
