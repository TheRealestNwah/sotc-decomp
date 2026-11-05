#ifdef NONMATCHING
int ColCont2_IsEventColStatus(char *p, int mask, int val)
{
    int r;

    if (val != -1) {
        if ((*(long *)(p + 8) & mask) == val) {
            return 1;
        }
        goto zero;
    }
    if (mask != val) {
        r = 1;
        if (!(*(long *)(p + 8) & mask)) {
zero:
            r = 0;
        }
        return r;
    }
    return 1;
}
#endif
