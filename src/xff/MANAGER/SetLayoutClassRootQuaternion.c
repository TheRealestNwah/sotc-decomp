typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetGeometryPointerQuaternion(Vec4 *, char *);
extern void DivQuaternion(char *, Vec4 *, Vec4 *);

void SetLayoutClassRootQuaternion(char *l, Vec4 *q)
{
    Vec4 g;
    (*(Vec4 **)(l + 0x13C))->q = q->q;
    if (*(int *)(l + 0x124) != 0) {
        GetGeometryPointerQuaternion(&g, l + 0xC0);
        DivQuaternion(l + 0x60, q, &g);
    }
}
