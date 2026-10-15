typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 YUnitVector;
extern Vec4 ZeroPoint;
typedef struct { int a, b, c, pad; long d; long pad2; Vec4 n; Vec4 p0; Vec4 p1; int e; } ColPlane;

void GAMEUTIL_constructor_col_plane_info(ColPlane *p)
{
    p->a = 0;
    p->b = 0;
    p->c = 0;
    p->d = 0;
    p->n.q = YUnitVector.q;
    p->p0.q = ZeroPoint.q;
    p->p1.q = ZeroPoint.q;
    p->e = 0;
}
