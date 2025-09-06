
#include <cs50.h>
#include <stdio.h>

#define N 3

double get_average(int [], size_t);

int main(void)
{
    int scores[N];

    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }
    // Print average
    printf("Average: %f\n", get_average(scores, sizeof(scores) / sizeof(scores[0])));
}

double get_average(int scores[], size_t scores_len)
{
    int sum = 0;

    for (int i = 0; i < scores_len; i++)
    {
        sum += scores[i];
    }

    return (double) sum / scores_len;
}