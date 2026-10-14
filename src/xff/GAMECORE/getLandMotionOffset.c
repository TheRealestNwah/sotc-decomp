typedef int s128 __attribute__((mode(TI)));

void getLandMotionOffset(char *p, s128 *out)
{
    *out = *(s128 *)(p + 0xF0);
}
