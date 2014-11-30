#include <stdio.h>
#include <stdbool.h>

/* Prototypes */
unsigned long hash (char* key);

/* Constants */
#define NUM_STRINGS 10

int main (void) 
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
	
	long hash_return;
	
	for (int i=0; i<NUM_STRINGS; i++)
	{
		hash_return = hash(strings[i]);
		printf("%s has a hash value of %li \n", strings[i], hash_return);
	}
	
}

unsigned long hash (char* key)
{
	unsigned long hash = 5381;
    int c;

    while ((c = *key++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash<0) ? hash*-1 : hash;
}
