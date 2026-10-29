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

extern void iosFree(void *);
int ReleaseCollisionFinder(int *finder)
{
    if (finder_alive((char *)finder)) {
        finder_flush(finder);
        iosFree((void *)finder[3]);
        iosFree((void *)finder[4]);
        finder[3] = 0;
        finder[4] = 0;
    }
    return 1;
}
