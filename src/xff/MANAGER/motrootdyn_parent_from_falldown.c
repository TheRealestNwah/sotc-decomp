/* Picks the parent geometry (0xF70, 0xC0 or 0xEF0), puts the A80 offset through the geometry matrix into *134, and aligns the root quaternion so its local Y follows the surface plane, flipping 180 degrees about X when it faces away. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void UpdateLayoutClassParentGeometry(char *, int, int);
extern void GetGeometryPointerQuatPos(void *, void *);
extern void GetMatrixFromQuatPos(void *, void *);
extern Vec4 *GetGeometryPointerSurfacePlane(void *);
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, int, void *);
extern void SetLayoutClassRootQuaternion(char *, void *);
extern Vec4 XUnitVector;

static inline void dirX(Vec4 *out, Vec4 *q)
{
    register Vec4 *o asm("$7") = out;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(o), "r"(q) : "memory");
}

static inline int dirY(Vec4 *out, Vec4 *q)
{
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
                         : : "r"(out), "r"(q) : "memory");
}

static inline void dirZ(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline int outerProduct(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(Vec4 *out, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v) : "memory");
}

static inline float innerProduct(Vec4 *a, Vec4 *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(dot) : "r"(a), "r"(b));
    return dot;
}

static inline void mulQuat(Vec4 *out, Vec4 *a, Vec4 *b)
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

static inline void *parentGeo(char *cls)
{
    if (*(int *)(cls + 0xFBC))
        return cls + 0xF70;
    if (*(int *)(cls + 0x124))
        return cls + 0xC0;
    if (*(int *)(cls + 0xF3C))
        return cls + 0xEF0;
    return 0;
}

static inline void setVec(Vec4 *v, float *a)
{
    v->f[0] = a[0];
    v->f[1] = a[1];
    v->f[2] = a[2];
    v->f[3] = 1.0f;
}

static inline void flip(Vec4 *out, Vec4 *q, float d)
{
    Vec4 r;

    if (d < 0.0f) {
        SetQuaternionByAxisRotateVWithNoRegularize(&r, -0x8000, &XUnitVector);
        mulQuat(out, q, &r);
    }
}

void motrootdyn_parent_from_falldown(void *m, char *cls)
{
    Vec4 mat[4];
    Vec4 qp[2];
    Vec4 v;
    Vec4 dx;
    Vec4 q;
    Vec4 dz;
    Vec4 dy;
    void *g = 0;
    Vec4 *plane;

    g = parentGeo(cls);
    if (g == 0)
        return;
    UpdateLayoutClassParentGeometry(cls, 0, 0);
    GetGeometryPointerQuatPos(qp, g);
    GetMatrixFromQuatPos(mat, qp);
    setVec(&v, (float *)(cls + 0xA80));
    applyMatrix(*(Vec4 **)(cls + 0x134), mat, &v);
    plane = GetGeometryPointerSurfacePlane(g);
    dirX(&dx, *(Vec4 **)(cls + 0x13C));
    outerProduct(&v, &dx, plane);
    normalize(&v, &v);
    dirZ(&dz, *(Vec4 **)(cls + 0x13C));
    GetDifferencialQuaternionWithNoRegularize(&q, &v, &dz);
    mulQuat(&q, &q, *(Vec4 **)(cls + 0x13C));
    dirY(&dy, &q);
    flip(&q, &q, innerProduct(&dy, plane));
    SetLayoutClassRootQuaternion(cls, &q);
}
