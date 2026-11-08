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
extern void func_000E75F8(CameraLwsAnimeData *out, void *animation, const Vector *reference);
extern void func_000E7688(Vector *out, const Vector *input, void *parameter, unsigned char *object, int mode, const Vector *offset);

extern Vector ZeroVector;
extern Vector ZeroPoint;
extern int is_interest_type_camera_lws_animation(void *);

static inline void initAnimeData(CameraLwsAnimeData *out)
{
    out->id = -1;
    out->frame = 0;
    out->next = -1;
    out->rot = ZeroVector;
    out->rot_speed = ZeroVector;
    out->pos = ZeroPoint;
    out->pos_speed = ZeroPoint;
    out->unk50 = 0;
    out->unk54 = -1;
    out->target = ZeroPoint;
    out->target_speed = ZeroPoint;
    out->scale = 1.0f;
    out->unk80 = 0;
    out->unk84 = 0;
    out->unk88 = 0;
}
int get_interest_type_camera_lws_animation_data(CameraLwsAnimeData *out, int *anim, int param)
{
    void *base = (void *)anim[0];
    initAnimeData(out);
    if (anim[0] != 0 && is_interest_type_camera_lws_animation(base) == 1) {
        out->unk50 = param;
        if (*(int *)(anim[0x11] + 0x14) == 1) {
            __asm__ __volatile__("break 0");
        }
        out->id = 1;
        func_000E75F8(out, anim, &ZeroPoint);
        func_000E7688(&out->target_speed, &out->target, base, (void *)out->unk50, *(int *)((char *)base + 0x4C), &ZeroPoint);
        return 1;
    }
    return 0;
}
