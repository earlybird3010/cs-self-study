#include <stdio.h>
#include <cs50.h>

void print_larger(double x, double y) {
    if (x < y) {
        printf("%f is less than %f", x, y);
    } else if (x > y) {
        printf("%f is greater than %f", x, y);
    } else {
        printf("%f is equal to %f", x, y);
    }
}


int main(void) {
    double x = get_double("Insert x: ");
    double y = get_double("Insert y: ");
    print_larger(x, y);
}

for ()