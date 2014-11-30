/**
 * linked.c
 *
 * week 7 section
 * fall 2013
 *
 * practice using linked lists
 */

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// typedef a node for the linked list
typedef struct node
{
    int n;
    struct node* next;
}
node;

// function prototypes
bool insert_node(int value);
void print_nodes(node* list);
void free_nodes(node* list);

// global variable for the head of the list
node* head = NULL;

int main(void)
{
    // offer the user two options
    while (true)
    {
        printf("Please choose an option (0, 1, 2): ");
        int option = GetInt();
        
        switch (option)
        {
            // quit
            case 0:
                free_nodes(head);
                printf("Goodbye!\n");
                return 0;
            
            // insert int into linked list
            case 1:
                printf("Please enter an int: ");
                int v = GetInt();
                char* success = insert_node(v) ? "was" : "was not";
                printf("The insert %s successful.\n", success);
                break;
            
            // print all ints
            case 2:
                print_nodes(head);
                break;
            
            default:
                printf("Not a valid option.\n");
                break;
        }
    }
}

/**
 * Create a new node for a given value and insert it into a list.
 */
bool insert_node(int value, node* list)
{
    // create a new node
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
    	return false;
    }
    new_node->n = value;
    
    // create current and prev pointers
    node* curr == list;
    node* prev == NULL;
    
    // go through the list
    while (curr != NULL) 
    {
    	// if value < this node
    	if (value < curr->n)
    	{
    		// insert before
    		if (prev == NULL)
    		{
    			head = new_node;
    		}
    		else 
    		{
    		
    			node* temp = prev->next;
    			prev->next = new_node;
    			free (temp);
    		}
    		return true;
    	}
    }
}

/**
 * Print out all of the ints in a list.
 */
void print_nodes(node* list)
{
    // TODO
}

/**
 * Frees all of the nodes in a list upon exiting the program.
 */
void free_nodes(node* list)
{   
    // TODO
}
