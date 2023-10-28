#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int only_digits(const char *numstr);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) == 1)

    {
        printf("Usage: %s <shift>\n", argv[0]);
        return 1;
    }

    int shift = atoi(argv[1]);
    string text = get_string("plaintext: ");
    int i, n;
    for (i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = (char)((((int)text[i] - 65 + shift) % 26) + 65);
        }
        else if (islower(text[i]))
        {
            text[i] = (char)((((int)text[i] - 97 + shift) % 26) + 97);
        }
    }
    printf("ciphertext: %s\n", text);
    return 0;
}

int only_digits(const char *numstr)
{
    for (int x = 0; x < strlen(numstr); x++)
    {
        if (!isdigit(numstr[x]))
        {
            return 1;
        }
    }
    return 0;
}
