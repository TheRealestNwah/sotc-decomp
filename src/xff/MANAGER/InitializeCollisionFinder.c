typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

static inline void finder_flush(int *f)
{
    int n = f[0];
    int *e;
    char *l;

    if (f[1] < n)
        n = f[1];
    l = (char *)f[4];
    e = (int *)f[3];
    while (--n != -1) {
        if (*e != 0)
            DeleteTwoWayLink((Link *)(l));
        e += 2;
        l += 12;
    }
    f[0] = 0;
}

static inline int finder_alive(char *p)
{
    if (*(int *)(p + 0xC) == 0) {
        goto no;
    }
    if (*(int *)(p + 0x10) == 0) {
        goto no;
    }
    return 1;
no:
    return 0;
}

extern void iosJumpRecoverPoint(const char *, ...);
extern char D_00140858[];
int InitializeCollisionFinder(int *finder, void *entries, void *nodes, int count, int flags)
{
    finder[1] = count;
    finder[2] = flags;
    finder[3] = (int)entries;
    finder[4] = (int)nodes;
    if (finder_alive((char *)finder)) {
        finder[0] = 0;
        finder_flush(finder);
        return 1;
    }
    iosJumpRecoverPoint(D_00140858);
    return 0;
}
