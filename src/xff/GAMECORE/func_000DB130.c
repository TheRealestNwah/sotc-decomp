typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

extern int CAM_get_ground_contact_obj(void *);
extern int GAMEUTIL_is_boss_obj(int, int);
extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);
extern int CAM_is_target_float(void *, int);
extern int func_000DB418(int *obj, char *cam, void *coll);

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline int calcDir(Vec4 *out, float *outYaw, float *outPitch, float *dir, float yawDefault)
{
    Vec4 n;
    float yaw;
    float pitch;

    if (GAMEUTIL_check_and_get_normalize_vector(n.f, 0, dir) == 1) {
        if (GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, n.f) == 0)
            yaw = yawDefault;
        if (pitch > 1.48352981f)
            pitch = 1.48352981f;
        if (pitch < -1.48352981f)
            pitch = -1.48352981f;
        GAMEUTIL_get_direction_by_yaw_pitch(n.f, yaw, pitch);
        out->q = n.q;
        *outYaw = yaw;
        *outPitch = pitch;
        return 1;
    }
    return 0;
}

static void func_000DB130(int *out, int *target, char *cam, void *coll, float yawDefault)
{
    Vec4 v;
    int r;
    int ok;

    if (GAMEUTIL_is_boss_obj(CAM_get_ground_contact_obj(cam + 0x23C), 1) == 1) {
        *out = 0;
        return;
    }
    vecSub(v.f, (float *)(cam + 0x520), (float *)(cam + 0x530));
    if (*target == 2)
        vecSub(v.f, v.f, (float *)((char *)target + 0x50));
    ok = calcDir((Vec4 *)(out + 4), (float *)(out + 8), (float *)(out + 9), v.f, yawDefault);
    if (ok == 1) {
        r = func_000DB418(out, cam, coll);
        if (r == 1) {
            if (CAM_is_target_float(cam + 0x23C, -1) == r)
                *out = 2;
            else
                *out = r;
        } else
            *out = 0;
    } else
        *out = 0;
}
