#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int max = 100;
const int min = 10;

int main(int argc, string argv[])
{
    // Generate a random number
    printf("Guess a number between %i and %i\n", min, max);
    srand((unsigned) time(NULL));
    int num = rand() % (max - min + 1) + min;

    int rounds = get_int("How many rounds do u want to play? ");
    
    // Ask user for an input. If he guesses it right, end game.
    // If he is wrong, continue for a fixed number of rounds,
    // and display appropriate messages.
    int cur_rounds = 0;
    do 
    {
        int x = get_int("Guess a number: ");
        if (x > max)
        {
            printf("Out of bound!\n");
        }
        else if (x > num)
        {
            printf("Too big!\n");
        } 
        else if (x < num)
        {
            printf("Too small!\n");
        }
        else if (x < min)
        {
            printf("Out of bound!\n");
        } else
        {
            printf("Yay! You guessed correctly!\n");
            break;
        }

        cur_rounds++;
    } while (cur_rounds < rounds);

    printf("Bye!\n");

}