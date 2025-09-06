#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");

    for (size_t i = 0, s_len = strlen(s); i < s_len; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}