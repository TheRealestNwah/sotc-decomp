extern int ClipCollisionVariableXZSurface(void *out, void *a, void *b, void *c);
extern void CopyGeometryPointer(void *dst, void *src);

static int func_00034880(void *geometry, void *a, void *b, void *c)
{
    char buf[0x50];
    if (ClipCollisionVariableXZSurface(buf, a, b, c) == 0) {
        return 0;
    }
    CopyGeometryPointer(geometry, buf);
    return 1;
}
