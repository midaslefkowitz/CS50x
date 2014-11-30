#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DUMMY_NODES 4
#define INSERT_NODES 5
#define TO_FIND 5

typedef struct node 
{
	int n;
	struct node* next;
} node;

node* append(node* current, int value);
bool insert(node* current, int value);
void print_list(node* head);
bool find(node* head, int value);
node* delete(node* head, int value);
void delete_all(node* head);

int main(int argc, char* argv[])
{
	/* create a linked list with some dummy data */

	// dummy numbers
	int dummy[] = {2, 4, 6, 8};
	int to_insert[] = {2, 4, 5, 9, 0};
	int to_find[] = {0, 5, 7, 9, 10};
	
	// create head node
	node* head = malloc(sizeof(node));

	// keep track of current node
	node* current = head;
	current->n = dummy[0];
	
	for (int i=1; i<DUMMY_NODES; i++)
	{
		current = append(current, dummy[i]);
	}
	
	// traverse list printing all values 
	current = head;
	printf("Before insert\n");
	print_list(head);
	int i;
	
	// insert new nodes
	for (i=0; i<INSERT_NODES; i++)
	{
		insert(head, to_insert[i]);
		printf("After insert %i\n", to_insert[i]);
		print_list(head);
	}
	
	// find some values
	for (i=0; i<TO_FIND; i++)
	{
		printf("%i is ", to_find[i]);
		if (!(find(head, to_find[i])))
		{
			printf("not ");
		}
		printf("in the list\n");
	}
	
	// delete 
	head = delete(head, 0);
	printf("after deleting 0\n");
	print_list(head);
	head = delete(head, 4);
	printf("after deleting 4\n");
	print_list(head);
	head = delete(head, 9);
	printf("after deleting 9\n");
	print_list(head);
	head = delete(head, 10);
	printf("after deleting 10\n");
	print_list(head);
	
	// delete all
	delete_all(head);
	
	head = NULL;
	current = NULL;
	
}

void delete_all (node* head)
{
	node* current = head;
	node* next = current->next; 
	
	while (current != NULL)
	{
		next = current->next;
		free (current);
		current = next;
	}
}

void print_list(node* head)
{
	node* current = head;
	while (current->next != NULL) 
	{
		printf("%i\n", current->n);
		current = current->next;
	}
	printf("%i\n", current->n);	
}

/***
* Returns a pointer to the appended node
***/

node* append(node* current, int value)
{
	node* new_node = malloc(sizeof(node));
	current->next = new_node;
	new_node->n = value;
	new_node->next = NULL;
	return new_node; 
}

/***
* Returns a pointer to the head of the new list 
***/
node* delete(node* head, int value) 
{
	node* current = head;
	if (head->n == value) 
	{	
		head = head->next;
		free (current);	
	}
	else
	{
		while (current->next != NULL)
		{
			if (((current->next)->n) == value)
			{
				node* temp = current->next;
				current->next = ((current->next)->next);
				free (temp);
				break;
			}
			current = current->next;
		}
	}
	return head;
}

/***
* Returns true if value in list false otherwise
***/
bool find(node* head, int value)
{
	node* current = head;
	while (current->next != NULL) 
	{
		// Take advantage of sorted list
		if (value > current->n)
		{
			// if searched for value > current value not in list	
			return false;
		}
		else if (current->n == value)
		{
			return true;
		}
		current = current->next;
	}
	return current->n==value;
}

/***
* Returns true if insert was successful false otherwise
***/
bool insert(node* head, int value)
{
	node* current = head;

	while (true) 
	{
		// if current value is equal to inserted value no need to insert
		if (current->n == value)
		{
			return false;
		}
			
		/* if next is null just need to append */
		if (current->next == NULL)
		{
			// append the value to the list
			append(current, value);
			return true;
		}
		
		/* if current value greater than inserted value */
		if (current->n > value)
		{
			/* prepend node here */
			
			// save a copy of current_node n
			int temp_n = current->n;

			// change current n to value
			current->n = value;
			
			// save a reference to next so doesn't get lost
			node* temp_node = current->next; 
			
			// append old current n to new current
			node* inserted = append(current, temp_n);
			
			// appends next to inserted
			inserted->next = temp_node;
			
			return true;
		}
	
		/* if the current value is less than inserted value */
		if (current->n < value)
		{
			// if next value is greater than the inserted value
			if (((current->next)->n) > value)
			{
				// insert value between current and next
			
				// save a reference to next so doesn't get lost
				node* temp = current->next;
			
				// append value to current
				node* inserted = append(current, value);
			
				// appends next to inserted
				inserted->next = temp;
			
				return true;
			}
	
			// change current node to next node
			current = current->next;
		}
	}
	return false;
}
