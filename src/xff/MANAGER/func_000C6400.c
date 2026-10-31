extern int CheckCollisionFinderAlive(void *);
extern int InitCollisionFinder(void *, void *, int);
extern char rootPtn[];

static int func_000C6400(void *p)
{
    if (CheckCollisionFinderAlive(p) || InitCollisionFinder(p, rootPtn, 0x40))
        return 1;
    return 0;
}
