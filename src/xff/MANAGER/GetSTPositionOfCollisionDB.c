#ifdef NONMATCHING /* parked draft: 138 diffs, VU0 runs in place */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetLayoutClass(void *);
extern void func_000999E0(void *, int, char *, int, int);
extern void func_0009AE78(void *, int, int, int, int, int, int, int);

int GetSTPositionOfCollisionDB(float *s, float *t, int *handle, float *point)
{
    Vec4 e1;
    Vec4 e2;
    Vec4 d;
    Vec4 w[2];
    int *rec[2];
    unsigned int idx = handle[1] & 0xFFFFFF;
    unsigned int group = ((unsigned int)handle[1] >> 24) & 0x7F;
    char *cls = GetLayoutClass((void *)handle[0]);
    float a, b, f2, f3;

    if (handle[1] < 0) {
        func_000999E0(rec, 0, cls, group, idx);
    } else {
        char *g = *(char **)(*(char **)(cls + 0x184) + 0x20);
        char *p = *(char **)(cls + 0x154 + 0x20);
        func_0009AE78(rec, 0, *(int *)(p + 0x28), *(int *)(*(char **)(p + 0x24)), *(int *)(g + 0x8), *(int *)(g + 0x14), *(int *)(g + 0x18), idx);
    }
    __asm__ __volatile__("lqc2 vf29, 0x0(%1)\n"
                         "lqc2 vf30, 0x0(%2)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n"
                         : : "r"(&e1), "r"((float *)rec[1]), "r"((float *)rec[0]) : "memory");
    __asm__ __volatile__("lqc2 vf29, 0x0(%1)\n"
                         "lqc2 vf30, 0x0(%2)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n"
                         : : "r"(&e2), "r"((float *)rec[2]), "r"((float *)rec[0]) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%3)\n"
                         "lqc2 vf5, 0x0(%4)\n"
                         "lqc2 vf6, 0x0(%5)\n"
                         "lqc2 vf7, 0x0(%3)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf8, vf6, vf5\n"
                         "vsub.w vf8, vf8, vf8\n"
                         "vopmula.xyz ACC, vf8, vf6\n"
                         "vopmsub.xyz vf9, vf6, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f2) : "r"(point), "r"((float *)rec[0]), "r"(&d), "r"(&e1), "r"(&e2) : "$2", "memory");
    __asm__ __volatile__("vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf5\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f3) : : "$2", "memory");
    *s = f2 / f3;
    __asm__ __volatile__("vopmula.xyz ACC, vf8, vf5\n"
                         "vopmsub.xyz vf9, vf5, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f2) : : "$2", "memory");
    __asm__ __volatile__("vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf6\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f3) : : "$2", "memory");
    *t = f2 / f3;
    a = *s;
    b = *t;
    if (a < -0.00001f)
        return 0;
    if (b < -0.00001f)
        return 0;
    if (a + b - 1.0f > 0.00001f)
        return 0;
    return 1;
}
#endif
