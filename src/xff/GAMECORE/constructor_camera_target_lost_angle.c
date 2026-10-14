typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 ZUnitVector;
extern Vec4 ZeroPoint;
typedef struct { int a; char pad[0xC]; Vec4 dir; float f20; float f24; char pad2[8]; Vec4 pos; } T;
void constructor_camera_target_lost_angle(T *p)
{
    p->a = 0;
    p->dir.q = ZUnitVector.q; p->f20 = p->f24 = 0.0f;
    p->pos.q = ZeroPoint.q;
}
