typedef int s128 __attribute__((mode(TI)));
extern s128 *getPassageWork(void *, int);

int getAimPosFromPathManager(void *m, s128 *out)
{
    s128 *w = getPassageWork(m, 0);
    if (w == 0)
        return 0;
    *out = *w;
    return 1;
}
