extern void GetGeometryPointerSurfaceAttribute(long *, int);

long GetGeometryPointerCharColAttr(int a)
{
    long r;

    GetGeometryPointerSurfaceAttribute(&r, a);
    return r;
}
