#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK 'r'
#define PAPER 'p'
#define SCISSORS 's'
#define ROCK_VALUE 0
#define PAPER_VALUE 1
#define SCISSORS_VALUE 2
#define DEFAULT_STORE ' '

// Player
int p_score = 0;
int is_p_win = false;
char p_choice;

// Computer
int pc_score = 0;
int is_pc_win = false;
char pc_choice;
char pc_choose_random(void);

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
int get_rounds_num(void);
void start_game(int);
char get_player_choice(void);
void update_game(void);
void display_computer_choice(void);
void display_result(void);

int main(void)
{
    // Display welcome screen
    print_welcome_screen();
    
    // Get number of rounds and display result
    int number_of_rounds = get_rounds_num();
    printf("Okay, we're going to play %i rounds.\n", number_of_rounds);
    
    // Seed the random generator
    srand(time(NULL));

    start_game(number_of_rounds);

    printf("GOODBYE! And see you again!\n");
}

void print_welcome_screen(void)
{
    printf("%s", rock_art);
    printf("%s", paper_art);
    printf("%s", scissors_art);
    printf("Welcome to the classic Rock, Paper, Scissors! We wish you a happy experience!\n");
}

char get_player_choice(void)
{
    char p_choice = DEFAULT_STORE;

    do
    {
        p_choice = get_char("Pick an option amongst rock(r), paper(p), or scissors(s): ");
    } while (p_choice != ROCK && p_choice != PAPER && p_choice != SCISSORS);

    return p_choice;
}

// Get an integer number of rounds from the user
int get_rounds_num(void)
{   
    int number_of_rounds = 0;
    do
    {
        number_of_rounds = get_int("How many rounds do you want to play? ");
    } while (number_of_rounds <= 0);
    
    return number_of_rounds;
}

// Update state of game when get results from 1 round of rock, paper, scissors
void update_game(void)
{
    if (p_choice == ROCK && pc_choice == PAPER)
    {
        is_p_win = false;
        is_pc_win = true;
        pc_score += 1;
    } else if (p_choice == ROCK && pc_choice == SCISSORS)
    {
        is_p_win = true;
        is_pc_win = false;
        p_score += 1;
    } else if (p_choice == PAPER && pc_choice == ROCK)
    {
        is_p_win = true;
        is_pc_win = false;
        p_score += 1;
    } else if (p_choice == PAPER && pc_choice == SCISSORS)
    {
        is_p_win = false;
        is_pc_win = true;
        pc_score += 1;
    } else if (p_choice == SCISSORS && pc_choice == PAPER)
    {
        is_p_win = true;
        is_pc_win = false;
        p_score += 1;
    } else if (p_choice == SCISSORS && pc_choice == ROCK)
    {
        is_p_win = false;
        is_pc_win = true;
        pc_score += 1;
    } else
    {
        is_p_win = false;
        is_pc_win = false;
    }

}

void display_computer_choice(void)
{
    if (pc_choice == ROCK)
    {
        printf("The computer chooses ROCK!\n");
    } else if (pc_choice == PAPER)
    {
        printf("The computer chooses PAPER!\n");
    } else if (pc_choice == SCISSORS)
    {
        printf("The computer chooses SCISSORS!\n");
    }
}

// Display result of the current round
void display_result(void)
{
    if (is_p_win == is_pc_win)
    {
        printf("DRAW!\n");
    } else if (is_p_win)
    {
        switch(p_choice)
        {
            case ROCK:
                printf("ROCK smashes SCISSORS!\n");
                break;
            case PAPER:
                printf("PAPER covers ROCK!\n");
                break;
            case SCISSORS:
                printf("SCISSORS cuts PAPER!\n");
        }
        printf("YOU WIN!\n");
    } else
    {
        switch(pc_choice)
        {
            case ROCK:
                printf("ROCK smashes SCISSORS!\n");
                break;
            case PAPER:
                printf("PAPER covers ROCK!\n");
                break;
            case SCISSORS:
                printf("SCISSORS cuts PAPER!\n");
        }
        printf("YOU LOSE!\n");
    }
}

// Start game loop until a result is obtained
void start_game(int number_of_rounds)
{
    for (int i = 0; i < number_of_rounds; i++)
    {
        p_choice = get_player_choice();
        pc_choice = pc_choose_random();
        display_computer_choice();
        update_game();
        display_result();

        //Display points
        printf("Player: %i      Computer: %i\n", p_score, pc_score);

        //Check for endgame conditions
        int remaining_rounds = number_of_rounds - 1 -i;
        if (p_score - pc_score > remaining_rounds)
        {
            printf("You have won this game!\n");
            break;
        } else if (pc_score - p_score> remaining_rounds)
        {
            printf("The computer has won this game!\n");
            break;
        } else if (p_score == pc_score && i == number_of_rounds - 1)
        {
            printf("We have a draw!\n");
            break;
        } else if (p_score > pc_score && i == number_of_rounds - 1)
        {
            printf("You have won this game!\n");
            break;
        } else if (i ==  number_of_rounds - 1)
        {
            printf("The computer has won this game!\n");
            break;
        }
        //system("clear");
    }
}

// Choose ROCK, PAPER, SCISSORS randomly
char pc_choose_random(void)
{
    int max_value = 2, min_value = 0;
    char error = 'e';

    int choice = rand() % (max_value - min_value + 1) + min_value;

    switch(choice)
    {
        case ROCK_VALUE:
            return ROCK;
            break;
        case PAPER_VALUE:
            return PAPER;
            break;
        case SCISSORS_VALUE:
            return SCISSORS;
            break;
    }

    return error;
}