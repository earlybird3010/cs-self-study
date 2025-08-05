// Prompt the user for a number between 1 and 8 (inclusive) and display 2 adjacent pyramids of
// blocks
#include <cs50.h>
#include <stdio.h>

// Print 2 adjacent pyramids with corresponding height
void print_pyramids(int height)
{
    // show_block: visible pyramid block on each line, hide_block: invisible pyramid block on each
    // line
    int show_block = 1, hide_block = height - show_block;

    for (int i = 0; i < height; i++)
    {
        // Print line of left pyramid
        for (int j = 0; j < hide_block; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < show_block; j++)
        {
            printf("#");
        }

        // Print distance between two pyramids
        printf("  ");

        // Print line of right pyramid
        for (int j = 0; j < show_block; j++)
        {
            printf("#");
        }

        // Remember to move to the next line
        printf("\n");

        show_block += 1;
        hide_block -= 1;
    }
}

int main(int argc, string argv[])
{
    // Prompt user for number
    while (true)
    {
        int pyramid_height = get_int("Height: ");
        if (pyramid_height >= 1 && pyramid_height <= 8)
        {
            print_pyramids(pyramid_height);
            break;
        }
    }
}
