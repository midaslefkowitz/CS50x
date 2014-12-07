/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"

/* Node in the trie */
typedef struct node
{
    bool word_end;
    struct node* children[27];
} node;

/* Globals */
int total_words = 0;
node* root;

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
	return false;
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
 * Converts a char into appropriate index for trie node
 */
int getIndex(char letter)
{
	if (letter == '\'')
	{
		return 26;
	}
	else
	{
		return letter - 'a';
	}
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	char* ptr = malloc(sizeof(char) * strlen(word) );
	strcpy(ptr, word);
	node* current = root;
	while (*ptr != '\0')
	{
		*ptr = toLower(*ptr);
		int index = getIndex(*ptr);
		if (current->children[index] == NULL)
		{
			return false;
		}
		else
		{
			current = current->children[index];
		}
		ptr++;
	}
    return current->word_end;
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
	char* buffer = malloc(sizeof(char));
	
	// current position in trie
	node* current = root = malloc(sizeof(node));
	
	// iterate through the dictionary one char at a time
	while (fread(buffer, sizeof(char), 1, file))
	{
		// ensure that that the char is valid
		if (isValid(*buffer))
		{
			// convert uppercase to lowercase
			*buffer = toLower(*buffer);
			
			// if buffer is a newline 
			if (*buffer == '\n')
			{
				if (current != root && 
					!current->word_end &&
					current != NULL)
				{
					// mark current node as word_end
					current->word_end = true;
					// increment total words
					total_words++;
					// reset current to root
					current = root;
				}
			}
			// else move down the appropriate branch of the trie
			else
			{	
				// find which index of node->[] to go to
				int index = getIndex(*buffer);
				// check if it's NULL
				if (current->children[index] == NULL)
				{				
					// create a new node
					node* new_node = malloc(sizeof(node));
					if (new_node == NULL)
					{
						return false;
					}
					// set its fields to NULL
					for (int i=0; i<27; i++)
					{
						new_node->children[i] = NULL;
					}
					current->children[index] = new_node;
				}	
				// set that node as current
				current = current->children[index];
			}
		}
	}
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return total_words;
}

void unloadHelper(node* current)
{
	for (int i=0; i<27; i++)
	{
		if (current->children[i] != NULL)
		{
			unloadHelper(current->children[i]);
		}
	}
	free(current);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	unloadHelper(root);
	return true;
}
