#include <stdio.h>

int main(int argc, char* argv[])
{
    int day;
    int month;
    int year;
    char *months[] = {"January", "February", "March", "April", "May", "June", "July",
                    "August", "September", "October", "November", "December"};

    if (argc != 2) {
        printf("Usage: print-formatted-date date\n");
        return 1;
    }

    if ((sscanf(argv[1], "%d*[-/]%d*[-/]%d", &day, &month, &year)) == 3) {
        printf("%s %d, %d", months[month-1], day, year);
    } else {
        printf("Date is not in a valid format.\n");
        printf("Date must be either in format day/month/year or day-month-year\n");
    }

    return 0;
}