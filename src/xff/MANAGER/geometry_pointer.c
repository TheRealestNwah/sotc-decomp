/* Geometry pointers: a reference to a point on some piece of geometry (a
 * fixed position, a motion node, a collision surface or edge, cloth), and
 * the queries that resolve it to a position, quaternion or plane. */

typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
    int i[4];
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

/* A GeometryPointer as ConvertGeometryPointerZNormalMode copies it, in
 * doublewords. */
typedef struct {
    long pad0[6];
    int type;
    int pad34;
    long pad38;
} GeometryPointerWords;

extern unsigned char InitialGeometryPointer[];
extern Vec4 YUnitVector;
extern s128 All1Vector;
extern char D_001408A0[];

extern void GetClothPosition(Vec4 *, void *, void *, int, float);
extern void GetClothQuaternion(Vec4 *, void *, void *, float, int);
extern void GetCollisionDBPositionWithNodeLocalPos(Vec4 *, GeometryPointer *, Vec4 *);
extern void GetCollisionDBPositionWithST(Vec4 *, GeometryPointer *, float, float);
extern void GetCollisionEdgePositionWithS(Vec4 *, GeometryPointer *, float);
extern void GetCollisionVariableXZSurfPosition(Vec4 *, GeometryPointer *);
extern void GetCollisionDBQuaternion(Vec4 *, GeometryPointer *);
extern void GetCollisionDBPlaneNormalZQuaternion(Vec4 *, GeometryPointer *);
extern float *GetCollisionDBPlane(void *);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, void *, int);
extern void GetMotionNodeGeoToolCoord(void *, void *, void *, void *, int, int);
extern void GetMatrixFromQuatPos(Vec4 *, QuatPos *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, float *);
extern float GetPlaneSlopeDegree(float *);
extern void CompletePlaneD(Vec4 *, Vec4 *);
extern void GetGeometryPointerWithCollisionDBDataGlobalPoint(GeometryPointer *, GeometryPointer *, float *);
extern void iosJumpRecoverPoint(const char *, ...);

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

static inline void setTransA1(Vec4 *m, Vec4 *t)
{
    /* Pinning t to $a1 for case 7 only gives the Original's registers there. */
    register Vec4 *tt __asm__("$5") = t;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(tt) : "memory");
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

