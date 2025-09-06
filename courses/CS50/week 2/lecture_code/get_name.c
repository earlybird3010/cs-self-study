// Get name from user and print to the console

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    string name = get_string("What's your name? ");
    if (name)
    {
        printf("Hello, %s\n", name);
    } else
    {
        printf("\nLooks like you typed in a special key!\n");
    }

    return 0;
}