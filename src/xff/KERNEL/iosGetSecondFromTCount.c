float iosGetSecondFromTCount(unsigned long ticks)
{
    unsigned long seconds = ticks / 150000000UL;
    ticks -= seconds * 150000000UL;
    return (float)seconds + (float)ticks * (1.0f / 150000000.0f);
}