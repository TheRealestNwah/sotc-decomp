/* Parked: 3 diffs. Finds the water surface height under a point by clipping a vertical segment (pos with y = lo and y = hi) against each group object's variable XZ surface, with the water callback func_000AE150 and a depth limit (lim when mode is 1). The body is ClipCollisionVariableXZSurfaceCB inlined, with the object test and the hit record as nested inlines. Remaining: the copy of the buffer pointer for the hit record's matApply (daddu s0, s2) is scheduled before the lq instead of after the GetLayoutClass argument move; the permuter found nothing better in 30 minutes. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2 $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2 $8, vf24\n"
                         "qmtc2 $9, vf25\n"
                         "qmtc2 $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
static inline void matApply(float *out, float *m, float *v)
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

extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetLayoutClass(int);
extern int func_0009C0B0(void *, void *, void *, int, int, int, int, int);

static inline int testObj(void *buf, void *a, void *b, int obj, int t0, int t2, int t3, int arg)
{
    int *v = *(int **)(*(int *)(GetLayoutClass(obj) + 0x184) + 0x20);
    if (*v >= 2 && v[14] != 0 && func_0009C0B0(buf, a, b, obj, t0, t2, t3, arg))
        return 1;
    return 0;
}

static inline void setHit(char *out, int obj, Vec4 *hb)
{
    char *cls;
    if (out) {
        *(s128 *)(out + 0x40) = *(s128 *)hb;
        cls = GetLayoutClass(obj);
        *(int *)out = obj;
        matInverse((float *)hb[1], (float *)*(int *)(cls + 0x158));
        matApply((float *)(out + 0x10), (float *)hb[1], (float *)hb);
        *(int *)(out + 0x30) = 10;
    }
}

static inline int clipSurface(char *out, void *a, void *b, int group, int t0, int (*cb)(int, int), int t2, int t3, int arg)
{
    Vec4 buf[5];
    int r = 0;
    int obj = 0;
    int *g;

    for (g = isysGroupForFirst(group, 0); g; g = isysGroupForNext(g, 0)) {
        obj = g[0];
        {
            if (GetLayoutClass(obj)[0x1B8] != 0 && 1) {
                int ok;
                char *cls;
                ok = testObj(buf, a, b, obj, t0, t2, t3, arg);
                if (ok) {
                    setHit(out, obj, buf);
                    r = obj;
                    break;
                }
            }
        }
    }
    if (obj)
        isysGroupForExit(obj, 0);
    return r;
}

extern int func_000AE150();

int GetWaterSurfacePositionYExtend(float *out, float *pos, int group, int mode, float lo, float hi, float lim)
{
    char hit[0x50];
    union { s128 q; float f[4]; } a;
    union { s128 q; float f[4]; } b;
    float l;

    if (mode == 1) {
        l = lim;
    } else {
        l = 0.0f;
    }
    a.q = *(s128 *)pos;
    b.q = *(s128 *)pos;
    a.f[1] = lo;
    b.f[1] = hi;
    if (clipSurface(hit, &a, &b, group, mode, 0, 0, (int)func_000AE150, (int)&l)) {
        *out = *(float *)(hit + 0x44);
        return 1;
    }
    return 0;
}
#endif