static inline void quatMul(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void *GetGeometryPointerCollisionDB(GeometryPointer *g)
{
    switch (g->type) {
    case 2:
    case 3:
    case 4:
    case 5:
        return g;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        return 0;
    }
    return 0;
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

void GetGeometryPointerQuaternion(Vec4 *out, GeometryPointer *g)
{
    char *geometry = (char *)g;
    struct { Vec4 position, quaternion; } coordinate;
    s128 rotation;
    switch (*(unsigned int *)(geometry + 0x30)) {
    case 9:
        GetClothQuaternion(out, *(void **)geometry, *(void **)(geometry + 4),
                           *(float *)(geometry + 8), 0);
        break;
    case 0:
        out->q = *(s128 *)geometry;
        break;
    case 6:
        out->q = **(s128 **)geometry;
        quatMul(out, out, (Vec4 *)(geometry + 0x10));
        break;
    case 7:
        out->q = *(s128 *)(geometry + 0x20);
        break;
    case 5:
        GetCollisionDBPlaneNormalZQuaternion(out, g);
        break;
    case 1:
        GetMotionNodeQuaternionPosToolCoord(&coordinate.quaternion, &coordinate.position,
                                            *(void **)geometry,
                                            *(void **)(geometry + 4), 1);
        quatMul(out, &coordinate.quaternion, (Vec4 *)(geometry + 0x10));
        break;
    case 8:
        out->q = *(s128 *)(geometry + 0x10);
        break;
    case 2:
    case 3:
    case 4:
        GetCollisionDBQuaternion(out, g);
        break;
    case 10:
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(out) : "memory");
        SetQuaternionByAxisRotateVWithNoRegularize(&rotation, 0x4000, YUnitVector.f);
        quatMul(out, out, (Vec4 *)&rotation);
        break;
    }
}

void GetGeometryPointerQuatPos(QuatPos *out, GeometryPointer *g)
{
    switch (g->type) {
    case 9:
        GetClothQuaternion(&out->quat, g->p0, g->p4, g->f8, 0);
        GetClothPosition(&out->pos, g->p0, g->p4, 0, g->f8);
        break;
    case 0:
        out->quat.q = ((Vec4 *)g)->q;
        out->pos.q = g->v10.q;
        break;
    case 6: {
        Vec4 m[4];
        Vec4 *p = &out->pos;
        Vec4 *q = g->p0;
        Vec4 *t = g->p4;
        quatToMatrix(m, q);
        setTrans(m, t);
        applyMatrix(p, m, &g->v20);
        out->quat.q = ((Vec4 *)g->p0)->q;
        quatMul(&out->quat, &out->quat, &g->v10);
        break;
    }
    case 7: {
        Vec4 m[4];
        Vec4 *p = &out->pos;
        Vec4 *t;
        Vec4 *q;
        Vec4 *mm = m;
        q = g->p0;
        t = g->p4;
        quatToMatrix(mm, q);
        setTransA1(m, t);
        __asm__ __volatile__("" : : );
        applyMatrix(p, m, &g->v10);
        out->quat.q = g->v20.q;
        break;
    }
    case 1: {
        QuatPos qp;
        Vec4 m[4];
        GetMotionNodeQuaternionPosToolCoord(&qp.quat, &qp.pos, g->p0, g->p4, 1);
        GetMatrixFromQuatPos(m, &qp);
        applyMatrix(&out->pos, m, &g->v20);
        quatMul(&out->quat, &qp.quat, &g->v10);
        break;
    }
    case 2:
        GetCollisionDBPositionWithNodeLocalPos(&out->pos, g, &g->v10);
        GetCollisionDBQuaternion(&out->quat, g);
        break;
    case 3:
        GetCollisionDBPositionWithST(&out->pos, g, g->f8, g->fC);
        GetCollisionDBQuaternion(&out->quat, g);
        break;
    case 5:
        GetCollisionDBPositionWithST(&out->pos, g, g->f8, g->fC);
        GetCollisionDBPlaneNormalZQuaternion(&out->quat, g);
        break;
    case 4: {
        Vec4 *p = &out->pos;
        float s = g->fC;
        if (*(int *)&g->v10 != 0)
            s = 1.0f - s;
        GetCollisionEdgePositionWithS(p, g, s);
        GetCollisionDBQuaternion(&out->quat, g);
        break;
    }
    case 8:
    case 10:
        GetGeometryPointerPosition(&out->pos, g);
        GetGeometryPointerQuaternion(&out->quat, g);
        break;
    default:
        iosJumpRecoverPoint("geoptr:\tsomething wrong...: %d\n", g->type);
        break;
    }
}

int GetGeometryPointerVirtualSurfacePlane(Vec4 *plane, GeometryPointer *g)
{
    Vec4 pos;
    Vec4 q;
    int ret = 0;

    switch (g->type) {
    case 2:
    case 3:
    case 4:
    case 5: {
        void *db = GetGeometryPointerCollisionDB(g);
        Vec4 *p = &YUnitVector;

        if (db != 0)
            p = (Vec4 *)GetCollisionDBPlane(db);
        plane->q = p->q;
        ret = 1;
        break;
    }
    case 9: {
        GetGeometryPointerPosition(&pos, g);
        GetClothQuaternion(&q, g->p0, g->p4, g->f8, 0);
        __asm__ __volatile__("" : : );
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                             "vmul.xyzw vf5, vf4, vf4\n"
                             "vmr32.xyzw vf6, vf4\n"
                             "vmul.xyzw vf7, vf6, vf4\n"
                             "vaddy.z vf6, vf0, vf7y\n"
                             "vsubw.z vf6, vf6, vf7w\n"
                             "vsubx.y vf6, vf0, vf5x\n"
                             "vsubz.y vf6, vf6, vf5z\n"
                             "vaddz.x vf6, vf7, vf7z\n"
                             "vsub.w vf6, vf0, vf0\n"
                             "vadd.w vf5, vf0, vf0\n"
                             "vmulw.xyz vf6, vf6, vf5w\n"
                             "vaddw.y vf6, vf6, vf0w\n"
                             "sqc2 vf6, 0x0(%0)\n"
                             : : "r"(plane), "r"(&q) : "memory");
        CompletePlaneD(plane, &pos);
        break;
    }
    default: {
        GetGeometryPointerPosition(&q, g);
        plane->q = YUnitVector.q;
        CompletePlaneD(plane, &q);
        break;
    }
    }
    return ret;
}

