typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern int D_00136F80;
extern int ClipCollisionDirect(void *, Vec4 *, Vec4 *, int);

void DebugTestWideAreaSearch(char *s)
{
    Vec4 a, b;
    GetGeometryPointerPosition(&a, s + 0x20);
    GetGeometryPointerPosition(&b, s + 0x60);
    ClipCollisionDirect(s + 0xA0, &a, &b, D_00136F80);
}
