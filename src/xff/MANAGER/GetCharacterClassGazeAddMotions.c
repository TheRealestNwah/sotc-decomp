extern void func_0004AFA8(void *, void *, void *);

void GetCharacterClassGazeAddMotions(void *a, char *c)
{
    int n = *(int *)(c + 0x41C);
    char *e;
    void *m;

    if (n != 0) {
        m = *(void **)(c + 0x358);
        e = *(char **)(c + 0x334);
        do {
            func_0004AFA8(a, m, e);
            e += 0x10;
        } while (--n);
    }
}