void CopyGeometryPointer(void *arg0, void *arg1)
{
    (*(long *)((char *)(arg0) + 0)) = (long) (*(long *)((char *)(arg1) + 0));
    (*(long *)((char *)(arg0) + 8)) = (long) (*(long *)((char *)(arg1) + 8));
    (*(long *)((char *)(arg0) + 0x10)) = (long) (*(long *)((char *)(arg1) + 0x10));
    (*(long *)((char *)(arg0) + 0x18)) = (long) (*(long *)((char *)(arg1) + 0x18));
    (*(long *)((char *)(arg0) + 0x20)) = (long) (*(long *)((char *)(arg1) + 0x20));
    (*(long *)((char *)(arg0) + 0x28)) = (long) (*(long *)((char *)(arg1) + 0x28));
    (*(long *)((char *)(arg0) + 0x30)) = (long) (*(long *)((char *)(arg1) + 0x30));
    (*(long *)((char *)(arg0) + 0x38)) = (long) (*(long *)((char *)(arg1) + 0x38));
}

float GetGeometryPointerSurfaceSlopeDegree(char *g)
{
    void *db;
    float *r;
    switch (*(unsigned int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        db = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        db = 0;
        break;
    default:
        db = 0;
        break;
    }
    r = YUnitVector.f;
    if (db != 0)
        r = GetCollisionDBPlane(db);
    return GetPlaneSlopeDegree(r);
}

float *GetGeometryPointerSurfacePlane(char *g)
{
    void *db;
    float *r;
    switch (*(unsigned int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        db = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        db = 0;
        break;
    default:
        db = 0;
        break;
    }
    r = YUnitVector.f;
    if (db != 0)
        r = GetCollisionDBPlane(db);
    return r;
}

void InitGeometryPointer(void *arg0)
{
    (*(long *)((char *)(arg0) + 0)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0));
    (*(long *)((char *)(arg0) + 8)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 8));
    (*(long *)((char *)(arg0) + 0x10)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x10));
    (*(long *)((char *)(arg0) + 0x18)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x18));
    (*(long *)((char *)(arg0) + 0x20)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x20));
    (*(long *)((char *)(arg0) + 0x28)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x28));
    (*(long *)((char *)(arg0) + 0x30)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x30));
    (*(long *)((char *)(arg0) + 0x38)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x38));
}

void SetGeometryPointerGlobalState(char *pa0, char *pa1, char *pa2)
{
    ((Vec4 *)(pa0 + 0x30))->i[0] = 0;
    ((Vec4 *)(pa0 + 0x0))->q = ((Vec4 *)(pa1 + 0x0))->q;
    ((Vec4 *)(pa0 + 0x10))->q = ((Vec4 *)(pa2 + 0x0))->q;
}

void GetGeometryPointerScale(s128 *out, int *g)
{
    s128 a, b;
    if (g[12] == 1)
        GetMotionNodeGeoToolCoord(&a, &b, out, (void *)g[0], g[1], 1);
    else
        *out = All1Vector;
}

void SetGeometryPointerGlobalStatePointer(Vec4 *p, int a, int b, Vec4 *u, Vec4 *v)
{
    p[0].i[0] = a;
    p[3].i[0] = 6;
    p[0].i[1] = b;
    p[1].q = u->q;
    p[2].q = v->q;
}

void SetGeometryPointerGlobalStatePosPointer(Vec4 *p, int a, int b, Vec4 *u, Vec4 *v)
{
    p[0].i[0] = a;
    p[3].i[0] = 7;
    p[0].i[1] = b;
    p[1].q = u->q;
    p[2].q = v->q;
}

void *GetGeometryPointerObject(char *g)
{
    switch (*(unsigned int *)(g + 0x30)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 8:
    case 9:
    case 10:
        return *(void **)g;
    case 6:
    case 7:
        break;
    }
    return 0;
}

int GetGeometryPointerObjectParentNodeId(char *p)
{
    if (*(int *)(p + 0x30) != 1) {
        return -1;
    }
    return *(int *)(p + 0x4);
}

void ConvertGeometryPointerZNormalMode(GeometryPointerWords *dst, GeometryPointerWords *src)
{
    float pos[4];

    *dst = *src;
    switch (src->type) {
    case 4:
        GetGeometryPointerPosition((Vec4 *)pos, (GeometryPointer *)src);
        GetGeometryPointerWithCollisionDBDataGlobalPoint((GeometryPointer *)dst, (GeometryPointer *)src, pos);
    case 2:
    case 3:
        dst->type = 5;
        break;
    case 5:
    case 10:
        break;
    default:
        iosJumpRecoverPoint(D_001408A0, src->type);
        break;
    }
}
