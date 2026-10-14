extern char *GetDamageClass(void *);
extern void GetGeometryPointerSurfaceAttribute(long *, void *);

long SCRGetBossCollisionAttribute(void *actor)
{
    long attribute;

    GetGeometryPointerSurfaceAttribute(&attribute, GetDamageClass(actor) + 0x10);
    return attribute;
}
