typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);

static inline void quatRotateVector(Vec4 *out, float *quat, Vec4 *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

extern s128 ZeroVector;
extern struct { char pad[0x190]; float dt; } gcGlobalVar;
extern void SCRSetCharaMotionPlaySpeedRatioDirect(int, float);
extern void func_000B76A8(char *, float, float);
extern void AI_GetMotionBasicVelocity(void *, void *, float);

static inline void vadd(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vscale(void *out, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void vscalew(void *out, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void vsubw(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vsub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vnormalize(void *out, void *a)
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
                         : : "r"(out), "r"(a) : "memory");
}

static inline float vdot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline float vdistsq(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static void func_000BA520(char *w)
{
    int th = isysGetThisSubThread();
    float r = *(float *)(w + 0x264);
    float k;
    float h;
    float lim;
    float dy;
    float dsq;
    int th2;
    register char *lc asm("$18");
    char *lay0;
    char *lay;
    char *lay3;
    char *pos;
    Vec4 v;
    Vec4 t;
    Vec4 d;
    Vec4 e;

    if (r < 0.1f)
        r = 0.1f;
    SCRSetCharaMotionPlaySpeedRatioDirect(th, r);
    func_000B76A8(w, *(float *)(w + 0x23C), *(float *)(w + 0x26C));
    k = *(float *)(w + 0x60);
    lc = GetLayoutClass(th);
    AI_GetMotionBasicVelocity(w + 0x200, GetCharacterClass(th) + 0x9E0, *(float *)(w + 0x264));
    if ((unsigned int)(*(int *)(w + 0x15C) - 0xE) < 2) {
        quatRotateVector(&v, *(float **)(lc + 0x13C), (Vec4 *)(w + 0x200));
        vadd(&v, w + 0x220, &v);
    } else {
        vadd(&v, w + 0x210, w + 0x200);
        quatRotateVector(&v, *(float **)(lc + 0x13C), &v);
        *(s128 *)(w + 0x220) = v.q;
    }
    if (*(int *)(w + 0x2F4) != 0)
        k *= 0.5f;
    vscale(&v, &v, k);
    lay0 = GetLayoutClass(th);
    vscale(&t, &v, gcGlobalVar.dt);
    vadd(*(char **)(lay0 + 0x134), *(char **)(lay0 + 0x134), &t);

    th2 = isysGetThisSubThread();
    lay = GetLayoutClass(th2);
    h = *(float *)(w + 0x24C) - *(float *)(w + 0x1A4) + *(float *)(*(char **)(w + 0x64) + 8);
    if (h < ((float *)*(char **)(lay + 0x134))[1]) {
        char *cc = GetCharacterClass(th2);
        register int f asm("$3");
        ((float *)*(char **)(lay + 0x134))[1] = h;
        __asm__ __volatile__("" : : : "memory");
        f = *(int *)(cc + 0xFF0);
        if (f != 0) {
            vsubw(&d, cc + 0x1000, *(char **)(lay + 0x134));
            *(int *)&d.f[1] = 0;
            vnormalize(&d, &d);
            if (vdot(&d, w + 0x140) > 0.0f)
                v.q = ZeroVector;
        }
    }

    lay3 = GetLayoutClass(isysGetThisSubThread());
    pos = *(char **)(lay3 + 0x134);
    dsq = vdistsq(pos, w + 0x20);
    dy = ((float *)pos)[1] - *(float *)(w + 0x24);
    if (*(float *)(w + 0x30) * *(float *)(w + 0x30) < dsq) {
        vsub(&e, pos, w + 0x20);
        vnormalize(&e, &e);
        vscalew(&e, &e, *(float *)(w + 0x30));
        vadd(*(char **)(lay3 + 0x134), w + 0x20, &e);
    }
    lim = *(float *)(w + 0x34);
    if (((dy < 0.0f) ? -dy : dy) > lim) {
        float *p = (float *)*(char **)(lay3 + 0x134);
        float b = *(float *)(w + 0x24);
        if (dy < 0.0f) {
            float nl = -lim;
            __asm__("" : "+f"(nl));
            p[1] = b + nl;
        } else
            p[1] = b + lim;
    }
}
