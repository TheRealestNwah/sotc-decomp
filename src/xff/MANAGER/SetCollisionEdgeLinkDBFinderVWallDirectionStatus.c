typedef int s128 __attribute__((mode(TI)));

void SetCollisionEdgeLinkDBFinderVWallDirectionStatus(char *dst, char *src)
{
    *(s128 *)(dst + 0x0) = *(s128 *)(src + 0x0);
}
