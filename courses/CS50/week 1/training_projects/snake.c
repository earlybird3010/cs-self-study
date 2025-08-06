#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Maze
#define BOUNDARY_LENGTH 30
#define BOUNDARY_WIDTH 15
int ground[BOUNDARY_WIDTH][BOUNDARY_LENGTH];

// Snake
int snake_coordinates[(BOUNDARY_LENGTH - 2) * (BOUNDARY_WIDTH - 2)][2];
int snake_length = 0; 

void print_welcome(void);
void print_alternate(int[], size_t, char start);

void start_game(void);

void set_ground(void);
void display_ground(void);

void set_snake(void);
void snake_move(char direction);
int is_snake_collide(void);

int main(void)
{
    // Display welcome screen
    print_welcome();

    char option;
    printf("Do you want to start a new game? (y/n)\n");
    scanf("%c", &option);
    if (option == 'y') 
    {
        start_game();
    }
    else
    {
        printf("SEE YOU NEXT TIME!\n");       
    }

}

// Print open message to screen
void print_welcome(void)
{
    char white = 'W';
    char black = 'B';

    int first_line[] = {2, 8, 2, 2, 6, 2, 4, 6, 4, 2, 6, 2, 2, 10};
    int second_line[] = {2, 10, 2, 6, 2, 2, 2, 6, 2, 2, 2, 4, 2, 4, 2, 8};
    int third_line[] = {2, 10, 4, 4, 2, 2, 2, 6, 2, 2, 2, 2, 2, 6, 2, 8};
    int fourth_line[] = {8, 4, 2, 2, 2, 2, 2, 2, 10, 2, 4, 8, 8, 2};
    int fifth_line[] = {8, 2, 2, 2, 4, 4, 2, 2, 6, 2, 2, 2, 2, 2, 6, 2, 8};
    int sixth_line[] = {8, 2, 2, 2, 6, 2, 2, 2, 6, 2, 2, 2, 4, 2, 4, 2, 8};
    int seventh_line[] = {8, 4, 2, 6, 2, 2, 2, 6, 2, 2, 2, 6, 2, 2, 10};

    size_t first_length = sizeof(first_line) / sizeof(first_line[0]);
    size_t second_length = sizeof(second_line) / sizeof(second_line[0]);
    size_t third_length = sizeof(third_line) / sizeof(third_line[0]);
    size_t fourth_length = sizeof(fourth_line) / sizeof(fourth_line[0]);
    size_t fifth_length = sizeof(fifth_line) / sizeof(fifth_line[0]);
    size_t sixth_length = sizeof(sixth_line) / sizeof(sixth_line[0]);
    size_t seventh_length = sizeof(seventh_line) / sizeof(seventh_line[0]);

    print_alternate(first_line, first_length, white);
    print_alternate(second_line, second_length, black);
    print_alternate(third_line, third_length, black);
    print_alternate(fourth_line, fourth_length, black);
    print_alternate(fifth_line, fifth_length, white);
    print_alternate(sixth_line, sixth_length, white);
    print_alternate(seventh_line, seventh_length, black);
}

// Print two different characters on screen continuously based on START, based on the idea of mario.c from CS50
void print_alternate(int nums[], size_t nums_length, char start)
{ 
    char symbol = (start == 'W')? ' ' : '*';
    
    for (int i = 0; i < nums_length; i++)
    {
        int repetitions = nums[i];

        
        for (int j = 0; j < repetitions; j++)
        {
            printf("%c", symbol);
        }

        symbol = (symbol == ' ')? '*' : ' ';
    } 
    printf("\n");
}

// Start game
void start_game(void)
{
    set_ground();
    set_snake();
    char direction = ' ';

    while (!is_snake_collide())
    {
        display_ground();
        printf("Enter a direction:");
        scanf(" %c", &direction);
        snake_move(direction);
    }

    display_ground();
    printf("TOO BAD! Maybe next time!");
}

// Set the playing ground before the game
void set_ground(void)
{
    for (int i = 0; i < BOUNDARY_WIDTH; i++) 
    {
        for (int j = 0; j < BOUNDARY_LENGTH; j++)
        {
            if (i == 0 || j == 0 || i == BOUNDARY_WIDTH - 1 || j == BOUNDARY_LENGTH - 1)
            {
                ground[i][j] = 1;
            }
            else
            {
                ground[i][j] = 0;
            }
        }
    }
}

// Display the playing ground at any pont in the game
void display_ground(void)
{
    for (int i = 0; i < BOUNDARY_WIDTH; i++)
    {
        for (int j = 0; j < BOUNDARY_LENGTH; j++)
        {
            if (ground[i][j] == 0)
            {
                printf(" ");
            } 
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }
}

// Set position for snake prior to the game
void set_snake(void)
{
    srand(time(NULL)); // Seed the random number generator

    int min_x = 1;
    int max_x = BOUNDARY_WIDTH - 1;
    int min_y = 1;
    int max_y = BOUNDARY_LENGTH - 1;

    // Generate a random integer point within the specified range
    int random_x = (rand() % (max_x - min_x + 1)) + min_x;
    int random_y = (rand() % (max_y - min_y + 1)) + min_y;
    snake_coordinates[snake_length][0] = random_x;
    snake_coordinates[snake_length][1] = random_y;
    snake_length += 1;

    // Snake occupies a point on the ground
    ground[random_x][random_y] = 1; 
}

// Snake moves
void snake_move(char direction)
{   
    int tail_x = snake_coordinates[snake_length - 1][0];
    int tail_y = snake_coordinates[snake_length - 1][1];

    ground[tail_x][tail_y] = 0;

    for (int i = snake_length - 1; i >= 1; i--)
    {
        snake_coordinates[i][0] = snake_coordinates[i - 1][0];
        snake_coordinates[i][1] = snake_coordinates[i - 1][1];
    }
    switch (direction)
    {
        case 'W':
            snake_coordinates[0][0] -= 1;
            break;
        case 'A':
            snake_coordinates[0][1] -= 1;
            break;
        case 'D':
            snake_coordinates[0][1] += 1;
            break;
        case 'S':
            snake_coordinates[0][0] += 1;
            break;
    }

    int head_x = snake_coordinates[0][0];
    int head_y = snake_coordinates[0][1];


    ground[head_x][head_y] = 1;
}

int is_snake_collide(void)
{
    int head_x = snake_coordinates[0][0];
    int head_y = snake_coordinates[0][1];

    for (int i = 1; i < snake_length; i++)
    {
        int body_x, body_y = snake_coordinates[i][0], snake_coordinates[i][1];
        if (body_x == head_x && body_y == head_y)
        {
            return 1;
        }
    }

    if (head_x == 0 || head_x == BOUNDARY_WIDTH - 1 || head_y == 0 || head_y == BOUNDARY_LENGTH - 1)
    {
        return 1;
    }
    return 0;
}