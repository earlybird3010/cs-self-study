// Simulate the classic game rock, paper, scissors

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROCK 'r'
#define PAPER 'p'
#define SCISSORS 's'
#define ROCK_VALUE 0
#define PAPER_VALUE 1
#define SCISSORS_VALUE 2
#define DEFAULT_STORE ' '

// Player
int p_score = 0;
bool is_p_win = false;
char p_choice;

// Computer
int pc_score = 0;
bool is_pc_win = false;
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
int is_input_match(string, string);
char get_player_choice(void);
int get_choice_value(char);
void update_game(char, char);
void display_computer_choice(void);
void print_rules(char choice);
void display_result(void);

int main(void)
{
    // Display welcome screen
    print_welcome_screen();
    
    // Get number of rounds and display result
    int number_of_rounds = get_rounds_num();
    printf("Okay, we're going to play %i rounds.\n", number_of_rounds);
    
    // Seed the random generator
    srand((unsigned) time(NULL));

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

// Returns true if one of INPUT_STRING and MATCH_STRING is the prefix of the other one, ignoring the leading white spaces
int is_input_match(string input_string, string match_string)
{
    // Check if input_string is NULL or match_string is NULL to safeguard segmentation fault
    if (!input_string || !match_string)
    {
        return 0;
    }

    size_t length_match_string = strlen(match_string);

    //Removing leading whitespace characters
    while (*input_string && (isspace((unsigned char) *input_string)))
    {
        input_string++;
    }

    size_t length_input_string = strlen(input_string);

    for (size_t i = 0; i < length_input_string && i < length_match_string; i++)
    {
        char input_string_ch = input_string[i];
        char match_string_ch = match_string[i];
        if (tolower((unsigned char) input_string_ch) != tolower((unsigned char) match_string_ch))
        {
            return 0;
        } 
    }

    // Check if input_string is an empty line
    return length_input_string > 0;
}

char get_player_choice(void)
{
    char p_choice = DEFAULT_STORE;

    do
    {
        // Robust input handling
        string input_string = get_string("Pick an option amongst rock(r), paper(p), or scissors(s): ");

        // Safeguard against Ctrl + D ---> make stdin at EOF
        if (!input_string)
        {
            if (feof(stdin))
            {
                printf("\nNo input(EOF). Exiting!\n");
                exit(0);
            }

            if (ferror(stdin)) 
            { 
                perror("stdin"); 
                clearerr(stdin); 
                continue; 
            }

        }
        
        if (is_input_match(input_string, "rock"))
        {
            p_choice = ROCK;
        } else if (is_input_match(input_string, "paper"))
        {
            p_choice = PAPER;
        } else if (is_input_match(input_string, "scissors"))
        {
            p_choice = SCISSORS;
        } else
        {
            printf("Please enter r/p/s or any similar word to rock or paper or scissors.\n");
        }
    } 
    while (p_choice != ROCK && p_choice != PAPER && p_choice != SCISSORS);

    return p_choice;
}

// Get an integer number of rounds from the user
int get_rounds_num(void)
{   
    int number_of_rounds = 0;
    do
    {
        number_of_rounds = get_int("How many rounds do you want to play? ");

        // Safeguard against Ctrl + D ---> make stdin at EOF
        if (number_of_rounds == INT_MAX)
        {
            if (feof(stdin))
            {
                printf("\nNo input(EOF). Exiting!\n");
                exit(0);
            }

            if (ferror(stdin)) 
            { 
                perror("stdin"); 
                clearerr(stdin); 
                continue; 
            }
        }

        if (number_of_rounds > 0)
        {
            return number_of_rounds;
        }

        printf("Please enter a positive integer!\n");
    } 
    while (number_of_rounds <= 0);
}

// Return the corresponding value of CHOICE (r, p, or s)
int get_choice_value(char choice)
{
    switch(choice) {
        case ROCK:
            return ROCK_VALUE;
        case PAPER:
            return PAPER_VALUE;
        default:
            return SCISSORS_VALUE;
    }
}

// Update state of game when get results from 1 round of rock, paper, scissors
void update_game(char p_choice, char pc_choice)
{
    int p_choice_value = get_choice_value(p_choice), pc_choice_value = get_choice_value(pc_choice);

    is_p_win = ((p_choice_value - pc_choice_value + 3) % 3 == 1);
    is_pc_win = ((pc_choice_value - p_choice_value + 3) % 3 == 1);

    p_score += (int) is_p_win;
    pc_score += (int) is_pc_win;
}

void display_computer_choice(void)
{
    if (pc_choice == ROCK)
    {
        printf("The computer chooses ROCK!\n");
    } 
    else if (pc_choice == PAPER)
    {
        printf("The computer chooses PAPER!\n");
    } 
    else if (pc_choice == SCISSORS)
    {
        printf("The computer chooses SCISSORS!\n");
    }
}

// Print the basic rule of rock, paper, scissors
void print_rules(char winner_choice)
{
    switch(winner_choice)
    {
        case ROCK:
            printf("ROCK smashes SCISSORS!\n");
            break;
        case PAPER:
            printf("PAPER covers ROCK!\n");
            break;
        case SCISSORS:
            printf("SCISSORS cut PAPER!\n");
    }
}

// Display result of the current round
void display_result(void)
{
    if (is_p_win == is_pc_win)
    {
        printf("DRAW!\n");
        return;
    } 
    
    char winner_choice = (is_p_win) ? p_choice : pc_choice;
    print_rules(winner_choice);

    printf(is_p_win ? "YOU WIN!\n" : "YOU LOSE!\n");
}

// Start game loop until a result is obtained
void start_game(int number_of_rounds)
{
    for (int i = 0; i < number_of_rounds; i++)
    {
        p_choice = get_player_choice();
        pc_choice = pc_choose_random();
        display_computer_choice();
        update_game(p_choice, pc_choice);
        display_result();

        //Display points
        printf("Player: %i      Computer: %i\n", p_score, pc_score);

        //Check for endgame conditions
        int remaining_rounds = number_of_rounds - 1 - i;

        if (abs(p_score - pc_score) > remaining_rounds)
        {
            printf(p_score > pc_score ? "You have won this game!\n" : "The computer has won this game!\n");
            break;
        }

        if (p_score == pc_score && i == number_of_rounds - 1)
        {
            printf("We have a draw!\n");
            break;
        } 
        else if (p_score > pc_score && i == number_of_rounds - 1)
        {
            printf("You have won this game!\n");
            break;
        } 
        else if (i ==  number_of_rounds - 1)
        {
            printf("The computer has won this game!\n");
            break;
        }
    }
}

// Choose ROCK, PAPER, SCISSORS randomly
char pc_choose_random(void)
{
    switch(rand() % (SCISSORS_VALUE - ROCK_VALUE + 1) + ROCK_VALUE)
    {
        case ROCK_VALUE:
            return ROCK;
        case PAPER_VALUE:
            return PAPER;
        default:
            return SCISSORS;
    }
}
