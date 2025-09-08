// Simulate the classic game rock, paper, scissors

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define EMPTY '\0'
#define ROCK 'r'
#define PAPER 'p'
#define SCISSORS 's'
#define ROCK_VALUE 0
#define PAPER_VALUE 1
#define SCISSORS_VALUE 2
#define DEFAULT_STORE ' '
#define EASY 'e'
#define PCT_RAND_EASY 60
#define PCT_RAND_HARD 15
#define NORMAL 'n'
#define HARD 'h'
#define EXPERT 'x'
#define P_PREV_CHOICES 7

// Player
int p_score = 0;
bool is_p_win = false;
char p_choice;
char prev_choices[P_PREV_CHOICES];

// Computer
int pc_score = 0;
bool is_pc_win = false;
char pc_choice;
char pc_choose_normal(void);
char pc_choose_easy(void);
char pc_choose_lose_CR(void);
char pc_choose_hard(char [], int);
char pc_choose_win_frequency(char [], int);
char most_frequent_recent_choice(char, char, char, int, int, int, char []);

// Game
char mode;
void print_mode(char);

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
bool is_input_match(string, string);
void set_mode(void);
void set_prev_choices(int);
char get_player_choice(void);
int get_choice_value(char);
void update_prev_choices(char [], int, char);
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
    set_mode();
    printf("Okay, we're going to play %i rounds ", number_of_rounds);
    print_mode(mode);
    set_prev_choices(P_PREV_CHOICES);
    
    // Seed the random generator for different sequences of random output every time we run the program
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
bool is_input_match(string input_string, string match_string)
{
    // Check if input_string is NULL or match_string is NULL to safeguard segmentation fault
    if (!input_string || !match_string)
    {
        return false;
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
            return false;
        } 
    }

    // Check if input_string is an empty line
    return length_input_string > 0;
}

void print_mode(char mode)
{
    if (mode == EASY)
    {
        printf("in easy mode.\n");
    }
    else if (mode == NORMAL)
    {
        printf("in normal mode.\n");
    }
    else if (mode == HARD)
    {
        printf("in hard mode.\n");
    }
    else if (mode == EXPERT)
    {
        printf("in expert mode.\n");
    }
}

void set_mode(void)
{
    mode = DEFAULT_STORE;

    do
    {
        // Strict input handling
        mode = get_char("Pick amongst easy(e), normal(n), hard(h), or expert(x): ");

        // Safeguard against non-readable lines
        if (mode == CHAR_MAX)
        {
            if (feof(stdin))
            {
                printf("\nNo input (EOF). Exiting!\n");
                exit(0);
            }

            if (ferror(stdin))
            {
                perror("stdin");
                clearerr(stdin);
                continue;
            }
        }

        if (mode == 'e' || mode == 'n' || mode == 'h' || mode == 'x')
        {
            return;
        }

        printf("Please enter a valid option!\n");
    } while (mode != 'e' && mode != 'n' && mode != 'h' && mode != 'x');
}

