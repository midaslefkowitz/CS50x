#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int onlyAlpha(string key);

int main(int argc, string argv[])
{
    if (!(argc==2)) 
    {
        printf("Vigenere.c accepts (ONLY) one argument \n");
        return 1;
    }
    
    else if ((onlyAlpha(argv[1])) == 1)
    {
        printf("Vigenere.c accepts ONLY strings \n");
        return 1;
    }
       
    else 
    {
        // extract key from command line
        string keyText = argv[1];
        // get plaintext from user
        string text = GetString();
        
        // keep an index for iterating through keyText
        int index = 0;
        
        for (int i = 0, textLen = strlen(text); i < textLen; i++)
        // iterate through string
        {
            // get key based on current index
            int key = (isupper(keyText[index]) ? (keyText[index]-'A') : (keyText[index]-'a'));
            
            if ( isalpha(text[i]) ) //if the character is a letter...
            {
                // ...change letter based upon case and key
                text[i]= (isupper(text[i])) ? ((((text[i]-'A')+key)%26 )+'A') : ((((text[i]-'a')+key)%26)+'a');
                // increment index and wrap around
                index = (index+1) % strlen(keyText);
            }
        }
        printf("%s\n", text); //print the result
        return 0;
    }
}

int onlyAlpha(string key)
{
    for (int i = 0, keyLen = strlen(key);i < keyLen; i++)
    {
        if (!(isalpha(key[i]) ) )
        {
            return 1;
        }
    }
    return 0;
}
