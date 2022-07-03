#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int owed;
    while (1)
    {
        owed = get_float("Change owed: ");
        if (owed >= 0)
        {
            break;
        }
    }

    return owed;
}

int calculate_quarters(int cents)
{
    int count = 0;

    // if we do not need to return user more than 25 cents
    if (cents < 25)
    {
        return 0;
    }
    while (1)
    {
        if (cents >= 25 * (count + 1))
        {
            count++ ;
        }
        else
        {
            break;
        }
    }

    return count;
}

int calculate_dimes(int cents)
{
    int count = 0;

    // if we do not need to return user more than 10 cents
    if (cents < 10)
    {
        return 0;
    }

    while (1)
    {
        if (cents >= 10 * (count + 1))
        {
            count++ ;
        }
        else{
            break;
        }
    }

    return count;
}

int calculate_nickels(int cents)
{
    int count = 0;

    // if we do not need to return user more than 5 cents
    if (cents < 5)
    {
        return 0;
    }

    while (1)
    {
        if (cents >= 5 * (count + 1))
        {
            count++ ;
        }
        else{
            break;
        }
    }

    return count;
}

int calculate_pennies(int cents)
{
    int count = 0;

    // if we do not need to return user more than 1 cents
    if (cents < 1)
    {
        return 0;
    }

    while (1)
    {
        if (cents >= 1 * (count + 1))
        {
            count++ ;
        }
        else{
            break;
        }
    }

    return count;
}
