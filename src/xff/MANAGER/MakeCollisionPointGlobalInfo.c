typedef int s128 __attribute__((mode(TI)));

void MakeCollisionPointGlobalInfo(char *p, s128 *v)
{
    *(s128 *)(p + 0x40) = *v;
    *(int *)(p + 0x30) = 0;
}
