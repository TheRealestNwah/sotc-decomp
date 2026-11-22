/* Like charrootdyn_getCyclicCollisionDetectZYOneWay, but with a caller-supplied
 * collision callback, and dir picks the segment direction passed to the finder. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

extern int ClipCollisionFinderCallBack(void *, Vec4 *, Vec4 *, void *, void *, void *);

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

static inline void makePoint(Vec4 *out, float r, float a)
{
    short ang = (int)(a * 32768.0f / 3.1415927f);
    out->i[0] = 0;
    out->f[1] = r * iosGetTableSin(ang);
    out->f[2] = r * iosGetTableCos(ang);
    out->f[3] = 1.0f;
}
int charrootdyn_getCyclicCollisionDetectZYOneWayCB(void *ctx, Vec4 *pos, Vec4 *quat, int n, int dir, void *db, void *cb,
                                                   void *arg, float r)
{
    Vec4 prev;
    Vec4 v;
    Vec4 cur;
    Vec4 w;
    float start;
    float step;
    int i;

    start = (r < 0.0f) ? 0.78539813f : -0.78539813f;
    step = 1.0f / (float)n;
    makePoint(&v, r, start);
    quatPosApply(prev.f, quat->f, pos->f, v.f);
    if (dir != 0) {
        for (i = 0; i < n; i++) {
            float t = (float)(i + 1) * 3.1415927f * step - 0.78539813f;
            if (r < 0.0f)
                t = -t;
            makePoint(&w, r, t);
            quatPosApply(cur.f, quat->f, pos->f, w.f);
            if (ClipCollisionFinderCallBack(ctx, &prev, &cur, db, cb, arg))
                return 1;
            prev.q = cur.q;
        }
    } else {
        for (i = 0; i < n; i++) {
            float t = (float)(i + 1) * 3.1415927f * step - 0.78539813f;
            if (r < 0.0f)
                t = -t;
            makePoint(&w, r, t);
            quatPosApply(cur.f, quat->f, pos->f, w.f);
            if (ClipCollisionFinderCallBack(ctx, &cur, &prev, db, cb, arg))
                return 1;
            prev.q = cur.q;
        }
    }
    return 0;
}
