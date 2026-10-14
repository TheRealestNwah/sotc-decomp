extern long GetGeometryPointerCharColAttr(void *);

long nico_GetGeometryPointerAttr(void *geometry)
{
    return GetGeometryPointerCharColAttr(geometry);
}
