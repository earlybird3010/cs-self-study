#include <cs50.h>
#include <stdio.h>

// Calculate the sum of digits of a positive integer n
long sum_digits(long n)
{
    if (n < 0)
    {
        return -1;
    }

    long sum = 0;

    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Calculate the sum of digits of those modified digits
// in Luhn's algorithm
long sum_digits_modified(long n)
{
    bool is_include = false;
    long sum = 0;
    long current_digit = -1;

    while (n > 0)
    {
        current_digit = n % 10;
        if (is_include)
        {
            sum += sum_digits(current_digit * 2);
        }
        is_include = !is_include;
        n /= 10;
    }

    return sum;
}

// Calculate the sum of unmodified digits of n
long sum_digits_unmodified(long n)
{
    long sum = 0;
    bool is_include = true;
    long current_digit = -1;

    while (n > 0)
    {
        current_digit = n % 10;

        if (is_include)
        {
            sum += current_digit;
        }

        is_include = !is_include;
        n /= 10;
    }

    return sum;
}

// Check if a numeric card satisfies the Luhn's Algorithm
bool is_luhn_satisfied(long n)
{
    long total_sum = sum_digits_modified(n) + sum_digits_unmodified(n);
    if (total_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Get the first two digits of a number greater than or equal to 10
long get_first_two(long n)
{
    if (n < 10)
    {
        return -1;
    }

    if (n < 100)
    {
        return n;
    }

    while (n > 100)
    {
        n /= 10;
    }
    return n;
}

// Return the possible type of a numeric card based on
// the first two number and number of digits of the card
string get_type(long n)
{
    long digits_count = 0;
    long temp_n = n;

    while (temp_n > 0)
    {
        digits_count += 1;
        temp_n /= 10;
    }

    long first_two_digits = get_first_two(n);
    bool is_valid_luhn = is_luhn_satisfied(n);

    if (!is_valid_luhn)
    {
        return "INVALID\n";
    }

    if (digits_count == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        return "AMEX\n";
    }
    else if (digits_count == 16 && first_two_digits >= 51 && first_two_digits <= 55)
    {
        return "MASTERCARD\n";
    }
    else if ((digits_count == 13 || digits_count == 16) && first_two_digits >= 40 &&
             first_two_digits <= 49)
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}

int main(int argc, string argv[])
{
    long card_number = get_long("Number: ");
    printf("%s", get_type(card_number));
}
