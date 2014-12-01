#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// typedef a node for the linked list
typedef struct node
{
    char* word;
    struct node* next;
} node;

/* Prototypes */
unsigned long hash (char* key);
bool insert (char* value, node* head);
bool load_table();
char* toLower (char* word);

/* Constants */
#define NUM_STRINGS 10

int main (void) 
{
	if (!load_table())
	{
		// table didn't load properly
		return 1;
	}
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
	
	// declare hash table as array of linked lists
	node* hash_table[NUM_STRINGS];
	
	// initialize the cells in the table to NULL
	for (int i=0; i<NUM_STRINGS; i++)
	{
		hash_table[i] = NULL;
	}
	
	// for each word in the dummy data list
	for (int i=0; i<NUM_STRINGS; i++)
	{
		// convert the key to all lowercase
		char* key = toLower(strings[i]);
		
		// get the hash value of the string
		unsigned long hash_value = hash(key);
		
		// modulo the hash value to size of table
		hash_value = hash_value % NUM_STRINGS;
		
		// insert the value into the hash table
		if (!insert(strings[i], hash_table[hash_value]))
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

bool insert (char* value, node* head)
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
    if (head == NULL)
    {
        new_node->next = NULL;
        head = new_node;
        return true;
    }
    
    else 
    {
    	// check if string already in table
    	node* temp = head;
    	while (temp != NULL)
    	{
			if (strcmp(value, temp->word))
		    {
		        free(new_node);
		        return false;
		    }
		    temp = temp->next;
        }
        /* insert word */
        // save reference to next node
        temp = head->next;
        // insert node at beginning of list
		head = new_node;
		// update the reference to next node
		head->next = temp;
		return true;
	}
	return true;
}
