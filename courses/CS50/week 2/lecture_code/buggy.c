#include <stdio.h>
#include <cs50.h>

void print_column(int);

int main()
{
    int height = get_int("Choose height: ");
    print_column(height);
}

void print_column(int height)
{
    for (int i = 0; i <= height; i++)
    {
        printf("#\n");
    }
}
