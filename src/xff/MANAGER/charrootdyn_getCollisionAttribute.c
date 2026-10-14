extern void GetGeometryPointerSurfaceAttribute(long *, void *);

long charrootdyn_getCollisionAttribute(void *geometry)
{
    long attribute;

    GetGeometryPointerSurfaceAttribute(&attribute, geometry);
    return attribute;
}
