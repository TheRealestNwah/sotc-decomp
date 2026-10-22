typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void FlushCollisionFinder(int *f)
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
