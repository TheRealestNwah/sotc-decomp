extern int InitCollisionFinder(void *, void *, int);

static void func_000ECB78(void *f, void *ptn)
{
    if (!InitCollisionFinder(f, ptn, 0x400))
        __asm__ __volatile__("break 0");
}
