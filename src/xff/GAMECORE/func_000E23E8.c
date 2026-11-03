typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct {
    char pad0[0x64];
    float x64;
} SpringParam;

extern Vec4 ZeroVector;
extern void func_000DF418(char *, void *, void *, char *, void *);
extern void reset_double_spring_interp_cntrl3D(char *, float *);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void doit_double_spring_interp_cntrl3D(char *, char *, int, float);

static void func_000E23E8(char *obj, void *a, void *b, void *c, SpringParam **prm, char *mode, float t)
{
    if (*(int *)(mode + 0x1360) != 1) {
        reset_double_spring_interp_cntrl3D(obj + 0x1C0, ZeroVector);
    } else {
        func_000DF418(obj + 0x200, a, b, obj, c);
        set_param_double_spring_interp_common(obj + 0x1C0, (*prm)->x64, -1.0f, (*prm)->x64 * 0.5f, -1.0f);
        doit_double_spring_interp_cntrl3D(obj + 0x1C0, obj + 0x200, 0, t);
    }
}
