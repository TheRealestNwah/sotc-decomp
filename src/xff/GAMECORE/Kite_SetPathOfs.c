typedef int s128 __attribute__((mode(TI)));

void Kite_SetPathOfs(char *p, s128 *v)
{
    *(s128 *)(p + 0xD0) = *v;
    *(s128 *)(p + 0x1A0) = *v;
}
