#include <stdio.h>
#include <stdbool.h>

bool isVowel(char ch);

int main(void) {

    int count = 1;
    
    for (char firstLetter = 'b'; firstLetter <= 'z'; ++firstLetter) {
        if (isVowel(firstLetter)) continue;
        for (char secondLetter = 'a'; secondLetter <= 'z'; ++secondLetter) {
            if (!isVowel(secondLetter)) continue;
            for (char thirdLetter = 'b'; thirdLetter <= 'z'; ++thirdLetter) {
                if (isVowel(thirdLetter)) continue;
                printf("%d %c%c%c\n ", count, firstLetter, secondLetter, thirdLetter);
                count++;
            }
        }
    }

    return 0;
}

bool isVowel(char ch) {
    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
            break;
        default:
            return false;
            break;
    }
}