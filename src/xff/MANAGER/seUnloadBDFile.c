extern void sndBDClose(char *);
extern void sndVabHDClose(char *);
extern void iosFree(void *);
extern void sndVabDelete(char *);

void seUnloadBDFile(int a, int b, char *v)
{
    void *p;
    if (v == 0)
        return;
    **(int **)(v + 0x18) = 0;
    sndBDClose(v);
    p = *(void **)(v + 0xC);
    sndVabHDClose(v);
    iosFree(p);
    sndVabDelete(v);
}
