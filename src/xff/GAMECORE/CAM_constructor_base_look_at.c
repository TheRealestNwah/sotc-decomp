typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 ZeroPoint;
extern Vec4 ZeroVector;
typedef struct { Vec4 a; Vec4 b; Vec4 c; Vec4 d; float e; float f; } BaseLookAt;

void CAM_constructor_base_look_at(BaseLookAt *p)
{
    p->a.q = ZeroPoint.q;
    p->b.q = ZeroPoint.q;
    p->c.q = ZeroVector.q;
    p->d.q = ZeroVector.q;
    p->e = p->f = 0.0f;
}
