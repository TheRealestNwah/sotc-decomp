extern void iosFree(void *);

void delPathData(void *a, void *b, void *w)
{
    iosFree(w);
    w = 0;
}
