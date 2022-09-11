void censor(char *str) {

    char *ch = str;
    
    while (ch+2 != '\0') {
        if (*ch == 'f' && *(ch+1) == 'o' && *(ch+2) == 'o') {
            *ch = *(ch+1) = *(ch+2) = 'x';
        }
        ch++;
    }
}