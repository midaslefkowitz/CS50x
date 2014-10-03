/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
      
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if the array has only one value
	if (n==1)
	{
		// see if it's the one we're looking for
		return ((value==values[0]) ? true : false);
	}
	else
	{
		// find the middle of the array
		int middle = n/2;
		
		if (value==values[middle]) // got lucky
		{
			return true;
		}
		else if (values[middle]>value)
		{
			// get first half of array
			int first_half[middle];
			for (int i=0; i<middle; i++)
			{
				first_half[i] = values[i];
			}
			
			// search the first half of the array
			return search (value, first_half, middle);
		}
		else
		{
			// get the second half of array
			int second_half[(n-middle-1)];
			for (int i=(middle+1), j=0; i<n; i++)
			{
				second_half[j] = values[i];
				j++;
			}
			// search the second half of the array
			return search (value, second_half, (n-middle-1));
		}
		return false;
	}
	return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int x=0; x<n; x++)
	{
		int min = x;
        
        // find next lowest
		for(int y=x; y<n; y++)
		{
			if(values[min]>values[y])
			{
				min = y;
			}
		}
		
		// swap lowest with value at x
		int temp = values[x];
		values[x] = values[min];
		values[min] = temp;
	}
}
