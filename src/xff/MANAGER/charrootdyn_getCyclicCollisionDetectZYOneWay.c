/* Steps a point around a half circle of radius r in the YZ plane and runs the
 * collision finder on each segment; returns 1 on the first hit. */
/* Parked: 20 diffs.
 * Remaining: n lands in s5 instead of s4 (swapped with &cur/&w's s-registers),
 * and gcc hoists the callback address (lui) above the argument moves instead of
 * materialising it in $t0 right before the call. The constants are laundered
 * so cse2 doesn't share the outer pi/32768 with the loop.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern float iosGetTableSin(short);
extern float iosGetTableCos(short);
extern int func_00064660();
extern int ClipCollisionFinderCallBack(void *, Vec4 *, Vec4 *, void *, int (*)(), int);

static inline void transformPoint(Vec4 *out, Vec4 *v, Vec4 *quat, Vec4 *pos)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf18, 0x0(%3)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(quat), "r"(pos) : "memory");
}

static inline void makePoint(Vec4 *out, float r, float a)
{
    short ang = (int)(a * 32768.0f / 3.1415927f);
    out->i[0] = 0;
    out->f[1] = r * iosGetTableSin(ang);
    out->f[2] = r * iosGetTableCos(ang);
    out->f[3] = 1.0f;
}
static inline void makePoint0(Vec4 *out, float r, float a, float one)
{
    float k = 32768.0f, pi = 3.1415927f;
    short ang;
    __asm__("" : "+f"(k), "+f"(pi));
    ang = (int)(a * k / pi);
    out->i[0] = 0;
    out->f[1] = r * iosGetTableSin(ang);
    out->f[2] = r * iosGetTableCos(ang);
    out->f[3] = one;
}

int charrootdyn_getCyclicCollisionDetectZYOneWay(void *ctx, Vec4 *pos, Vec4 *quat, int n, void *db, float r)
{
    Vec4 prev;
    Vec4 v;
    Vec4 cur;
    Vec4 w;
    float start;
    float step;
    int i;

    start = (r < 0.0f) ? 0.78539813f : -0.78539813f;
    {
        float one = 1.0f;
        __asm__("" : "+f"(one));
        step = one / (float)n;
        makePoint0(&v, r, start, one);
    }
    transformPoint(&prev, &v, quat, pos);
    for (i = 0; i < n; i++) {
        float t = (float)(i + 1) * 3.1415927f * step - 0.78539813f;
        if (r < 0.0f)
            t = -t;
        makePoint(&w, r, t);
        transformPoint(&cur, &w, quat, pos);
        if (ClipCollisionFinderCallBack(ctx, &cur, &prev, db, func_00064660, 0))
            return 1;
        prev.q = cur.q;
    }
    return 0;
}
#endif
