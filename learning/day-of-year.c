#include <stdio.h>

int day_of_year(int day, int month, int year) {

    int i;

    for (i = 1; i < month; i++) {
        switch(i) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                day += 31;
                break;
            case 4: case 6: case 9: case 11:
                day += 30;
                break;
            case 2:
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                    day += 29;
                else
                    day += 28;
        }
    }
    return day;
}

int main(void)
{
    int day, month, year;

    printf("Insert a date in this format without brackets (day month year): ");
    scanf("%d %d %d", &day, &month, &year);

    printf("Day of year: %d", day_of_year(day, month, year));

    return 0;
}