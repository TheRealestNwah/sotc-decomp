typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) V4;

extern float D_0017B720;
extern int get_status_camera_target_approach(void *);
extern int CAM_is_target_fast_moving(void *);
extern void *CAM_get_target_obj(void *);
extern void GAMEUTIL_get_local_directionZ(float *, void *);
extern float iosGetCosf(float);

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static void func_000EC1B8(char *cam)
{
    V4 dir;
    float d;
    float v;
    int fast;

    if (get_status_camera_target_approach(cam + 0x6A0) == 1) {
        fast = 0;
        if (CAM_is_target_fast_moving(cam + 0x23C) == 1) {
            GAMEUTIL_get_local_directionZ(&dir.x, CAM_get_target_obj(cam + 0x23C));
            d = vecDot(&dir.x, (float *)(cam + 0x80));
            if (d <= iosGetCosf((120.0f * 0.0174532925f))) {
                fast = 1;
            }
        }
        if (fast == 1) {
            *(float *)(cam + 0x1828) = 3.8f;
        } else {
            v = *(float *)(cam + 0x1828) - D_0017B720;
            *(float *)(cam + 0x1828) = v;
            if (v < 0.0f) {
                *(float *)(cam + 0x1828) = 0.0f;
            }
        }
    } else {
        *(float *)(cam + 0x1828) = 0.0f;
    }
}
