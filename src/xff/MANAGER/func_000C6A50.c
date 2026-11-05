typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern s128 *GetGeometryPointerSurfacePlane(void *);

static void func_000C6A50(Vec4 *pos, Vec4 *plane, char *g)
{
    pos->q = *(s128 *)(g + 0x40);
    plane->q = *GetGeometryPointerSurfacePlane(g);
    plane->f[3] = 0.0f;
}
