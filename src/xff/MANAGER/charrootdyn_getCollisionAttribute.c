typedef int GeometryAttributeVector __attribute__((mode(TI)));
typedef union {
    GeometryAttributeVector vector;
    long words[2];
} GeometryAttribute;

extern void GetGeometryPointerSurfaceAttribute(GeometryAttribute *, void *);

long charrootdyn_getCollisionAttribute(void *geometry)
{
    GeometryAttribute attribute;

    GetGeometryPointerSurfaceAttribute(&attribute, geometry);
    return attribute.words[0];
}
