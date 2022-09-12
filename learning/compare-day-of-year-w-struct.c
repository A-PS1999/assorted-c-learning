struct date {
    int day;
    int month;
    int year;
};

int day_of_year(struct date d) {
    int day, i;

    for (i = 1; i < d.month; i++) {
        switch(i) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                day += 31;
                break;
            case 4: case 6: case 9: case 11:
                day += 30;
                break;
            case 2:
                if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
                    day += 29;
                else
                    day += 28;
        }
    }

    return day + d.day;
}

int compare_dates(struct date d1, struct date d2) {
    int d1_day_of_year = day_of_year(d1);
    int d2_day_of_year = day_of_year(d2);

    if (d1_day_of_year < d2_day_of_year) {
        return -1;
    } else if (d2_day_of_year > d1_day_of_year) {
        return 1;
    } else {
        return 0;
    }
}