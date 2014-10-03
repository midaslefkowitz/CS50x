/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP by a factor of n (the first argument).
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define HEADERS_SIZE 54

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

	// get factor
	int factor = atoi(argv[1]);
	
	// ensure that factor is proper size
	if (factor < 1 || factor > 100)
	{
		printf("First argument must be an int between 1 (inclusive) and 100 (inclusive)\n");
		return 2;
	}
	
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
	    
	// make a copy of BITMAPFILEHEADER for resized bitmap
	BITMAPFILEHEADER bf_new;
	bf_new.bfType = bf.bfType; 
    bf_new.bfReserved1 = bf.bfReserved1; 
    bf_new.bfReserved2 = bf.bfReserved2; 
    bf_new.bfOffBits = bf.bfOffBits; 


    // make a copy of BITMAPINFOHEADER for resized bitmap
	BITMAPINFOHEADER bi_new;
	bi_new.biSize = bi.biSize; 
    bi_new.biWidth = bi.biWidth * factor;
    bi_new.biHeight = bi.biHeight * factor;
    bi_new.biPlanes = bi.biPlanes;
    bi_new.biBitCount = bi.biBitCount;
    bi_new.biCompression = bi.biCompression;
    bi_new.biXPelsPerMeter = bi.biXPelsPerMeter;
    bi_new.biYPelsPerMeter = bi.biYPelsPerMeter;
    bi_new.biClrUsed = bi.biClrUsed;
    bi_new.biClrImportant = bi.biClrImportant;

    // determine padding for scanlines
    int padding_old =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// adjust file size in header to accomodate refactoring
	// actual image size is pixels * sizeof pixels + padding * height
	bi_new.biSizeImage = ((bi_new.biWidth * sizeof(RGBTRIPLE)) + padding_new) * abs(bi_new.biHeight);
	// total image size is that + the size of the headers (54)
	bf_new.bfSize = bi_new.biSizeImage + HEADERS_SIZE;
		
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);
	
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // create array to save scanLine of pixels
        RGBTRIPLE line[bi_new.biWidth];
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

           	// read RGB triple from infile
           	fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
			
			// repeat factor number of times to resize width
			for (int k=0; k < factor; k++)
			{
				// get current width position in resized image 
            	int w_position = (j * factor) + k;
            	// place triple into array
            	line [w_position] = triple;
            	
            	// write RGB triple to outfile
            	//fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        
        // write from the array to new image factor times to resize height
        for (int lines = 0; lines < factor; lines++)
        {
			for (int w_position = 0; w_position < bi_new.biWidth; w_position++)
        	{
        		fwrite(&(line[w_position]), sizeof(RGBTRIPLE), 1, outptr);
        	}        	

        	// add padding to new image, if any
        	for (int k = 0; k < padding_new; k++)
        	{
            	fputc(0x00, outptr);
        	}
        }

        // skip over padding, if any
       	fseek(inptr, padding_old, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
