struct tm { int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst; };
extern long mktime(struct tm *);

long iosGetClockSecond(unsigned char *c)
{
    struct tm t;
    if (c[0] != 0)
        return 0;
    t.tm_sec = c[1];
    t.tm_min = c[2];
    t.tm_hour = c[3];
    t.tm_mday = c[5];
    t.tm_mon = c[6] - 1;
    t.tm_year = c[7] - 1900;
    t.tm_wday = 0;
    t.tm_yday = 0;
    t.tm_isdst = 0;
    return mktime(&t);
}
