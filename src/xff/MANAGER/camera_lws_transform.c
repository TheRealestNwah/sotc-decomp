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
typedef Vector Vec4;
typedef struct {
    int id;
    int frame;
    int next;
    int pad0C;
    Vec4 rot;
    Vec4 rot_speed;
    Vec4 pos;
    Vec4 pos_speed;
    int unk50;
    int unk54;
    int pad58[2];
    Vec4 target;
    Vec4 target_speed;
    int unk80;
    int unk84;
    int unk88;
    float scale;
} CameraLwsAnimeData;


typedef struct {
    char prefix[0x10];
    Vector position;
    char pad20[0x10];
    int auxiliary;
    char tail[0x2C];
} AnimationSample;
static float T_000E5EA0(void *, const Vector *);
extern int GetAnimationClassObjectAnimation(void *, float *, void *, int);
static inline void scaleXYZ(Vector *out, float scale)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "qmtc2.ni %1, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(scale) : "memory");
}
static void func_000E75F8(CameraLwsAnimeData *out, void *animation, const Vector *reference)
{
    AnimationSample sample;
    float scale = T_000E5EA0(animation, reference);
    (void)GetAnimationClassObjectAnimation(&sample, (float *)((char *)animation + 4),
        (void *)*(int *)((char *)animation + 0x44), 1);
    out->unk54 = sample.auxiliary;
    out->target = sample.position;
    if (scale != 1.0f)
        scaleXYZ(&out->target, scale);
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
