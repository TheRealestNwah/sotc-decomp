typedef struct { char *p; short n; } Cloth;
extern void func_000BCA98(char *);

int DebugDispCloth(Cloth *c)
{
    char *p = c->p;
    int n = c->n;
    int i;
    for (i = 0; i < n; i++) {
        func_000BCA98(p);
        p += 0x90;
    }
    return 1;
}
