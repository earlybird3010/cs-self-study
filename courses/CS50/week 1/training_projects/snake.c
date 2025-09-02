#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Game macros
#define WAITING_TIME 2
#define WELCOME_LENGTH 58
#define WELCOME_WIDTH 7
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
#define TIMEOUT 600
char welcome_grid[WELCOME_WIDTH][WELCOME_LENGTH];
int ground[BOUNDARY_WIDTH][BOUNDARY_LENGTH];

// Snake
int snake_coordinates[(BOUNDARY_LENGTH - 2) * (BOUNDARY_WIDTH - 2)][2];
int prev_tail_coordinate[2];
int snake_length = 0;
void set_snake(void);
void next_cell(int, int, int, int *, int *);
void snake_move(int);
int is_snake_collide_next(int);
void snake_eat(void);

// Fruit
int is_fruit_available = 0; 
int fruit_coordinate[2];
void set_fruit(void);
int is_fruit_on_top_snake(void);

// Screen display
void curses_print_welcome(void);
void set_welcome_grid(void);
void fill_grid_row(int, int[], size_t, char);

void start_game(void);

// Maze display
void set_ground(void);
void curses_display_ground(void);

int main(void)
{
    // initialize the curses library
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    // Display welcome screen
    set_welcome_grid();
    curses_print_welcome();
    refresh();

    int option;
    printw("\nDo you want to start a new game? (y/n)\n");
    refresh();
    option = getch();

    if (option == 'y') 
    {
        srand(time(NULL)); // Seed the random number generator
        erase();
        timeout(TIMEOUT);
        start_game();
    }
    else
    {
        printw("SEE YOU NEXT TIME!\n");
        refresh();
        sleep(WAITING_TIME);       
    }
    endwin();

}

// Update the image of the welcome grid for curses's subroutines
void curses_print_welcome(void)
{
    for (int i = 0; i < WELCOME_WIDTH; i++)
    {
        for (int j = 0; j < WELCOME_LENGTH; j++)
        {
            char current_point = welcome_grid[i][j];
            mvaddch(i, j, current_point);
        }
    }
}

// Set welcome grid for ncurses to display welcome screen
void set_welcome_grid(void)
{
    char white = 'W';
    char black = 'B';

    int zero_line[] = {2, 8, 2, 2, 6, 2, 4, 6, 4, 2, 6, 2, 2, 10};
    int first_line[] = {2, 10, 2, 6, 2, 2, 2, 6, 2, 2, 2, 4, 2, 4, 2, 8};
    int second_line[] = {2, 10, 4, 4, 2, 2, 2, 6, 2, 2, 2, 2, 2, 6, 2, 8};
    int third_line[] = {8, 4, 2, 2, 2, 2, 2, 2, 10, 2, 4, 8, 8, 2};
    int fourth_line[] = {8, 2, 2, 2, 4, 4, 2, 2, 6, 2, 2, 2, 2, 2, 6, 2, 8};
    int fifth_line[] = {8, 2, 2, 2, 6, 2, 2, 2, 6, 2, 2, 2, 4, 2, 4, 2, 8};
    int sixth_line[] = {8, 4, 2, 6, 2, 2, 2, 6, 2, 2, 2, 6, 2, 2, 10};

    size_t zero_length = sizeof(zero_line) / sizeof(zero_line[0]);
    size_t first_length = sizeof(first_line) / sizeof(first_line[0]);
    size_t second_length = sizeof(second_line) / sizeof(second_line[0]);
    size_t third_length = sizeof(third_line) / sizeof(third_line[0]);
    size_t fourth_length = sizeof(fourth_line) / sizeof(fourth_line[0]);
    size_t fifth_length = sizeof(fifth_line) / sizeof(fifth_line[0]);
    size_t sixth_length = sizeof(sixth_line) / sizeof(sixth_line[0]);

    fill_grid_row(0, zero_line, zero_length, white);
    fill_grid_row(1, first_line, first_length, black);
    fill_grid_row(2, second_line, second_length, black);
    fill_grid_row(3, third_line, third_length, black);
    fill_grid_row(4, fourth_line, fourth_length, white);
    fill_grid_row(5, fifth_line, fifth_length, white);
    fill_grid_row(6, sixth_line, sixth_length, black);
}

