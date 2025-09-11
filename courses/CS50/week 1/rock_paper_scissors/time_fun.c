#include <stdio.h>
#include <time.h>
#include <stdint.h>
int main(void)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    int year = t -> tm_year + 1900;
    int month = t -> tm_mon + 1;
    int day = t -> tm_mday;

    printf("Current hours: %02d", t -> tm_hour);

    printf("Current date: %d-%02d-%02d\n", year, month, day);

    FILE *file = fopen("example_history.csv", "a");
    if (file)
    {
        fprintf(file, "%d-%02d-%02d\n", year, month, day);
    }
    fclose(file);
}