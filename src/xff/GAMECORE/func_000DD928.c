typedef int s128 __attribute__((mode(TI)));

static inline void vecScaleXYZ(float *dst, float *v, float s)
{
    __asm__ __volatile__("mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(v), "f"(s) : "$2", "memory");
}

static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDist2(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

typedef struct {
    char pad0[0x44];
    float f44;
    float f48;
} CamSub;

extern char *GetLayoutClass(void *);
extern float GAMEUTIL_get_object_move_noise(void *);
extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern int camera_collision_check_direct(void *, void *, void *, void *, int, int, void *, int);

static void func_000DD928(char *w, char *cam, void *to)
{
    float pos[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    char hit[0x50] __attribute__((aligned(16)));
    char *tgt;
    char *lay;
    float noise;
    float d2;
    int r;
    CamSub *sub = *(CamSub **)cam;

    if (0.0f <= sub->f44 || 0.0f <= sub->f48) {
        tgt = cam + 0x23C;
        lay = GetLayoutClass(*(void **)tgt);
        if (*(int *)(w + 0x144) == 1) {
            noise = GAMEUTIL_get_object_move_noise(*(void **)tgt);
            d2 = vecDist2(*(float **)(lay + 0x134), (float *)(w + 0x150));
            if (noise * noise <= d2) {
                *(int *)(w + 0x144) = 0;
            }
        }
        if (*(int *)(cam + 0x1834) != 0) {
            return;
        }
        vecSubXYZ(d, (float *)(cam + 0x70), *(float **)(lay + 0x134));
        r = GAMEUTIL_check_and_get_normalize_vector(d, 0, d);
        if (r != 1) {
            return;
        }
        vecScaleXYZ(d, d, 0.29999999f);
        vecAddXYZ(pos, (float *)(cam + 0x70), d);
        if (camera_collision_check_direct(hit, *(void **)(lay + 0x134), pos, to, 1, 0, *(void **)(tgt + 0x2C8), 1) == 0) {
            return;
        }
        *(int *)(w + 0x144) = r;
        *(s128 *)(w + 0x150) = *(s128 *)*(int *)(lay + 0x134);
    } else {
        *(int *)(w + 0x144) = 0;
    }
}
