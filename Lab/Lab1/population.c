#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    double n;
    do
    {
        n = get_double("Starting Population Size: ");
    }
    while (n < 9);

    // TODO: Prompt for end size
    double n2;
    do
    {
        n2 = get_double("Ending Population Size: ");
    }
    while (n2 < n);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (n<n2)
    {
        n+=n/12.0;
        years++;
        printf("%f %f %i\n", n, n2, years);
    }
    // TODO: Print number of years
    printf("Time taken in years: %i\n", years);
}
