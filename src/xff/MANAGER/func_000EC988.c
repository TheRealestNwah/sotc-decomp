typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;

extern int DldSysUndefSymbol;
extern char *D_00139F78;
extern char *D_00139F80;
extern V4 B_0015E440;
extern V4 D_00139F90;
extern V4 IdentityQuaternion;
extern V4 XUnitVector;
extern V4 YUnitVector;
extern V4 ZUnitVector;
extern void SetQuaternionByAxisRotateVWithNoRegularize(V4 *, short, V4 *);
extern void SetGeometryPointerNodePosState(void *, char *, int, V4 *, V4 *);
extern void SetGeometryPointerNodePosStateGlobalRot(void *, char *, int, V4 *, V4 *);
extern void CopyGeometryPointer(void *, char *);

static inline void quatMul(V4 *dst, V4 *a, V4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
" "lqc2 vf12, 0x0(%1)
" "vmul.xyzw vf13, vf11, vf12
" "vaddy.x vf13, vf13, vf13y
" "vaddz.x vf13, vf13, vf13z
" "vsubx.w vf13, vf13, vf13x
" "vmulw.xyz vf14, vf12, vf11w
" "vmulw.xyz vf15, vf11, vf12w
" "vopmula.xyz ACC, vf12, vf11
" "vopmsub.xyz vf16, vf11, vf12
" "vadd.xyz vf13, vf14, vf15
" "vadd.xyz vf13, vf13, vf16
" "sqc2 vf13, 0x0(%2)
" : : "r"(a), "r"(b), "r"(dst) : "memory");
}

static inline char *dldEntry(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

static inline void quatAxisMul(V4 *dst, V4 *src, int ang, V4 *axis)
{
    V4 t;
    V4 *d = dst;
    V4 *s = src;

    SetQuaternionByAxisRotateVWithNoRegularize(&t, (short)ang, axis);
    quatMul(d, s, &t);
}

static inline void quatAxisMul0(V4 *dst, V4 *src, int ang, V4 *axis)
{
    V4 t;
    V4 *s = src;

    SetQuaternionByAxisRotateVWithNoRegularize(&t, (short)ang, axis);
    quatMul(dst, s, &t);
}

static void func_000EC988(void *geom, float *arg)
{
    V4 pos;
    V4 q;
    char *e;
    V4 *r;
    int n;

    q.x = -arg[3];
    q.y = arg[4];
    q.z = -arg[5];
    q.w = 1.0f;
    pos = q;
    if (D_00139F80 == 0) {
        e = dldEntry((unsigned int *)(arg + 2));
        if (!e) {
            SetGeometryPointerNodePosState(geom, D_00139F78, -2, &IdentityQuaternion, &pos);
        } else {
            r = &q;
            quatAxisMul0(r, &IdentityQuaternion, -(short)(int)(arg[6] * 32768.0f / 180.0f), &YUnitVector);
            quatAxisMul(r, r, -(short)(int)(arg[7] * 32768.0f / 180.0f), &XUnitVector);
            quatAxisMul(r, r, (int)(arg[8] * 32768.0f / 180.0f), &ZUnitVector);
            n = *(int *)(e + 8);
            if (*(int *)(arg + 9)) {
                quatMul(r, &B_0015E440, r);
                SetGeometryPointerNodePosStateGlobalRot(geom, D_00139F78, n, r, &pos);
            } else {
                quatMul(r, &D_00139F90, r);
                SetGeometryPointerNodePosState(geom, D_00139F78, n, r, &pos);
            }
        }
    } else {
        CopyGeometryPointer(geom, D_00139F80);
    }
}
