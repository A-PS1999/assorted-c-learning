#ifndef LINE_H
#define LINE_H

// clears current line
void clear_line(void);

/*
    Adds word to end of current line. 
    If this is not first word in this line, put space before current word.
*/
void add_word(const char *word);

// Returns number of characters left in current line
int space_remaining(void);

// writes current line with justification
void write_line(void);

// Writes current line without justification. If line is empty, does nothing.
void flush_line(void);

#endif