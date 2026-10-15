typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern int *GetDamageClass(void *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern void SCRGetTargetPosXZDirOnMyCtrlGeo(Vec4 *, void *, Vec4 *);

int SCRConditionDamagedPosRight(void *a)
{
    Vec4 p;
    int *d = GetDamageClass(a);
    if (d[0] == 0)
        return 0;
    GetGeometryPointerPosition(&p, d + 4);
    SCRGetTargetPosXZDirOnMyCtrlGeo(&p, a, &p);
    if (!(0.0f <= p.f[0]))
        return 0;
    return 1;
}
