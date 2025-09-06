#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./greet first_name last_name\n");
        return -1;
    }

    printf("Hello, %s %s\n", argv[1], argv[2]);
    return 0;
}