/* Region test: sphere (0), ellipsoid (1), cylinder (2), box (3). The case
 * locals share stack slots, so they are laid out in one union. */
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4s;

extern void iosAbsVector(void *, void *);
extern void iosInverseMatrix(float *, void *);
extern void iosRotMatrixZ(float *, float);
extern void iosRotMatrixY(float *, float);

static inline void applyMatrix(float *m, float *v, float *out)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void mulMatrix(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatToMatrix(float *m, float *q)
{
    __asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(q), "r"(m) : "memory");
}

static inline void setTrans(float *m, float *t)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(t) : "memory");
}

static inline float distSq(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float lenSq(float *a)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static inline float lenSqXZ(float *a)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static inline void mulXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void makeMat(float *m, float *q, float *t)
{
    quatToMatrix(m, q);
    setTrans(m, t);
}

typedef float V4[4] __attribute__((aligned(16)));
typedef float M4[16] __attribute__((aligned(16)));
typedef union {
    struct { V4 s; M4 inv; V4 local; Vec4s rcp; Vec4s tmp; } e;
    struct { V4 pad; V4 cyl; M4 rot; V4 pad2[2]; M4 inv; V4 local; } c;
    struct { V4 pad[6]; V4 b; M4 inv; V4 local; } b;
} Locals;

static inline int ell(float *m, float *pos, Locals *u, float x, float y, float z)
{
    u->e.s[0] = x;
    u->e.s[1] = y;
    u->e.s[2] = z;
    u->e.s[3] = 1.0f;
    iosInverseMatrix(u->e.inv, m);
    u->e.tmp.w = 0.0f;
    u->e.tmp.x = 1.0f / u->e.s[0];
    u->e.tmp.y = 1.0f / u->e.s[1];
    u->e.tmp.z = 1.0f / u->e.s[2];
    u->e.rcp = u->e.tmp;
    applyMatrix(u->e.inv, pos, u->e.local);
    mulXYZ(u->e.local, u->e.local, &u->e.rcp.x);
    return lenSq(u->e.local) <= 1.0f;
}

static inline int cyl(float *m, float *pos, Locals *u)
{
    int inY;
    iosInverseMatrix(u->c.inv, m);
    applyMatrix(u->c.inv, pos, u->c.local);
    inY = 0;
    if (u->c.cyl[1] <= u->c.local[1] && u->c.local[1] <= u->c.cyl[2])
        inY = 1;
    return lenSqXZ(u->c.local) < u->c.cyl[0] * u->c.cyl[0] && inY;
}

static inline int cube(float *m, float *pos, Locals *u, float x, float y, float z)
{
    int r;
    u->b.b[0] = x;
    u->b.b[1] = y;
    u->b.b[2] = z;
    u->b.b[3] = 1.0f;
    iosInverseMatrix(u->b.inv, m);
    applyMatrix(u->b.inv, pos, u->b.local);
    iosAbsVector(u->b.local, u->b.local);
    r = 0;
    if (u->b.local[0] <= u->b.b[0] && u->b.local[1] <= u->b.b[1] && u->b.local[2] <= u->b.b[2])
        r = 1;
    return r;
}

int IsInsideOfRegion(int type, float *pos, float *center, float *quat, float x, float y, float z)
{
    M4 m;
    Locals u;
    int ret;

    ret = 0;
    if (type == 0) {
        if (distSq(pos, center) <= x * x)
            ret = 1;
        return ret;
    }
    makeMat(m, quat, center);
    if (type == 1) {
        if (ell(m, pos, &u, x, y, z) == 1)
            ret = 1;
    } else if (type == 2) {
        u.c.cyl[0] = y;
        u.c.cyl[1] = -z;
        u.c.cyl[2] = z;
        u.c.cyl[3] = 1.0f;
        if (x <= 1.0f) {
            iosRotMatrixZ(u.c.rot, 1.57079637f);
            mulMatrix(m, m, u.c.rot);
        } else if (x <= 2.0f) {
        } else if (x <= 3.0f) {
            iosRotMatrixY(u.c.rot, 1.57079637f);
            mulMatrix(m, m, u.c.rot);
        }
        if (cyl(m, pos, &u) == 1)
            ret = 1;
    } else if (type == 3) {
        if (cube(m, pos, &u, x, y, z) == 1)
            ret = 1;
    } else if (type == 4) {
        return 1;
    } else if (type == 5) {
        return 0;
    } else {
        __asm__ __volatile__("break 0");
    }
    return ret;
}
