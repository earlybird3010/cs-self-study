#include <ncurses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


// Game macros
#define WAITING_TIME 3
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
char welcome_grid[WELCOME_WIDTH][WELCOME_LENGTH];
int ground[BOUNDARY_WIDTH][BOUNDARY_LENGTH];

// Screen display
void curses_print_welcome(void);
void set_welcome_grid(void);
void fill_grid_row(int row_idx, int nums[], size_t nums_length, char start);

int main(void)
{
    set_welcome_grid();
    // initialize the curses library
    initscr();
    keypad(stdscr, TRUE);
    cbreak();

    // Display welcome screen
    // set_welcome_grid();
    curses_print_welcome();
    refresh();
    sleep(WAITING_TIME);
    endwin();
}

void print_normal_welcome(void)
{
    for (int i = 0; i < WELCOME_WIDTH; i++)
    {
        for (int j = 0; j < WELCOME_LENGTH; j++)
        {
            char current_point = welcome_grid[i][j];
            printf("%c", current_point);
        }
        printf("\n");
    }
}

// Update the image of the welcome grid for curses's subroutines
void curses_print_welcome(void)
{
    for (int i = 0; i < WELCOME_WIDTH; i++)
    {
        for (int j = 0; j < WELCOME_LENGTH; j++)
        {
            char current_point = welcome_grid[i][j];
            switch(current_point)
            {
                case EMPTY_SYMBOL:
                    mvaddch(i, j, EMPTY_SYMBOL);
                    break;
                case WALL_SYMBOL:
                    mvaddch(i, j, WALL_SYMBOL);
                    break;
            }
        }
        mvaddch(i, WELCOME_LENGTH, '\n');
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