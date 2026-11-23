/* Parked: 13 diffs, same size (332 words).
 * Samples a motion node's rotation, translation and scale keys at a float frame,
 * wrapping the frame into the key range and interpolating between neighbouring
 * keys (quaternion slerp-like lerp + normalize on VU0, vector lerp otherwise).
 * Remaining: the Original keeps q (a0) in s3 and i1 in s4 where gcc swaps them
 * (10 words), and the frames == 1 test uses bnel with $v0 where gcc emits bne
 * with $v1 (3 words).
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float off0, scale0, off1, scale1, off2, scale2; short *tbl; } PackVec;
typedef union { float f[4]; short h[8]; s128 q; } VecU;
typedef struct { unsigned char st, qt, vt, pad; void *data; void *qdata; void *sdata; } MotionOption;
extern void func_00031438(void *, int, void *, int);
extern void func_00032B78(void *, int, void *, int);
#define FETCH(o, i) do { void *data = opt->data; if (data) { int type = opt->vt; float z; (o)->f[3] = 1.0f; if (type != 0) { if (type != 2) { float *fv = (float *)data + (i) * 3; (o)->f[0] = fv[0]; (o)->f[1] = fv[1]; z = fv[2]; } else { PackVec *p = data; short *s = p->tbl + (i) * 3; (o)->f[0] = s[0] * p->scale0 * (1.0f / 32767.0f) + p->off0; (o)->f[1] = s[1] * p->scale1 * (1.0f / 32767.0f) + p->off1; z = s[2] * p->scale2 * (1.0f / 32767.0f) + p->off2; } } else { float *c = data; (o)->f[0] = c[0]; (o)->f[1] = c[1]; z = c[2]; } (o)->f[2] = z; } } while (0)
#define LERP(o, a, b, mask) __asm__ __volatile__("mfc1 $8, %3\n" "qmtc2.ni $8, vf7\n" "lqc2 vf5, 0x0(%1)\n" "lqc2 vf6, 0x0(%2)\n" "vsubx.w vf8, vf0, vf7x\n" "vmulax." mask " ACC, vf5, vf7x\n" "vmaddw." mask " vf5, vf6, vf8w\n" "sqc2 vf5, 0x0(%0)\n" : : "r"(o), "r"(a), "r"(b), "f"(frac) : "$8", "memory")
static inline void VecInter(VecU *o, VecU *a, VecU *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3
" "qmtc2.ni $8, vf7
" "lqc2 vf5, 0x0(%1)
" "lqc2 vf6, 0x0(%2)
" "vsubx.w vf8, vf0, vf7x
" "vmulax.xyz ACC, vf5, vf7x
" "vmaddw.xyz vf5, vf6, vf8w
" "sqc2 vf5, 0x0(%0)
" : : "r"(o), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}
static inline float Dot4(VecU *a, VecU *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)
" "lqc2 vf15, 0x0(%2)
" "vmul.xyzw vf15, vf14, vf15
" "vaddy.x vf15, vf15, vf15y
" "vaddz.x vf15, vf15, vf15z
" "vaddw.x vf15, vf15, vf15w
" "qmfc2.ni $2, vf15
" "mtc1 $2, %0
" : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}
static inline void Normalize4(VecU *o)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)
" "vmul.xyzw vf15, vf14, vf14
" "vaddy.x vf15, vf15, vf15y
" "vaddz.x vf15, vf15, vf15z
" "vaddw.x vf15, vf15, vf15w
" "vrsqrt Q, vf0w, vf15x
" "vwaitq
" "vmulq.xyzw vf15, vf14, Q
" "sqc2 vf15, 0x0(%0)
" : : "r"(o) : "memory");
}
static inline void QuatInter(VecU *o, VecU *a, VecU *b, float t)
{
    VecU tmp;
    union { float f; int i; } dot;
    tmp.q = b->q;
    dot.f = Dot4(a, &tmp);
    if (dot.i < 0) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)
" "qmtc2.ni %1, vf6
" "vmulx.xyzw vf5, vf5, vf6x
" "sqc2 vf5, 0x0(%0)
" : : "r"(&tmp), "r"(-1.0f) : "memory");
    }
    __asm__ __volatile__("mfc1 $8, %3
" "qmtc2.ni $8, vf7
" "lqc2 vf5, 0x0(%1)
" "lqc2 vf6, 0x0(%2)
" "vsubx.w vf8, vf0, vf7x
" "vmulax.xyzw ACC, vf5, vf7x
" "vmaddw.xyzw vf9, vf6, vf8w
" "sqc2 vf9, 0x0(%0)
" : : "r"(o), "r"(a), "r"(&tmp), "f"(t) : "$8", "memory");
    Normalize4(o);
}
static inline void GetVec(VecU *o, MotionOption *opt, int i)
{
    FETCH(o, i);
}
static inline void GetKey(VecU *q, VecU *v, VecU *s, MotionOption *opt, int i)
{
    GetVec(v, opt, i);
    if (opt->qdata) func_00031438(q, opt->qt, opt->qdata, i);
    if (opt->sdata) func_00032B78(s, opt->st, opt->sdata, i);
}
static void func_00032E98(VecU *q, VecU *v, VecU *s, MotionOption *opt, int frames, float frame)
{
    int i0, i1;
    float frac;
    if ((float)frames < frame) {
        if (frames == 1) {
            frame -= (float)(int)frame;
        } else {
            frame -= (float)((frames - 1) * (int)(frame / (float)(frames - 1)));
        }
    }
    i0 = (int)frame;
    frac = frame - (float)i0;
    i1 = i0 + 1;
    if (frac == 0.0f) {
        GetKey(q, v, s, opt, i0);
    } else {
        VecU qa[2], va[2], sa[2];
        GetKey(&qa[0], &va[0], &sa[0], opt, i0);
        GetKey(&qa[1], &va[1], &sa[1], opt, i1);
        QuatInter(q, &qa[1], &qa[0], frac);
        VecInter(v, &va[1], &va[0], frac);
        VecInter(s, &sa[1], &sa[0], frac);
    }
}
#else
extern void func_00032E98(void *, void *, void *, void *, int, float);
#endif