// Print two different characters on screen continuously based on START, based on the idea of mario.c from CS50
void fill_grid_row(int row_idx, int nums[], size_t nums_length, char start)
{ 
    char symbol = (start == 'W')? EMPTY_SYMBOL : WALL_SYMBOL;
    int col_idx = 0;
    
    for (int i = 0; i < nums_length; i++)
    {
        int repetitions = nums[i];

        
        for (int j = 0; j < repetitions; j++)
        {
            welcome_grid[row_idx][col_idx] = symbol;
            col_idx += 1;
        }

        symbol = (symbol == EMPTY_SYMBOL)? WALL_SYMBOL : EMPTY_SYMBOL;
    } 
}

// Start game
void start_game(void)
{
    set_ground();
    set_snake();
    int direction = ' ';

    while (1)
    {
        if (!is_fruit_available)
        {
            set_fruit();
        }

        curses_display_ground();
        refresh();

        int prev_direction = direction;
        direction = getch();

        // Continuous movement
        if (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd')
        {
            direction = prev_direction;
        }

        // Collision detection
        if (is_snake_collide_next(direction))
        {
            curses_display_ground();
            int next_row, next_column;
            next_cell(direction, snake_coordinates[0][0], snake_coordinates[0][1], &next_row, &next_column);
            mvaddch(next_row, next_column, SNAKE_SYMBOL);
            mvaddch(snake_coordinates[snake_length - 1][0], snake_coordinates[snake_length - 1][1], EMPTY_SYMBOL);
            refresh();
            sleep(WAITING_TIME);
            break;
        }

        snake_move(direction);
        snake_eat();
    }

    mvaddch(BOUNDARY_WIDTH - 1, BOUNDARY_LENGTH, '\n');
    printw("\nTOO BAD! Maybe next time!\n");
    refresh();
    sleep(WAITING_TIME);
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

// Update the image of the playing ground for curses's subroutines
void curses_display_ground(void)
{
    for (int i = 0; i < BOUNDARY_WIDTH; i++)
    {
        for (int j = 0; j < BOUNDARY_LENGTH; j++)
        {
            int current_point = ground[i][j];
            switch(current_point)
            {
                case EMPTY:
                    mvaddch(i, j, EMPTY_SYMBOL);
                    break;
                case WALL:
                    mvaddch(i, j, WALL_SYMBOL);
                    break;
                case SNAKE:
                    mvaddch(i, j, SNAKE_SYMBOL);
                    break;
                case FRUIT:
                    mvaddch(i, j, FRUIT_SYMBOL);
                    break;
            }
        }
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

// Store next cell positions to 2 variables
void next_cell(int direction, int row, int column, int *next_row, int *next_column)
{
    *next_row = row;
    *next_column = column;
    switch(direction)
    {
        case 'w':
            *next_row = row - 1;
            break;
        case 'a':
            *next_column = column - 1;
            break;
        case 's':
            *next_row = row + 1;
            break;
        case 'd':
            *next_column = column + 1;
    }
}

// Snake moves
void snake_move(int direction)
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

int is_snake_collide_next(int direction)
{
    // check for valid moves
    if (direction!='w' && direction!='a' && direction!='s' && direction!='d')
        return 0;

    int head_row = snake_coordinates[0][0];
    int head_col = snake_coordinates[0][1];

    int next_row, next_col;
    next_cell(direction, head_row, head_col, &next_row, &next_col);

    // out of bounds check
    if (next_row < 0 || next_row >= BOUNDARY_WIDTH || next_col < 0 || next_col >= BOUNDARY_LENGTH)
    {
        return 1;
    }

    // wall collision
    int is_wall_collision = (next_row == 0 || next_row == BOUNDARY_WIDTH - 1 || next_col == 0 || next_col == BOUNDARY_LENGTH - 1);

    // Fruit at the next cell?
    int is_fruit_next = is_fruit_available && next_row == fruit_coordinate[0] && next_col == fruit_coordinate[1];

    // classic rule: moving into *current* tail is OK if fruit not at next cell
    int tail_row = snake_coordinates[snake_length - 1][0];
    int tail_col = snake_coordinates[snake_length - 1][1];
    int is_tail_pass_through = (!is_fruit_next && next_row == tail_row && next_col == tail_col);

    int is_self_collision = (ground[next_row][next_col] == SNAKE) && !is_tail_pass_through;

    return is_wall_collision || is_self_collision;
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