#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>

// Welcome screen
const char *rock_art =
    "    _______ \n"
    "---'   ____)\n"
    "      (____)\n"
    "      (____)\n"
    "      (___)\n"
    "---.__(___)\n";

const char *paper_art =
    "    _______ \n"
    "---'   ____)____\n"
    "          ______)\n"
    "          _______)\n"
    "         _______)\n"
    "---.__________) \n";

const char *scissors_art =
    "    _______ \n"
    "---'   ____)____\n"
    "          ______)\n"
    "       __________)\n"
    "      (____)\n"
    "---.__(___)\n";

void print_welcome_screen(void);

// Game logic
int number_of_rounds = 0;
void get_rounds_num(void);

int main(void)
{
    // Display welcome screen
    print_welcome_screen();
    
    // Get number of rounds and display result
    get_rounds_num();
    printf("Okay, we're going to play %i rounds.\n", number_of_rounds);
}

void print_welcome_screen(void)
{
    printf("%s", rock_art);
    printf("%s", paper_art);
    printf("%s", scissors_art);
    printf("Welcome to the classic Rock, Paper, Scissors! We wish you a happy experience!\n");
}

// Get an integer number of rounds from the user
void get_rounds_num(void)
{   
    do
    {
        number_of_rounds = get_int("How many rounds do you want to play? ");
    } while (number_of_rounds <= 0);
}
