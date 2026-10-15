typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetQuaternionByDegEulerYXZ(Vec4 *, float, float, float);
extern void DebugSetObjectGeometry(void *, Vec4 *, Vec4 *);

void gameflowSetPos(void *o, float x, float y, float z, float rx, float ry, float rz)
{
    Vec4 pos, q;
    pos.f[0] = -x;
    pos.f[1] = y;
    pos.f[2] = -z;
    pos.f[3] = 1.0f;
    GetQuaternionByDegEulerYXZ(&q, rx, -ry, rz);
    DebugSetObjectGeometry(o, &q, &pos);
}
