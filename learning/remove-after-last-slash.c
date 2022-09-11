void remove_filename(char *url) {
    char *p = url;

    while (*url) {
        if (*url == '/') {
            p = url;
        }
        url++;
    }
    *p = '\0'; 
}