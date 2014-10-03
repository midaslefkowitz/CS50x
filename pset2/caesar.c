#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (!(argc==2)) 
    {
        printf("Ceaser.c accepts (ONLY) one argument \n");
        return 1;
    }
    
    else 
    {
        // extract key from command line arguments
        int key = atoi(argv[1])%26;
        // get plaintext from user
        string text = GetString();
        
        for (int i = 0, textLen = strlen(text); i < textLen; i++)
        // iterate through string
        {
            if ( isalpha(text[i]) ) //if the character is a letter...
            {
                // ...change letter based upon case and key
                text[i]= (isupper(text[i])) ? ((((text[i]-'A')+key)%26 )+'A') : ((((text[i]-'a')+key)%26)+'a');
            }
        }
        printf("%s\n", text); //print the result
        return 0;
    }
}
