extern int nico_GetGeometryPointerAttr(void *);

int IsGeoColStatus(void *g, int mask, int value)
{
    return (nico_GetGeometryPointerAttr(g) & mask) == value;
}
