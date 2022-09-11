#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool check_arg_validity(char key[]);

int main(int argc, char *argv[]) {

    char word_input[50];

    if (argc == 1 || argc >= 3) { // returns error message if inappropriate number of args provided from console
        printf("Usage: ./substitution key");
        return 1;
    }

    if (!check_arg_validity(argv[1])) { // returns 1 (error) if key not valid
        return 1;
    }

    printf("Plaintext: ");
    fgets(word_input, 50, stdin);

    printf("Ciphertext: ");

    for (int i=0; word_input[i]; i++) { // iterate sentence
        if (isalpha((unsigned char)word_input[i]) != 0) { // if current char of sentence is letter
            if (islower((unsigned char)word_input[i])) { // if lowercase, replace with lowercase from key
                word_input[i] = tolower(argv[1][word_input[i] - 'a']);
            } else { // else replace with uppercase from key
                word_input[i] = toupper(argv[1][word_input[i] - 'A']);
            }
        }
    }

    printf("%s", word_input);

    printf("\n");
    return 0;
}

bool check_arg_validity(char key[]) {
    int alphabet_count[26] = {0};
    
    if (strlen(key) != 26) { // returns false with error message if key not exactly 26 letters
        printf("Key must contain 26 characters");
        return false;
    }

    while (*key) { // iterate key
        if (!isalpha((int)*key)) { // if current key value not letter, return false with error message
            printf("Key must only contain letters");
            return false;
        }

        alphabet_count[toupper(*key) - 'A']++; // increment alphabet count to have record of how many of each letter
        key++; // increment key to get through while loop
    }

    for (int i = 0; i < 26; i++) { // iterate alphabet_count
        if (alphabet_count[i] > 1) { // aka if a letter shows up more than once, return false with message
            printf("Each letter in the key must appear only once");
            return false;
        }
    }

    return true; // if no conditions fire, return true
}