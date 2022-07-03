#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get input(height)
    int height;
    while (1)
    {
        height = get_int("Height:");
        if (height >0 && height <9)
        {
            break;
        }
    }

    //each line
    for (int i = 0; i < height; i++)
    {
        // " "part
        for (int j = 0; j < (height - i - 1); j++)
        {
            printf(" ");
        }
        // "#" part
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}