#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);


int main(void)
{
    string msg = get_string("Message:");
    int n = strlen(msg);
    int i, index, loop;

    int l[8];

    for (i = 0; i < n; i++)
    {
        char chr = msg[i];
        int chrdec = (int) chr;

        for (index = 7; index >= 0; index--)
        {
            l[index] = chrdec % 2;
            chrdec /= 2;
        }

        for (loop = 0; loop < 8; loop++)
        {
            print_bulb(l[loop]);
        }
        printf("\n");
    }
}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