// Set the initial state for the player's last CHOICES_LENGTH choices
void set_prev_choices(int choices_length)
{
    for (int i = 0; i < choices_length; i++)
    {
        prev_choices[i] = EMPTY;   
    }
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

    update_prev_choices(prev_choices, P_PREV_CHOICES, p_choice);
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
        // At this time, pc_choice, p_choice, is_p_win, is_pc_win describe prev round
        // Computer chooses based on mode except for first round
        if (i == 0 || mode == NORMAL)
        {
            pc_choice = pc_choose_normal();
        }
        else if (mode == EASY)
        {
            pc_choice = pc_choose_easy();
        }
        else if (mode == HARD)
        {
            pc_choice = pc_choose_hard(prev_choices, P_PREV_CHOICES);
        }
        else
        {
            pc_choice = pc_choose_normal();
        }

        p_choice = get_player_choice();

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
char pc_choose_normal(void)
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

// Choose ROCK, PAPER, SCISSORS randomly for 60% of the time, while pick the losing choice based on CR 
// for the rest of it
char pc_choose_easy(void)
{
    // Use probability to pick lose intentionally or randomly
    int roll = rand() % 100;
    
    // Carry out the pc_choose_normal or pc_choose_lose_CR
    if (roll < PCT_RAND_EASY)
    {
        return pc_choose_normal();
    }
        
    return pc_choose_lose_CR();
}

// Helper function to pick the losing choice assuming the player's conditional response: win-keep lose-shift
char pc_choose_lose_CR(void)
{
    // General behavior of a person: win or tie ---> keep choice, 
    // lose ---> shift to choice that beats opponent's prev choice
    if (is_p_win || is_pc_win)
    {
        return pc_choice;
    }
    
    switch(p_choice)
    {
        case ROCK:
            return SCISSORS;
        case PAPER:
            return ROCK;
        default:
            return PAPER;
    }
}

// Choose rock, paper, scissors randomly for 15% of the time, while choose the winning choice based on frequency
// for the rest of it 
char pc_choose_hard(char prev_choices[], int prev_choices_length)
{
    // Use probability to pick random or win based on frequency
    int roll = rand() % 100;

    if (roll < PCT_RAND_HARD)
    {
        return pc_choose_normal();
    }
    
    return pc_choose_win_frequency(prev_choices, prev_choices_length);
}

// Choose the winning choice based on frequency
char pc_choose_win_frequency(char prev_choices[], int prev_choices_length)
{
    // Iterate through the array to keep track of the number of rock, paper, scissors choice made, as well as
    // their order in terms of recency
    int count_rock = 0, count_paper = 0, count_scissors = 0;
    char recency[3] = {'\0', '\0', '\0'};

    for (int i = prev_choices_length - 1; i >= 0; i--)
    {
        char choice = prev_choices[i];

        if (choice == EMPTY)
        {
            continue;
        }

        if (recency[0] != choice)
        {
            recency[2] = recency[1];
            recency[1] = recency[0];
            recency[0] = choice;
        }

        switch(choice)
        {
            case ROCK:
                count_rock += 1;
                break;
            case PAPER:
                count_paper += 1;
                break;
            case SCISSORS:
                count_scissors += 1;
                break;
        }
    }

    char frequent_recent_choice = most_frequent_recent_choice(ROCK, PAPER, SCISSORS, count_rock, count_paper, count_scissors, recency);

    switch(frequent_recent_choice)
    {
        case ROCK:
            return PAPER;
            break;
        case PAPER:
            return SCISSORS;
            break;
        case SCISSORS:
            return ROCK;
            break;
    }

    return '\0';
}

// Return the most frequent recent choice
char most_frequent_recent_choice(char choice1, char choice2, char choice3, int count_c1, int count_c2, int count_c3, char recency[])
{
    int count_max;

    if (count_c1 >= count_c2)
    {
        if (count_c1 >= count_c3)
        {
            count_max = count_c1;
        }
        else
        {
            count_max = count_c3;
        }
    }
    else if (count_c2 >= count_c3)
    {
        count_max = count_c2;
    }
    else
    {
        count_max = count_c3;
    }

    if (count_max == count_c1 && count_max == count_c2 && count_max == count_c3)
    {
        return recency[0];
    }
    else if (count_max == count_c1 && count_max == count_c2)
    {
        // Pick the tied choice with the most recent occurence
        return ((recency[0] == choice1 || recency[0] == choice2)? recency[0] : recency[1]);
    }
    else if (count_max == count_c1 && count_max == count_c3)
    {
        return ((recency[0] == choice1 || recency[0] == choice3)? recency[0] : recency[1]);
    }
    else if (count_max == count_c2 && count_max == count_c3)
    {
        return (recency[0] == choice2 || recency[0] == choice3)? recency[0] : recency[1];
    }
    else if (count_max == count_c1)
    {
        return choice1;
    }
    else if (count_max == count_c2)
    {
        return choice2;
    }
    else
    {
        return choice3;
    }
}

// Push P_CHOICE, the most current choice to the front of PREV_CHOICES 
void update_prev_choices(char prev_choices[], int prev_choices_length, char p_choice)
{
    for (int i = prev_choices_length - 1; i >= 1; i--)
    {
        prev_choices[i] = prev_choices[i - 1];
    }
    prev_choices[0] = p_choice;
}