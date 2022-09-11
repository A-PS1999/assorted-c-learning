#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50
#define MSG_LEN 60

int read_line(char str[], int n);

int main(void)
{
    char reminders[MAX_REMIND][MSG_LEN+3];
    char day_str[3], msg_str[MSG_LEN+1];
    int month, day, hour, mins, i, j, num_remind = 0;

    for (;;) {
        if (num_remind == MAX_REMIND) {
            printf("No space left.\n");
            break;
        }

        printf("Enter month and day for reminder: ");
        scanf(" %2d/ %2d", &month, &day);
        if (day == 0 || month == 0) break;
        else if (day < 0 || day > 31) {
            printf("Day must be between 1 and 31!");
            while (getchar() != '\n');
            continue;
        }
        printf("\nEnter an hour and minute in 24-hour time: ");
        scanf(" %d: %d", &hour, &mins);

        sprintf(day_str, "%4.2d%4.2d %2.2d:%.2d", month, day, hour, mins);
        read_line(msg_str, MSG_LEN);

        for (i=0; i < num_remind; i++) {
            if (strcmp(day_str, reminders[i]) < 0) break;
        }
        for (j = num_remind; j > i; j--) {
            strcpy(reminders[j], reminders[j-1]);
        }

        strcpy(reminders[i], day_str);
        strcpy(reminders[i], msg_str);

        num_remind++;
    }

    printf("\nMonth Day Time Reminder\n");
    for (i=0; i < num_remind; i++) {
        printf(" %s\n", reminders[i]);
    }

    return 0;
}

int read_line(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}