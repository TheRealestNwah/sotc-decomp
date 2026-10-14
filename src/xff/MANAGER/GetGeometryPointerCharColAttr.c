extern void GetGeometryPointerSurfaceAttribute(long *, void *);

long GetGeometryPointerCharColAttr(void *geometry)
{
    long attribute;

    GetGeometryPointerSurfaceAttribute(&attribute, geometry);
    return attribute;
}
