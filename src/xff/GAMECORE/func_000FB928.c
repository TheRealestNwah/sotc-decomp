extern char *getGoalPointDataByAreaIdx(void *, int, int);
extern short *getChildSubPointIdxArrayByAreaIdx(void *, int, int);
extern char *getSubPointDataByAreaIdx(void *, int, int);
extern float iosGetRandom(void);
extern const int RO_00181300;

static int func_000FB928(void *w, int unused, int area, int cur, int stage)
{
    int n = 0;
    char *goal = getGoalPointDataByAreaIdx(w, area, stage);
    short *child = getChildSubPointIdxArrayByAreaIdx(w, area, stage);
    int buf[RO_00181300];
    unsigned int i;
    int r;

    if (goal == 0 || child == 0)
        return -1;
    for (i = 0; i < *(unsigned int *)(goal + 0x14); i++) {
        if (*(int *)(getSubPointDataByAreaIdx(w, child[i], stage) + 0x10) & 2) {
            if (cur != child[i] && (unsigned int)n < 20)
                buf[n++] = child[i];
        }
    }
    if (n > 0) {
        r = iosGetRandom() * n;
        if (r >= n)
            r = n - 1;
        return buf[r];
    }
    return cur;
}
