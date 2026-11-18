extern int DldSysUndefSymbol;
extern int MotionKind_ALWAYS;

static inline char *resourceObj(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    return off != 0 ? *(char **)((char *)h - off) : 0;
}

static inline char *resourceElement(unsigned int *h)
{
    char *t = resourceObj(h);
    if (t != 0 && t != (char *)DldSysUndefSymbol) {
        return *(char **)(t + 0x10) + (((unsigned int)*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC);
    }
    return 0;
}

typedef struct {
    unsigned int h;
    int e[2][2];
    char pad[0x4C - 0x14];
} MotionEntry;

static inline MotionEntry *tableOf(unsigned int *h)
{
    char *t = resourceObj(h);
    return t != 0 && t != (char *)DldSysUndefSymbol ? *(MotionEntry **)(t + 0x10) : 0;
}

static inline int countOf(unsigned int *h)
{
    char *t = resourceObj(h);
    return t != 0 && t != (char *)DldSysUndefSymbol ? *(int *)(t + 0xC) : 0;
}

static void *func_00052A80(unsigned int *h, char *key, int idx)
{
    MotionEntry *tab = tableOf(h);
    int n;
    int i;
    char *v;

    if (tab == 0) {
        return 0;
    }
    n = countOf(h);
    if (key != 0) {
        i = n - 1;
        if (n != 0) {
            do {
                v = resourceElement(&tab->h);
                if (v == (char *)MotionKind_ALWAYS || v == key) {
                    return (char *)tab + idx * 8 + 4;
                }
                tab++;
            } while (i-- != 0);
            return 0;
        }
    } else {
        tab = &tab[n - 1];
        if (resourceElement(&tab->h) == (char *)MotionKind_ALWAYS) {
            return (char *)tab + idx * 8 + 4;
        }
    }
    return 0;
}
