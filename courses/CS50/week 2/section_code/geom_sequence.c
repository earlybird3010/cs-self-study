// Create an array of size 5 in which every
// element is 2 times its previous element

#include <stdio.h>

int main(int argc, char *argv[])
{
    int geometric_sequence[5];

    int start = 1;

    for (size_t i = 0; i < sizeof(geometric_sequence) / sizeof(geometric_sequence[0]); i++)
    {
        geometric_sequence[i] = start;
        start *= 2;
    }

    for (size_t i = 0; i < sizeof(geometric_sequence) / sizeof(geometric_sequence[0]); i++)
    {
        printf("Element %i: %i\n", i + 1, geometric_sequence[i]);
    }
}