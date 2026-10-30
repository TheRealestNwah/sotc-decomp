typedef float Vec4[4] __attribute__((aligned(16)));

extern int CAM_is_visible_now_target_visibility(void *);
extern int acted_camera_warp(int);
extern void *CAM_get_target_obj(void *);
extern float GAMEUTIL_get_object_move_noise(void *);
extern void iosGetExceptAxisVector(float *, float *, void *);

static inline void vecSub(float *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecLen2(float *a)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static int func_000D77D8(char *st, char *cam, float dt)
{
    Vec4 v;
    int visible;
    float noise;

    visible = CAM_is_visible_now_target_visibility(cam + 0x520);
    if (acted_camera_warp(*(int *)(cam + 0x1838)) == 1)
        return 1;
    if (visible == 1)
        *(float *)(st + 0x30) += dt;
    else
        *(float *)(st + 0x30) = 0;
    if (*(float *)(st + 0x30) >= 0.2f)
        return 1;
    if (visible == 1) {
        char *pos = cam + 0x60;
        void *target = CAM_get_target_obj(cam + 0x23C);

        noise = GAMEUTIL_get_object_move_noise(target);
        noise = noise * noise;
        vecSub(v, st + 0x10, pos);
        iosGetExceptAxisVector(v, v, st + 0x20);
        return vecLen2(v) >= noise;
    }
    return 0;
}
