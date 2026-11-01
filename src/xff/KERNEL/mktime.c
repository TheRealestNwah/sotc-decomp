struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

typedef long time_t;

#define _SEC_IN_MINUTE 60
#define _SEC_IN_HOUR 3600
#define _SEC_IN_DAY 86400L

extern void func_00030460(struct tm *tim_p);
extern const int RO_00044DD8[12];

#define _DAYS_BEFORE_MONTH RO_00044DD8
#define _ISLEAP(y) (((y) % 4) == 0 && (((y) % 100) != 0 || (((y) + 1900) % 400) == 0))
#define _DAYS_IN_YEAR(year) (_ISLEAP(year) ? 366 : 365)

time_t mktime(struct tm *tim_p)
{
    time_t tim = 0;
    long days = 0;
    int year;

    func_00030460(tim_p);

    tim += tim_p->tm_sec + (tim_p->tm_min * _SEC_IN_MINUTE) + (tim_p->tm_hour * _SEC_IN_HOUR);

    days += tim_p->tm_mday - 1;
    days += _DAYS_BEFORE_MONTH[tim_p->tm_mon];
    if (tim_p->tm_mon > 1 && _DAYS_IN_YEAR(tim_p->tm_year) == 366)
        days++;

    tim_p->tm_yday = days;

    if (tim_p->tm_year > 10000 || tim_p->tm_year < -10000) {
        return (time_t)-1;
    }

    if (tim_p->tm_year > 70) {
        for (year = 70; year < tim_p->tm_year; year++)
            days += _DAYS_IN_YEAR(year);
    } else if (tim_p->tm_year < 70) {
        for (year = 69; year > tim_p->tm_year; year--)
            days -= _DAYS_IN_YEAR(year);
        days -= _DAYS_IN_YEAR(year);
    }

    if ((tim_p->tm_wday = (days + 4) % 7) < 0)
        tim_p->tm_wday += 7;

    tim += (days * _SEC_IN_DAY);

    return tim;
}
