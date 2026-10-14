typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;

void ResetCharacterClassSlideStatus(char *p)
{
    *(s128 *)(p + 0xAB0) = ZeroVector;
}
