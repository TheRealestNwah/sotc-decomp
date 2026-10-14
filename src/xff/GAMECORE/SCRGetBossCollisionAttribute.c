typedef int GeometryAttributeVector __attribute__((mode(TI)));
typedef union {
    GeometryAttributeVector vector;
    long words[2];
} GeometryAttribute;

extern char *GetDamageClass(void *);
extern void GetGeometryPointerSurfaceAttribute(GeometryAttribute *, void *);

long SCRGetBossCollisionAttribute(void *actor)
{
    GeometryAttribute attribute;

    GetGeometryPointerSurfaceAttribute(&attribute, GetDamageClass(actor) + 0x10);
    return attribute.words[0];
}
