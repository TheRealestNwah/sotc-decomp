extern void resetPassageWork(char *);

int forceSetWayFinish(char *p)
{
    int s;
    if (*(int *)(p + 0x3A0) == 0) {
        s = *(int *)(p + 0x380);
        if (s == 1) {
            resetPassageWork(p);
            *(int *)(p + 0x408) = s;
            return 1;
        }
    }
    return 0;
}
