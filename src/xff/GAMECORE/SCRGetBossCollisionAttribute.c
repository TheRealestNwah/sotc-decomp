extern char *GetDamageClass();
extern void GetGeometryPointerSurfaceAttribute(long *, char *);

long SCRGetBossCollisionAttribute(int a)
{
    long r;

    GetGeometryPointerSurfaceAttribute(&r, GetDamageClass(a) + 0x10);
    return r;
}
