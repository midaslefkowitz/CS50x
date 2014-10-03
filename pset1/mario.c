#include <stdio.h>
#include <cs50.h>

int main (void) 
{
    int height;
    do //get height from user
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height<0 || height>23);
    
    //print pyramid
    //first loop though pyramid height
    for (int i=0; i<height; i++) 
    {
        //for each row of pyramid determine bricks and spaces
        int numSpaces = height - (i + 1);
        int numBricks = height - numSpaces;
        
        //add spaces
        for (int space=0; space<numSpaces; space++)
        {
            printf(" ");
        }
        //add bricks
        for (int brick=0; brick<numBricks; brick++)
        {
            printf("#");
        }
        //add final brick and newline
        printf("#\n");
    }
}
