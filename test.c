#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned int) time(NULL));
    
    string color = "";
    
    int c = (int) (rand() % 256);
    
    sprintf(color, "%x", c);
    
    printf("%d as a hex: %s", c, color);
}
