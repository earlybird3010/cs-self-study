#include <ncurses.h>
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

// Functions
void set_ground(void);
void curses_display_ground(void);

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    set_ground();
    curses_display_ground();
    refresh();
    int ch = getch();
    printw("%d", ch);
    getch();
    endwin();
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
        mvaddch(i, BOUNDARY_LENGTH, '\n');
    }
}