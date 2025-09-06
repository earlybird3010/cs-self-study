// Provide user with a 26-character key as a command line argument to encrypt chosen message

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate_key(string);
string encrypt(string, string);
int get_pos(char);

int main(int argc, string argv[])
{
    // Check if exactly 1 key is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;       
    }

    //Validate key
    bool is_key_valid = validate_key(argv[1]);
    if (!is_key_valid)
    {
        return 1;
    }

    //Prompt user for a string
    string org_string = get_string("plaintext: ");

    //Cipher org_string to encrypted_string
    string cipher_string = encrypt(org_string, argv[1]);

    //Print result to console
    printf("ciphertext: %s\n", cipher_string);
    return 0;
}

// Return the original position of the alphabetical char C in alphabetical table
int get_pos(char c)
{
    return tolower(c) - 'a';
}

// Return an encrypted string of ORG_STRING using KEY
string encrypt(string org_string, string key)
{
    for (size_t i = 0; i < strlen(org_string); i++)
    {
        char replace_char = org_string[i];
        bool is_upper = (isupper(replace_char)) ? true: false;

        int org_pos = get_pos(replace_char);
        
        if (isalpha(replace_char))
        {
            replace_char = key[org_pos];
        }

        if (is_upper)
        {
            replace_char = toupper(replace_char);
        }
        else
        {
            replace_char = tolower(replace_char);
        }

        org_string[i] = replace_char;
    }

    return org_string;
}

bool validate_key(string key)
{
    size_t key_length = strlen(key);

    // Check if key has 26 chars
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // Check if all chars are alphabetical
    for (size_t i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain alphabetical characters.\n");
            return false;
        }
    
    }

    // Duplication: use an array of integers to store occurences of abc...z
    char occurences[26];
    for (int i = 0; i < 26; i++)
    {
        occurences[i] = 0;
    }

    for (size_t i = 0; i < key_length; i++)
    {
        occurences[get_pos(key[i])] += 1;
        if (occurences[get_pos(key[i])] > 1)
        {
            printf("Key must contain distinct characters.\n");
            return false;
        }
    }

    return true;
}
