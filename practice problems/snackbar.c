// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    menu[0] = (menu_item){"Burger", 9.5};
    menu[1] = (menu_item){"Vegan Burger", 11};
    menu[2] = (menu_item){"Hot Dog", 5};
    menu[3] = (menu_item){"Cheese Dog", 7};
    menu[4] = (menu_item){"Fries", 5};
    menu[5] = (menu_item){"Cheese Fries", 6};
    menu[6] = (menu_item){"Cold Pressed Juice", 7};
    menu[7] = (menu_item){"Cold Brew", 3};
    menu[8] = (menu_item){"Water", 2};
    menu[9] = (menu_item){"Soda", 2};
    return;
}


// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int j=0; j<10; j++)
    {
        if (strcasecmp(item, menu[j].item) ==0)
            return menu[j].price;
    }
    return 0.0;
}
