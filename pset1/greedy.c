#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define QUARTER .25
#define DIME .1
#define NICKEL .05
#define PENNY .01

float rnd(float);

int main(void) 
{
    // Get amount owed from the user
    float owed;
    do 
    {
        printf("How much change is owed?\n");
        owed = GetFloat();        
    }
    while (owed<0);
    owed = rnd(owed);
        
    int numCoins = 0;
    
    while (owed>0) //while still have change in hand
    {
        /* determine largest coin possible to make change
         * add one to total number of coins needed
         * subtract value of coin from change required */
        if (owed>=QUARTER) 
        {
            numCoins++; 
            owed-=QUARTER;  
        }
        else if (owed>=DIME)
        {
            numCoins++;
            owed-=DIME;
        }
        else if (owed>=NICKEL)
        {
            numCoins++;
            owed-=NICKEL;
        }
        else if (owed>0)
        {
            numCoins++;
            owed-=PENNY;
        }
        owed = rnd(owed);
    }

    printf("%i\n", numCoins);
}

float rnd(float num) 
{
    return ((int) (round(num*100)) )/100.0;
}
