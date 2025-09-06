// Prompts 2 players for inputs, and determine the winner based on those
// Problem: How to associate each character with their corresponding inputs => Answer: a function that returns the associated score of a letter
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_points(char);
int get_sum(string);

int main(void)
{
    // Prompt the players for inputs
    string first_input = get_string("Player 1: ");
    string second_input = get_string("Player 2: ");

    // Calculate points earned for each player
    int first_point = get_sum(first_input);
    int second_point = get_sum(second_input);

    // Announce the winner
    if (first_point > second_point)
    {
        printf("Player 1 wins!\n");
    } else if (first_point < second_point)
    {
        printf("Player 2 wins!\n");
    } else
    {
        printf("Tie!\n");
    }
}

int get_sum(string word)
{
    int sum = 0;

    for (size_t i = 0; i < strlen(word); i++)
    {
        sum += get_points(word[i]);
    }

    return sum;
}

int get_points(char c)
{
    // Normalize c
    c = tolower(c);
    if (c == 'q' || c == 'z')
    {
        return 10;
    } else if (c == 'x' || c == 'j')
    {
        return 8;
    } else if (c == 'k')
    {
        return 5;
    } else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y')
    {
        return 4;
    } else if (c == 'b' || c == 'c' || c == 'm' || c == 'p')
    {
        return 3;
    } else if (c == 'd' || c == 'g')
    {
        return 2;
    } else if (c >= 'a' && c <= 'z') {
        return 1;
    } else
    {
        return 0;
    }
}

