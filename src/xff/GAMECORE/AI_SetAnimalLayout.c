typedef int s128 __attribute__((mode(TI)));

void AI_SetAnimalLayout(char *p, s128 *v, float a, float b)
{
    *(s128 *)p = *v;
    *(float *)(p + 0x10) = a;
    *(float *)(p + 0x14) = b;
}
