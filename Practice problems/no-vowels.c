// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    int len=strlen(argv[1]);
    int i;
    for (i=0; i<len; i++)
    {
        switch(argv[1][i])
        {
            case 'a':
                argv[1][i]='6';
                break;
            case 'e':
                argv[1][i]='3';
                break;
            case 'i':
                argv[1][i]='1';
                break;
            case 'o':
                argv[1][i]='0';
                break;
            default:
                break;

        }
    }
    printf ("%s\n", argv[1]);
}
