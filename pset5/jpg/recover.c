/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h>
#include <stdlib.h>

#define BLOCKSIZE 512
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
	// Open forensic image of sd card
	FILE* file = fopen("card.raw", "r");
	
	// Ensure that found the card
	if (file == NULL)
	{
		printf("Couldn't find card.raw!\n");
		return 1;
	}
	
	// temporary storage
	BYTE* buffer = malloc(sizeof(BYTE) * BLOCKSIZE);
	
	// flag if found a pic already
	bool pic_open = false;
	
	// counter for found images
	int num_pics = 0;
	
	// string for current pic name
	char title[8];
	// declaration of img
	FILE* img;
	
	// read through the raw file
	while (fread(buffer, sizeof(BYTE), BLOCKSIZE, file))
	{
		// check for pic beginning
		bool startOfPic = false;
		if (buffer[0] == 0xff &&
			buffer[1] == 0xd8 &&
			buffer[2] == 0xff &&
			(buffer[3] == 0xe0 || buffer[3] == 0xe1))
		{
			startOfPic = true;
		}		
		
		// if found start of pic
		if (startOfPic)
		{
			// check if a pic was already opened
			if (pic_open)
			{
				//close old pic
				fclose(img);				
			}
			// open a new pic
			pic_open = true;
			sprintf(title, "%03d.jpg", num_pics++);
			img = fopen(title, "a");
		}
		if (pic_open)
		{
			// write to image
			fwrite(buffer, sizeof(BYTE), BLOCKSIZE, img);
		}
	}
	
	// close pic
	fclose(img);
	// close raw file
	fclose(file);
	
	free(buffer);
	return 0;
}
