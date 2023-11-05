#include <cs50.h>
#include <stdio.h>

void string_multiply(char chr, int num)
{
    for (; num > 0; num--)
    {
        printf("%c", chr);
    }
}

int main(void)
{
    int n;
    do
    {
        n = get_int("Enter the number: ");
    }
    while (n <= 0 || n > 8);
    int i;
    for (i = n; i >= 0; i--)
    {
        string_multiply(' ', i);
        string_multiply('#', n - i);
        printf("\n");
    }
}
