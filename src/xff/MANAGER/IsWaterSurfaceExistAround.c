#ifdef NONMATCHING /* parked draft: 79 diffs; skeleton of the ClipCollisionVariableXZSurface family, matInverse/matApply result block not yet wired */
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
extern int func_0009C0B0(void *, void *, void *, int, int, void *, int, void *);
extern int func_0009D0B0(void);
extern float RO_0011A5B4;

struct Res {
    int found;
    float dist;
    int pad[2];
    Vec4 pos;
    float a, b, c, d;
};

int IsWaterSurfaceExistAround(float *out, float *pos, int group, float f12, float f13)
{
    Vec4 buf[5];
    struct Res res;
    Vec4 query;
    float lim[2];
    int obj = 0;
    int *g;
    char *cls;
    int ok;

    res.found = 0;
    res.dist = RO_0011A5B4;
    *(s128 *)query = *(s128 *)pos;
    lim[0] = f12;
    lim[1] = f13;
    g = isysGroupForFirst(group, 0);
    if (g) {
        obj = g[0];
        do {
            if (GetLayoutClass(obj)[0x1B8] != 0) {
                int *v = *(int **)(*(int *)(GetLayoutClass(obj) + 0x184) + 0x20);
                if (*v < 2) {
                    ok = 0;
                } else if (v[14] != 0 && func_0009C0B0(buf, pos, pos, obj, 1, (void *)func_0009D0B0, 0, &res)) {
                    ok = 1;
                } else {
                    ok = 0;
                }
                if (ok) {
                    break;
                }
            }
            g = isysGroupForNext(g, 0);
            if (g)
                obj = g[0];
        } while (g);
    }
    if (obj)
        isysGroupForExit(obj, 0);
    if (res.found == 1)
        *out = res.dist;
    return res.found;
}
#endif
