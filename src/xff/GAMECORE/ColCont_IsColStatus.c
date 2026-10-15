int ColCont_IsColStatus(long *p, long mask, long value)
{
    if (value != -1) {
        if ((*p & mask) == value)
            return 1;
    } else if (*p & mask)
        return 1;
    return 0;
}
