#include <stdio.h>

void print_vertical(int n);

int main(void) {
    for (int i = 0; i < 4; i++) {
        printf("?");
    }
    printf("\n");
    print_vertical(3);
}

void print_vertical(int n) {
    for (int i = 0; i < 3; i++) {
        printf("#\n");
    }
}