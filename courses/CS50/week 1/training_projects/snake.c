#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Maze
#define BOUNDARY_LENGTH 30
#define BOUNDARY_WIDTH 15
#define EMPTY 0
#define EMPTY_SYMBOL ' '
#define WALL 1
#define WALL_SYMBOL '#'
#define SNAKE 2
#define SNAKE_SYMBOL '*'
#define FRUIT 3
#define FRUIT_SYMBOL '@'
int ground[BOUNDARY_WIDTH][BOUNDARY_LENGTH];

// Snake
int snake_coordinates[(BOUNDARY_LENGTH - 2) * (BOUNDARY_WIDTH - 2)][2];
int prev_tail_coordinate[2];
int snake_length = 0;
void set_snake(void);
void snake_move(char direction);
int is_snake_collide(void);
void snake_eat(void);

// Fruit
int is_fruit_available = 0; 
int fruit_coordinate[2];
void set_fruit(void);
int is_fruit_on_top_snake(void);

// Screen display
void print_welcome(void);
void print_alternate(int[], size_t, char start);

void start_game(void);

// Maze display
void set_ground(void);
void display_ground(void);

int main(void)
{
    // Display welcome screen
    print_welcome();

    char option;
    printf("Do you want to start a new game? (y/n)\n");
    scanf("%c", &option);
    if (option == 'y') 
    {
        srand(time(NULL)); // Seed the random number generator
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
    char symbol = (start == 'W')? EMPTY_SYMBOL : WALL_SYMBOL;
    
    for (int i = 0; i < nums_length; i++)
    {
        int repetitions = nums[i];

        
        for (int j = 0; j < repetitions; j++)
        {
            printf("%c", symbol);
        }

        symbol = (symbol == EMPTY_SYMBOL)? WALL_SYMBOL : EMPTY_SYMBOL;
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
        if (!is_fruit_available)
        {
            set_fruit();
        }

        system("clear");
        display_ground();
        printf("Enter a direction:");
        scanf(" %c", &direction);

        snake_move(direction);
        snake_eat();
    }

    display_ground();
    printf("TOO BAD! Maybe next time!\n");
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
                ground[i][j] = WALL;
            }
            else
            {
                ground[i][j] = EMPTY;
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
            int current_point = ground[i][j];
            switch(current_point)
            {
                case EMPTY:
                    printf("%c", EMPTY_SYMBOL);
                    break;
                case WALL:
                    printf("%c", WALL_SYMBOL);
                    break;
                case SNAKE:
                    printf("%c", SNAKE_SYMBOL);
                    break;
                case FRUIT:
                    printf("%c", FRUIT_SYMBOL);
                    break;
            }
        }
        printf("\n");
    }
}

// Set position for snake prior to the game
void set_snake(void)
{
    int min_x = 1;
    int max_x = BOUNDARY_WIDTH - 2;
    int min_y = 1;
    int max_y = BOUNDARY_LENGTH - 2;

    // Generate a random integer point within the specified range
    int random_x = (rand() % (max_x - min_x + 1)) + min_x;
    int random_y = (rand() % (max_y - min_y + 1)) + min_y;
    snake_coordinates[snake_length][0] = random_x;
    snake_coordinates[snake_length][1] = random_y;
    snake_length += 1;

    // Snake occupies a point on the ground
    ground[random_x][random_y] = SNAKE; 
}

// Snake moves
void snake_move(char direction)
{   
    int tail_x = snake_coordinates[snake_length - 1][0];
    int tail_y = snake_coordinates[snake_length - 1][1];
    prev_tail_coordinate[0] = tail_x;
    prev_tail_coordinate[1] = tail_y;

    ground[tail_x][tail_y] = EMPTY;

    for (int i = snake_length - 1; i >= 1; i--)
    {
        snake_coordinates[i][0] = snake_coordinates[i - 1][0];
        snake_coordinates[i][1] = snake_coordinates[i - 1][1];
    }
    switch (direction)
    {
        case 'w':
            snake_coordinates[0][0] -= 1;
            break;
        case 'a':
            snake_coordinates[0][1] -= 1;
            break;
        case 'd':
            snake_coordinates[0][1] += 1;
            break;
        case 's':
            snake_coordinates[0][0] += 1;
            break;
    }

    int head_x = snake_coordinates[0][0];
    int head_y = snake_coordinates[0][1];


    ground[head_x][head_y] = SNAKE;
}

int is_snake_collide(void)
{
    int head_x = snake_coordinates[0][0];
    int head_y = snake_coordinates[0][1];

    for (int i = 1; i < snake_length; i++)
    {
        int body_x = snake_coordinates[i][0];
        int body_y = snake_coordinates[i][1];
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

// Set fruit in maze if there is no fruit
void set_fruit(void)
{
    is_fruit_available = 1;
    int min_x = 1;
    int max_x = BOUNDARY_WIDTH - 2;
    int min_y = 1;
    int max_y = BOUNDARY_LENGTH - 2;

    // Generate a random integer point within the specified range
    int random_x = (rand() % (max_x - min_x + 1)) + min_x;
    int random_y = (rand() % (max_y - min_y + 1)) + min_y;
    fruit_coordinate[0] = random_x;
    fruit_coordinate[1] = random_y;

    // Make sure fruit doesn't lie on top of snake
    while (1)
    {
        if (is_fruit_on_top_snake())
        {
            fruit_coordinate[0] = (rand() % (max_x - min_x + 1)) + min_x;
            fruit_coordinate[1] = (rand() % (max_y - min_y + 1)) + min_y;
        }
        else
        {
            break;
        }
    }

    // Fruit available in maze
    ground[fruit_coordinate[0]][fruit_coordinate[1]] = FRUIT;
}

// Check if fruit is on top of snake
int is_fruit_on_top_snake(void)
{
    int is_on_top = 0;

    for (int i = 0; i < snake_length; i++)
    {
        int snake_x = snake_coordinates[i][0];
        int snake_y = snake_coordinates[i][1];
        if (snake_x == fruit_coordinate[0] && snake_y == fruit_coordinate[1])
        {
            is_on_top = 1;
        }
    }

    return is_fruit_available && is_on_top;
}

// Snake eats fruit
void snake_eat(void)
{
    int snake_head_x = snake_coordinates[0][0];
    int snake_head_y = snake_coordinates[0][1];
    int fruit_x = fruit_coordinate[0];
    int fruit_y = fruit_coordinate[1];
    if (is_fruit_available && snake_head_x == fruit_x && snake_head_y == fruit_y)
    {
        snake_length += 1;
        snake_coordinates[snake_length - 1][0] = prev_tail_coordinate[0];
        snake_coordinates[snake_length - 1][1] = prev_tail_coordinate[1];
        ground[prev_tail_coordinate[0]][prev_tail_coordinate[1]] = SNAKE;
        is_fruit_available = 0;
    }
}