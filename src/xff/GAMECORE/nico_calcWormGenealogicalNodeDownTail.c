extern char *GetSCRCharaAIWorkPtr(void *);
extern void nico_calcWormGenealogicalNodeTailBase(void **);

void nico_calcWormGenealogicalNodeDownTail(void **a)
{
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(*a) + 0x41B3) & ~0xF);
    int ok;
    int i;

    nico_calcWormGenealogicalNodeTailBase(a);
    ok = 1;
    for (i = 1; i < *(int *)(w + 0x1294) - 2; i++) {
        if (((signed char *)(w + 0xEE0))[i] == 0)
            ok = 0;
    }
    if (ok)
        w[0x129A] = 1;
}
