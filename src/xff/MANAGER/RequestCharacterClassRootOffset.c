typedef int s128 __attribute__((mode(TI)));

void RequestCharacterClassRootOffset(char *dst, char *src)
{
    *(s128 *)(dst + 0xC80) = *(s128 *)(src + 0x0);
}
