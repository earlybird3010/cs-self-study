#include <stdio.h>
#include <string.h>

const char *cow = 
"\\    ^__^\n"
" \\   (oo)\\_______\n"
"     (__)\\       )\\/\\\n"
"         ||----w |\n"
"         ||     ||\n";

const char *duck = 
"\\\n"
" \\\n"
"  \\ >()_\n"
"     (__)__ _\n";

char *duck_first_line = "\\\n";
char *duck_second_line = " \\\n";
char *duck_third_line = "  \\ >()_\n";
char *duck_fourth_line = "     (__)__ _\n";

char *cow_first_line = "\\    ^__^\n";
char *cow_second_line = " \\   (oo)\\_______\n";
char *cow_third_line = "     (__)\\       )\\/\\\n";
char *cow_fourth_line = "         ||----w |\n";
char *cow_fifth_line = "         ||     ||\n";

void print_cow(char *);
void print_duck(char *);
void print_shift_art(char *, unsigned int);

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 4)
    {
        printf("Usage: cowsay text\n");
        printf("Usage: cowsay -f duck text\n");
        return -1;
    }
    
    if (argc == 2)
    {
        print_cow(argv[1]);
    } else if (argc == 4)
    {
        print_duck(argv[3]);
    }
    return 0;
}

// print what the cow says together with it to the console
void print_cow(char *text)
{
    size_t text_length = strlen(text);

    printf(" ");
    for (size_t i = 0; i < text_length + 2; i++)
    {
        printf("_");
    }
    printf("\n");
    printf("< %s >\n", text);

    printf(" ");
    for (size_t i = 0; i < text_length + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    print_shift_art(cow_first_line, text_length + 3);
    print_shift_art(cow_second_line, text_length + 3);
    print_shift_art(cow_third_line, text_length + 3);
    print_shift_art(cow_fourth_line, text_length + 3);
    print_shift_art(cow_fifth_line, text_length + 3);
}

// print what the duck says together with it to the console
void print_duck(char *text)
{
    size_t text_length = strlen(text);

    printf(" ");
    for (size_t i = 0; i < text_length + 2; i++)
    {
        printf("_");
    }
    printf("\n");
    printf("< %s >\n", text);

    printf(" ");
    for (size_t i = 0; i < text_length + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    print_shift_art(duck_first_line, text_length + 3);
    print_shift_art(duck_second_line, text_length + 3);
    print_shift_art(duck_third_line, text_length + 3);
    print_shift_art(duck_fourth_line, text_length + 3);
}

// Move IMAGE STEPs steps to the right and print it
void print_shift_art(char *image, unsigned int steps)
{
    if (image == NULL)
    {
        return;
    }

    int image_length = 0;

    while(image[image_length] != '\0')
    {
        image_length++;
    }

    char dst_buffer[image_length + steps + 1];

    for (size_t i = 0; i < steps; i++)
    {
        dst_buffer[i] = ' ';
    }

    dst_buffer[steps] = '\0';

    strcat(dst_buffer, image);

    printf("%s", dst_buffer);
}

