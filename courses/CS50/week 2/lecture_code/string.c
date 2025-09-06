#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Input: ");
    printf("Output: ");

    for (size_t i = 0, s_len = strlen(s); i < s_len; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}