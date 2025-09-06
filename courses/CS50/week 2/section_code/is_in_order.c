// Return true if a lowercasestring's characters are in alphabetical order. 
// If yes, print "Yes". If no, print "No".

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_in_order(string);

int main(int argc, char *argv[])
{
    // Get a user's input
    string input = get_string("Input a string: ");
    for (int i = 0; i < strlen(input); i++)
    {
        input[i] = tolower(input[i]);
    }

    // Print result
    bool result = is_in_order(input);

    if (result)
    {
        printf("Yay!%s's characters are in alphabetical order.\n", input);
    }
    else
    {
        printf("Oops!%s's characters are not in alphabetical order.\n", input);
    }
}

// Return true iff the characters in s are in alphabetical order
bool is_in_order(string s)
{
    size_t s_len = strlen(s);
    char prev_char = '\0';

    for (size_t i = 0; i < s_len; i++)
    {
        char current_char = s[i];
        if (isalpha(current_char) && current_char < prev_char)
        {
            return false;
        }
        
        prev_char = isalpha(current_char)? current_char : prev_char; 

    }

    return true;
}