typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    void *p0;
    void *p4;
    float f8;
    float fC;
    Vec4 v10;
    Vec4 v20;
    int type;
} GeometryPointer;

typedef struct {
    Vec4 quat;
    Vec4 pos;
} QuatPos;

extern void GetClothPosition(Vec4 *, void *, void *, int, float);
extern void GetCollisionDBPositionWithNodeLocalPos(Vec4 *, GeometryPointer *, Vec4 *);
extern void GetCollisionDBPositionWithST(Vec4 *, GeometryPointer *, float, float);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, void *, int);
extern void GetMatrixFromQuatPos(Vec4 *, QuatPos *);
extern void GetCollisionEdgePositionWithS(Vec4 *, GeometryPointer *, float);
extern void GetCollisionVariableXZSurfPosition(Vec4 *, GeometryPointer *);

static inline void quatToMatrix(Vec4 *m, Vec4 *q)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(m), "r"(q) : "memory");
}

static inline void setTrans(Vec4 *m, Vec4 *t)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(t) : "memory");
}

static inline void applyMatrix(Vec4 *out, Vec4 *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

void GetGeometryPointerPosition(Vec4 *out, GeometryPointer *g)
{
    switch (g->type) {
    case 0:
        out->q = g->v10.q;
        break;
    case 6: {
        Vec4 m[4];
        Vec4 *q = g->p0;
        Vec4 *t = g->p4;
        quatToMatrix(m, q);
        setTrans(m, t);
        applyMatrix(out, m, &g->v20);
        break;
    }
    case 7: {
        Vec4 m[4];
        Vec4 *mm = m;
        Vec4 *q = g->p0;
        Vec4 *t = g->p4;
        quatToMatrix(mm, q);
        setTrans(m, t);
        __asm__ __volatile__("" : : );
        applyMatrix(out, m, &g->v10);
        break;
    }
    case 9:
        GetClothPosition(out, g->p0, g->p4, 0, g->f8);
        break;
    case 2:
        GetCollisionDBPositionWithNodeLocalPos(out, g, &g->v10);
        break;
    case 3:
    case 5:
        GetCollisionDBPositionWithST(out, g, g->f8, g->fC);
        break;
    case 1: {
        QuatPos qp;
        Vec4 m[4];
        GetMotionNodeQuaternionPosToolCoord(&qp.quat, &qp.pos, g->p0, g->p4, 1);
        GetMatrixFromQuatPos(m, &qp);
        applyMatrix(out, m, &g->v20);
        break;
    }
    case 8: {
        QuatPos qp;
        Vec4 m[4];
        GetMotionNodeQuaternionPosToolCoord(&qp.quat, &qp.pos, g->p0, g->p4, 1);
        GetMatrixFromQuatPos(m, &qp);
        applyMatrix(out, m, &g->v20);
        break;
    }
    case 4: {
        float s = g->fC;
        if (*(int *)&g->v10 != 0)
            s = 1.0f - s;
        GetCollisionEdgePositionWithS(out, g, s);
        break;
    }
    case 10:
        GetCollisionVariableXZSurfPosition(out, g);
        break;
    }
    out->f[3] = 1.0f;
}
