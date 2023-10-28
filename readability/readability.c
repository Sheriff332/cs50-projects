#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters,sentences,x;
    double words;
    int length = strlen(text);
    for (letters=0,words=1.0,sentences=0,x=0;x<length;x++)
    {
        if (isalnum(text[x]))
    {
        letters++;
    }
    else if (isspace(text[x]))
    {
        words++;
    }
    else if (text[x]==46 || text[x]==33 || text[x]==63)
    {
        sentences++;
    }
    }
    double a = (letters/words) *100.0;
    double b = (sentences/words) *100.0;
    int index = round((0.0588 * a) - (0.296 * b) - 15.8);
    if (index<1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index>16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
