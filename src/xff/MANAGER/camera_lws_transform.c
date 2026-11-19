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
#ifdef NONMATCHING
/* 15 diffs: register allocation around the volume-rate calls and stack layout of the lo/hi bounds. */
typedef struct { float x, y, z; int w; } __attribute__((aligned(8))) V;

extern int is_sub_type_camera_lws_animation(void *);
extern int func_000E7728(void *);
extern void GetGeometryPointerQuaternion(float *, void *);
extern float GetRateInOutEllipticalSphereVolume(float *, void *, V *, V *);
extern float GetRateInOutCubeVolume(float *, void *, V *, V *);

static inline V mkV(float x, float y, float z)
{
    V v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 0;
    return v;
}

static inline void quatToMatrix(float *m, float *q, void *pos)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(m), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(pos) : "memory");
}

static float T_000E5EA0(void *animation, const Vector *reference)
{
    void **anim = animation;
    void *pos = (void *)reference;
    char *s;
    float scale = 1.0f;
    float rate;
    float d;

    s = *anim;
    if (is_sub_type_camera_lws_animation(s) == 1) {
        scale = *(float *)(s + 0x60);
        if (func_000E7728(s) == 1) {
            rate = 1.0f;
            if (*(int *)(s + 0x64) == 1) {
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vmulax.w ACC, vf0, vf7x\n"
                                     "vmadday.w ACC, vf0, vf7y\n"
                                     "vmaddz.w vf7, vf0, vf7z\n"
                                     "vsqrt Q, vf7w\n"
                                     "vwaitq\n"
                                     "cfc2.ni $2, $22\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(d) : "r"((char *)anim + 0x90), "r"(pos) : "$2", "memory");
                if (!(d <= *(float *)(s + 0x68))) {
                    if (*(float *)(s + 0x74) <= d)
                        rate = 0.0f;
                    else
                        rate = (*(float *)(s + 0x74) - d) / (*(float *)(s + 0x74) - *(float *)(s + 0x68));
                }
            } else {
                V lo;
                lo = (V){ *(float *)(s + 0x68), *(float *)(s + 0x6C), *(float *)(s + 0x70), 0 };
                {
                V hi;
                hi = (V){ *(float *)(s + 0x74), *(float *)(s + 0x78), *(float *)(s + 0x7C), 0 };
                {
                V q;
                float m[16] __attribute__((aligned(16)));
                GetGeometryPointerQuaternion((float *)&q, (char *)anim + 0x50);
                quatToMatrix(m, (float *)&q, (char *)anim + 0x90);
                {
                register int type __asm__("$4") = *(int *)(s + 0x64);
                if (type == 2)
                    rate = GetRateInOutEllipticalSphereVolume(m, pos, &lo, &hi);
                else if (type == 3)
                    rate = GetRateInOutCubeVolume(m, pos, &lo, &hi);
                }
                }
                }
            }
            if (rate < 0.0f)
                rate = 0.0f;
            scale *= rate;
        }
    }
    return scale;
}
#endif
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
