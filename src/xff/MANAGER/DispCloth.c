typedef struct { char *p; short n; } Cloth;
extern void func_000BCCE8(char *);

int DispCloth(Cloth *c)
{
    char *p = c->p;
    int n = c->n;
    int i;
    for (i = 0; i < n; i++) {
        if (p[0x81] == 0)
            func_000BCCE8(p);
        else
            p[0x81] = 0;
        p += 0x90;
    }
    return 1;
}
