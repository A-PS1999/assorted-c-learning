int strcmp(char *strA, char *strB)
{
    while (*strA++ == *strB++) { // equivalent to strA[i] == strB[i]
        if (!*strA) { // !*strA means, if strA terminates with '\0'
            return 0;
        }
    }
    return *(--strA) - *(--strB);
}