typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float iosGetTableSin(short);
extern float iosGetTableCos(short);
extern int ClipCollisionFinderCallBack(void *, Vec4 *, Vec4 *, char *, int (*)(), int);
extern int func_00064660();

#define QUAT_MATRIX_BODY \
    "vaddw.xyz vf12, vf0, vf0w\n" \
    "lqc2 vf11, 0x0(%1)\n" \
    "vmr32.w vf14, vf0\n" \
    "vmr32.w vf15, vf0\n" \
    "vmr32.w vf16, vf0\n" \
    "vopmula.xyz ACC, vf11, vf12\n" \
    "vmadd.xyz vf11, vf0, vf0\n" \
    "vmadd.xyz vf10, vf11, vf12\n" \
    "vmul.xyz vf13, vf11, vf10\n" \
    "vopmula.xyz ACC, vf11, vf10\n" \
    "vmaddw.xyz vf15, vf10, vf11w\n" \
    "vmsubw.xyz vf16, vf10, vf11w\n" \
    "vopmula.xyz ACC, vf13, vf12\n" \
    "vmadd.xyz vf17, vf13, vf12\n" \
    "vopmula.xyz ACC, vf15, vf12\n" \
    "vmadd.xyz vf15, vf0, vf0\n" \
    "vsub.xyz vf14, vf12, vf17\n" \
    "vmove.yz vf17, vf14\n" \
    "vmove.y vf14, vf16\n" \
    "vmove.y vf16, vf15\n" \
    "vmove.y vf15, vf17\n" \
    "vmove.z vf14, vf15\n" \
    "vmove.z vf15, vf16\n" \
    "vmove.z vf16, vf17\n"

/* out = rotate v by quat, then translate by pos. */
static inline void quatPosApply(float *out, float *quat, float *pos, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n" : : "r"(v));
    __asm__ __volatile__("lqc2 vf18, 0x0(%0)\n"
                         "vmove.w vf18, vf0\n"
                         QUAT_MATRIX_BODY
                         : : "r"(pos), "r"(quat) : "memory");
    __asm__ __volatile__("vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out) : "memory");
}

int charrootdyn_getCyclicCollisionDetectZY(void *g, Vec4 *pos, Vec4 *quat, int n, char *db, float r)
{
    Vec4 prev;
    Vec4 from;
    Vec4 dir;
    Vec4 a;
    Vec4 b;
    Vec4 dir2;
    float step;
    int i;

    step = 1.0f / n;
    dir.f[0] = 0;
    dir.f[1] = r * iosGetTableSin(0);
    dir.f[2] = r * iosGetTableCos(0);
    dir.f[3] = 1.0f;
    quatPosApply(prev.f, quat->f, pos->f, dir.f);
    from.q = prev.q;
    for (i = 0; i < n;) {
        int next = i + 1;
        float ang = (float)next * 3.14159251f * step;
        short s;

        if (r < 0.0f)
            ang = -ang;
        dir2.f[0] = 0.0f;
        s = ang * 32768.0f / 3.14159251f;
        dir2.f[1] = r * iosGetTableSin(s);
        dir2.f[2] = r * iosGetTableCos(s);
        dir2.f[3] = 1.0f;
        quatPosApply(a.f, quat->f, pos->f, dir2.f);
        if (ClipCollisionFinderCallBack(g, &a, &prev, db, func_00064660, 0) != 0)
            return 1;
        dir2.f[1] = -dir2.f[1];
        quatPosApply(b.f, quat->f, pos->f, dir2.f);
        if (ClipCollisionFinderCallBack(g, &from, &b, db, func_00064660, 0) != 0)
            return 1;
        i = next;
        prev.q = a.q;
        from.q = b.q;
    }
    return 0;
}
