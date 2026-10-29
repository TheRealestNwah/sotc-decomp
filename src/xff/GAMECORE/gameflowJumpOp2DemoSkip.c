typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetQuaternionByDegEulerYXZ(Vec4 *, float, float, float);
extern void DebugSetObjectGeometry(void *, Vec4 *, Vec4 *);

static inline void set_demo_geometry(void *o, float x, float y, float z, float rx, float ry, float rz)
{
    Vec4 pos, q;
    pos.f[0] = -x;
    pos.f[1] = y;
    pos.f[2] = -z;
    pos.f[3] = 1.0f;
    GetQuaternionByDegEulerYXZ(&q, rx, -ry, rz);
    DebugSetObjectGeometry(o, &q, &pos);
}

extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);

void gameflowJumpOp2DemoSkip(void)
{
    void *player = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    void *horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    set_demo_geometry(player, 300.0f, 11.0f, 278.0f, 0.0f, 0.0f, 0.0f);
    if (horse != 0)
        set_demo_geometry(horse, 292.0f, 10.0f, 290.0f, 0.0f, 0.0f, 0.0f);
}
