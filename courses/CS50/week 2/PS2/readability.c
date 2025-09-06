// Return the approximate grade level needed to read a book
/*
Test description:
./readability
Text: input something here
Grade output
*/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_words(string);
int count_letters(string);
int count_sentences(string);

int main(void)
{
    // Text prompt
    string text = get_string("Text: ");
        
    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate the reading grade
    double L = letters * 1.0 / words * 100;
    double S = sentences * 1.0 / words * 100;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int grade_result = (int) round(index);

    // Print result to console
    if (grade_result < 1)
    {
        printf("Before Grade 1.\n");
    } else if (grade_result >= 16)
    {
        printf("Grade 16+\n");
    } else
    {
        printf("Grade %i\n", grade_result);
    }
}

int count_words(string text)
{
    int word_count = 0;

    // Number of words is the number of time we encounter a new word, i.e, move from ' ' to a nonspace character
    char prev_char = ' ';
    char cur_char = ' ';
    size_t text_length = strlen(text);

    for (size_t i = 0; i < text_length; i++)
    {
        cur_char = text[i];
        
        if (isspace(prev_char) && !isspace(cur_char))
        {
            word_count++;
        }
        prev_char = cur_char;
    }

    return word_count;
}

int count_letters(string text)
{
    int letter_count = 0;
    size_t text_length = strlen(text);

    for (size_t i = 0; i < text_length; i++)
    { 
        int cur_char = tolower(text[i]);

        if (cur_char >= 'a' && cur_char <= 'z')
        {
            letter_count += 1;
        }
    }

    return letter_count;
}

int count_sentences(string text)
{
    int sentence_count = 0;

    // Number of sentence is the number of time we encounter a non 'a-z' character from an 'a-z' character
    char prev_char = ' ';
    char cur_char = ' ';
    size_t text_length = strlen(text);

    for (size_t i = 0; i < text_length; i++)
    {
        cur_char = tolower(text[i]);
        
        if (prev_char >= 'a' && prev_char <= 'z' && 
            (cur_char == '!' || cur_char == '.' || cur_char == '?'))
        {
            sentence_count++;
        }
        prev_char = cur_char;
    }

    return sentence_count;    
}