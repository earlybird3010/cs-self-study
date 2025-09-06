// A program that calculates the length of a string wihout <string.h>
#include <cs50.h>
#include <stdio.h>

int get_length(string);

int main(void)
{
    string s = get_string("Text: ");
    printf("The text has %i characters.\n", get_length(s));
}

int get_length(string s)
{
    if (s == NULL)
    {
        printf("\nInvalid key!\n");
        return -1;
    }

    int s_len = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        s_len++;
    }

    return s_len;
}

