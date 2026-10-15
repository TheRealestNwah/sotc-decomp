extern void iosFree(void *);

void delLoadObjEditWork(void *a, void *b, void *w)
{
    iosFree(w);
    w = 0;
}
