#include <cs50.h>
#include <stdio.h>

bool is_triangle(double, double, double);

int main(int argc, string argv[])
{
    double size[3];

    for (int i = 0; i < 3; i++)
    {
        size[i] = get_int("Enter the triangle side's length: ");
    }

    if (is_triangle(size[0], size[1], size[2]))
    {
        printf("You gave valid lengths!\n");
    }
    else
    {
        printf("Oops! Your triangle cannot exist.\n");
    }
}

bool is_triangle(double x, double y, double z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }    

    if (x + y <= z || y + z <= x || x + z <= y)
    {
        return false;
    }

    return true;
}