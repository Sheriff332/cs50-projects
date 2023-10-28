#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc!=2)
    {
        printf ("Usage: %s key\n", argv[0]);
    }
    if (strlen(argv[1])!=26)
    {
        printf ("Key must contain 26 characters\n");
    }
    string text = get_string("plaintext: ");
    int len=strlen(text);
    int i;
    for (i=0;i<len;i++)
    {
        if(isupper(text[i]))
        {
            text[i]=toupper(argv[1][text[i]-65]);
        }
        else if(islower(text[i]))
        {
            text[i]=tolower(argv[1][text[i]-97]);
        }
    }
    printf("ciphertext: %s\n", text);
}
