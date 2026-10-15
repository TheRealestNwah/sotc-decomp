extern void iosFree(void *p);

void ReleaseStrHashKeyAll(int *h)
{
    iosFree((void *)h[1]);
    h[1] = 0;
    h[0] = 0;
}
