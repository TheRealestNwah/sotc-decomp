#ifdef NONMATCHING
int ColCont2_IsColStatus(long *p, int mask, int val)
{
    if (val == -1) {
        return mask == val || (*p & mask) != 0;
    }
    return (*p & mask) == val;
}
#endif
