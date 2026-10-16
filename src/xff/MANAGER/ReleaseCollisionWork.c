extern void iosFree(void *p);

void ReleaseCollisionWork(void **work)
{
    iosFree(work[0]);
    work[0] = 0;
}
