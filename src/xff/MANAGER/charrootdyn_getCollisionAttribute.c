extern void GetGeometryPointerSurfaceAttribute(long *, int);

long charrootdyn_getCollisionAttribute(int a)
{
    long r;

    GetGeometryPointerSurfaceAttribute(&r, a);
    return r;
}
