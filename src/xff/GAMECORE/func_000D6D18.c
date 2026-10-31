typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x50];
    Vec4 dir;
    char pad60[0x780 - 0x60];
    Vec4 base[6];
} CamWork;

typedef struct {
    int mode;
    char pad4[0x23C - 4];
    char target[1];
} CamCtrl;

extern Vec4 ZUnitVectorInv;
extern int get_base_default_direction(Vec4 *, Vec4 *, Vec4 *, Vec4 *, Vec4 *, Vec4 *, Vec4 *, int, CamCtrl *);
extern void *CAM_get_target_obj(void *);
extern void *GetCharacterClass(void *);
extern void GetCharacterClassControlFrontDirection(Vec4 *, void *);
extern int GAMEUTIL_is_yaw_pitch_get_direction(float *);

static inline void vecLerp(float *out, float *a, float *b, float t)
{
    __asm__ __volatile__(".set noreorder
"
                         "mfc1 $8, %0
"
                         "qmtc2.ni $8, vf7
"
                         "lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsubx.w vf8, vf0, vf7x
"
                         "vmulax.xyz ACC, vf5, vf7x
"
                         "vmaddw.xyz vf5, vf6, vf8w
"
                         "sqc2 vf5, 0x0(%3)
"
                         ".set reorder
"
                         : : "f"(t), "r"(a), "r"(b), "r"(out) : "memory", "$8");
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static void func_000D6D18(Vec4 *out, CamWork *w, CamCtrl *c)
{
    Vec4 *prev = &w->dir;
    Vec4 tmp;
    void *cls;

    if (!get_base_default_direction(out, &w->base[0], &w->base[1], &w->base[2], &w->base[3], &w->base[4],
                                    &w->base[5], c->mode, c)) {
        cls = GetCharacterClass(CAM_get_target_obj(c->target));
        if (cls)
            GetCharacterClassControlFrontDirection(out, cls);
        else
            out->q = ZUnitVectorInv.q;
    }
    if (!GAMEUTIL_is_yaw_pitch_get_direction(out->f)) {
        vecLerp(tmp.f, out->f, prev->f, 0.5f);
        vecNormalize(tmp.f);
        if (GAMEUTIL_is_yaw_pitch_get_direction(tmp.f) == 1)
            out->q = tmp.q;
        else
            out->q = prev->q;
    }
    w->dir.q = out->q;
}
