typedef int Quadword __attribute__((mode(TI)));
typedef struct { Quadword q; } Vector;
extern int is_sub_type_camera_lws_animation(void *);
extern char *GetLayoutClass(unsigned char *);

static inline void multiplyXYZ(Vector *out, const Vector *scale)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "lqc2 vf6, 0x0(%1)\n"
        "vmul.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(scale) : "memory");
}
static inline void addXYZ(Vector *out, const Vector *offset)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "lqc2 vf6, 0x0(%1)\n"
        "vadd.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(offset) : "memory");
}
static void func_000E7688(Vector *out, const Vector *input, void *parameter, unsigned char *object, int mode, const Vector *offset)
{
    *out = *input;
    if (!is_sub_type_camera_lws_animation(parameter)) {
        if (object)
            multiplyXYZ(out, (Vector *)(GetLayoutClass(object) + 0x90));
        if (mode == 1)
            addXYZ(out, offset);
    }
}
