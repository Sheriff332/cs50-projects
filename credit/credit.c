#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long card_number = get_long_long("Enter credit card number: ");

    int sum = 0;
    int alternate = 0;
    long long temp = card_number;

    while (temp > 0) {
        int digit = temp % 10;

        if (alternate) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        alternate = !alternate;
        temp /= 10;
    }

    if (sum % 10 == 0) {
        int length = 0;
        temp = card_number;
        while (temp > 0) {
            temp /= 10;
            length++;
        }

        long long divisor = 1;
        for (int i = 0; i < length - 2; i++) {
            divisor *= 10;
        }

        int first_two_digits = card_number / divisor;

        int first_digit = card_number / (divisor * 10);

        if ((first_two_digits >= 40 && first_two_digits <= 49) ||
            (first_digit == 4)) {
            printf("Visa\n");
        } else if (first_two_digits >= 51 && first_two_digits <= 55) {
            printf("MasterCard\n");
        } else if (first_two_digits == 34 || first_two_digits == 37) {
            printf("American Express\n");
        } else {
            printf("Unknown\n");
        }
    } else {
        printf("INVALID\n");
    }

    return 0;
}
