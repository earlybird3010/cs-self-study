#include <stdio.h>

int main(void) 
{
    char name[100];
    int age;
    char hometown[100];
    char phone[100];

    printf("Hello! What's your name? ");
    fgets(name, sizeof(name), stdin);
    printf("How old are you? ");
    scanf("%i", &age);
    getchar();
    printf("Where is your hometown? ");
    fgets(hometown, sizeof(hometown), stdin);
    printf("What's your phone number? ");
    fgets(phone, sizeof(phone), stdin);

    printf("Name: %sAge: %i\nHometown: %sPhone: %s", name, age, hometown, phone);
} 