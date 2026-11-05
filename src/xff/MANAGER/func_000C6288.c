typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern int D_001370D4;
extern int func_000C6400(void *);
extern void GetCollisionDB(void *, int, int, Vec4 *, Vec4 *, float);
extern void AddCollisionDB(void *, int, int, Vec4 *, Vec4 *, float);

static inline void scaleXYZ(Vec4 *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void addXYZ(Vec4 *out, void *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000C6288(char *e, char *d)
{
    Vec4 base;
    Vec4 step;
    Vec4 pos;
    Vec4 ofs;
    int ok;

    ok = func_000C6400(e + 0x170);
    if (ok == 1) {
        float scale = *(float *)(d + 0x124);
        float radius = *(float *)(d + 0x108);
        int n = *(int *)(d + 0x10C);
        float len = *(float *)(d + 0x110);
        int i;

        scaleXYZ(&step, e + 0x30, scale);
        addXYZ(&base, e + 0x10, &step);
        GetCollisionDB(e + 0x170, D_001370D4, 0, &base, &base, radius);
        if (n != ok) {
            scaleXYZ(&step, e + 0x30, len);
            for (i = 1; i < n; i++) {
                scaleXYZ(&ofs, &step, (float)i);
                addXYZ(&pos, &base, &ofs);
                AddCollisionDB(e + 0x170, D_001370D4, 0, &pos, &pos, radius);
            }
        }
    }
}
