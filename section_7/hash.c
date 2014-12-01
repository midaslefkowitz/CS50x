#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>

// typedef a node for the linked list
typedef struct node
{
    char* word;
    struct node* next;
} node;

/* Prototypes */
unsigned long hash (char* key);
bool insert (char* value, int index);
bool load_table();
char* toLower (char* word);
bool find (char* word_to_find);

/* Constants */
#define NUM_STRINGS 10

/* Globals */
node* hash_table[NUM_STRINGS];

int main (void) 
{
	if (!load_table())
	{
		// table didn't load properly
		printf("table didn't load properly\n");
		return 1;
	}
	
	while (true)
	{
		printf("1. Find a word in the dictionary\n");
		printf("2. Quit\n");

		int user_choice;
		do 
		{
			user_choice = GetInt();
		} while (user_choice != 1 && user_choice != 2);
		
		switch (user_choice)
		{
			case 1:
				printf("Please enter a word: ");
                char* word_to_find = GetString();
                char* success = find(word_to_find) ? "is" : "is not";
                printf("%s %s in the dictionary.\n",word_to_find, success);
                break;
            case 2:
            	return 0;
            	break;
		}
	}
	return 0;
}

bool load_table()
{
	char* strings[NUM_STRINGS] = 
	{
		"aaa",
		"aab",
		"hello",
		"cat",
		"dog",
		"kenny",
		"Kenny",
		"double",
		"ties",
		"egypt"
	};
	
	// initialize the cells in the table to NULL
	for (int i=0; i<NUM_STRINGS; i++)
	{
		hash_table[i] = NULL;
	}
	
	// for each word in the dummy data list
	for (int i=0; i<NUM_STRINGS; i++)
	{
		// convert the key o all lowercase
		char* key = toLower(strings[i]);
		
		// get the hash value of the string
		unsigned long hash_value = hash(key);
		
		// modulo the hash value to size of table
		hash_value = hash_value % NUM_STRINGS;
		
		// insert the value into the hash table
		if (!insert(key, hash_value))
		{
			return false;
		}
	}
	return true;
}

char* toLower (char* word)
{	
	// allocate space on heap for word
	int size = strlen(word);
	char* temp = malloc((sizeof(char)) * (size + 1));
	
	for (int i=0, len=strlen(word); i<len; i++)
	{
		if (word[i]<='Z')
		{
			*(temp+i) = word[i] + ('z' - 'Z');
		}
		else 
		{
			*(temp+i) = word[i];
		}
	}
	return temp;
}

unsigned long hash (char* key)
{
	
	unsigned long hash = 5381;
    int c;

    while ((c = *key++) != 0)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

bool insert (char* value, int index)
{
	// allocate and initialize new node
	node* new_node = malloc(sizeof(node));
	if (new_node == NULL)
	{
		// malloc unsuccessful
		return false;
	}
	
	// initialize fields of new node
	new_node->word = malloc((sizeof(char) * (strlen(value)+1) ) );
	strcpy(new_node->word, value);
	new_node->next = NULL;
	
	// first insertion
    if (hash_table[index] == NULL)
    {
        new_node->next = NULL;
        hash_table[index] = new_node;
        return true;
    }
    
    else 
    {
    	// check if string already in table
    	node* temp = hash_table[index];
    	while (temp != NULL)
    	{
			if ((strcmp(value, temp->word)) == 0)
		    {
		        free(new_node);
		        return true;
		    }
		    temp = temp->next;
        }
        /* insert word */
        // save reference to next node
        temp = hash_table[index]->next;
        // insert node at beginning of list
		hash_table[index] = new_node;
		// update the reference to next node
		hash_table[index]->next = temp;
		return true;
	}
	return true;
}

bool find (char* word_to_find)
{
	// get the hash value of the word_to_find
	unsigned long hash_value = hash(word_to_find);
	// modulo the hash value to size of table
	hash_value = hash_value % NUM_STRINGS;
	
	// go to the corresponding linked list in the hash_table
	node* current = hash_table[hash_value];
	// traverse the list looking for word_to_find
	while (current != NULL)
	{
		// if the node word == word_to_find
		if ((strcmp(current->word, word_to_find)) == 0)
		{
			// return true
			return true;
		}
		current = current->next;
	}
	// traversed and didn't find. return false	
	return false;
}
