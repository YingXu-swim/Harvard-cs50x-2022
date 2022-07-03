#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//declare
bool only_digits(string s);
char rotate(char c, int n);


int main(int argc, string argv[])
{
    //not legal condition
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

   //if is not number/negative
   int k = atoi(argv[1]);
   if (k < 0 || only_digits(argv[1]) == false)
   {
       printf("Usage: ./caesar key\n");
       return 1;
   }

    //input
    string s = get_string("plaintext:  ");
    printf("ciphertext: ");
    //for each char
    for (int i=0, n = strlen(s); i<n; i++)
    {
        printf("%c", rotate(s[i],k));
    }
    printf("\n");
}
//if a string onluy contents digit?
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i<n ; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}
//rotate a char into aimed char
char rotate(char c, int n)
{
    if (c >='a' && c<='z')
    {
        return (c + n - 'a') % 26 + 'a';
    }
    else if (c>='A' && c<='Z')
    {
        return (c + n - 'A') % 26 + 'A';
    }
    else
    {
        return c;
    }
}