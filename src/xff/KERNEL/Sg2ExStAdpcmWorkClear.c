extern void *memset(void *, int, unsigned int);

void Sg2ExStAdpcmWorkClear(int *p, int a)
{
    memset(p, 0, 0x2E0);
    p[0] = 0;
    p[2] = a;
    p[3] = a;
}
