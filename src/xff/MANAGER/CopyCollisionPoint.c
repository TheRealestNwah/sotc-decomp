typedef int s128 __attribute__((mode(TI)));
extern void CopyGeometryPointer(char *, char *);

void CopyCollisionPoint(char *dst, char *src)
{
    CopyGeometryPointer(dst, src);
    *(s128 *)(dst + 0x40) = *(s128 *)(src + 0x40);
}
