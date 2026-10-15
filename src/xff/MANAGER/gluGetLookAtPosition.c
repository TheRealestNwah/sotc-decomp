typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *get_cur_camera_context(void);

static inline void scale(Vec4 *o, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(v), "r"(s) : "memory");
}

static inline void add(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}

void gluGetLookAtPosition(Vec4 *out, float s)
{
    Vec4 t;
    char *c = get_cur_camera_context();
    scale(&t, (Vec4 *)(c + 0x150), s);
    add(out, (Vec4 *)(c + 0x140), &t);
}
