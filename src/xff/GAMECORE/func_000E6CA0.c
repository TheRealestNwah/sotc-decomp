typedef int s128 __attribute__((mode(TI)));

extern int act_camera_cutout_game_camera_param_manager(void *, void *);
extern void drop_camera_cutout_flag_game_camera_param_manager(void *, void *);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);
extern void func_000ECCF8(char *, char *, int);
extern float D_0017B720;

typedef union { s128 q; float f[4]; } __attribute__((aligned(16))) V4;
typedef struct {
    V4 q0;
    V4 q1;
    V4 q2;
    float yaw;
    float pitch;
    float z;
} Blk;

static inline int resetOrMovieOrCutout(char *camera)
{
    int mode = *(int *)(camera + 0x1360);
    int reset;
    if (mode == 0 || mode == 8)
        reset = 1;
    else
        reset = 0;
    if (reset == 1 || act_camera_cutout_game_camera_param_manager(camera + 0x50, camera) == 1)
        return 1;
    return 0;
}

static inline void copyBlk(Blk *dst, Blk *src)
{
    dst->q0.q = src->q0.q;
    dst->q1.q = src->q1.q;
    dst->q2.q = src->q2.q;
    dst->yaw = src->yaw;
    dst->pitch = src->pitch;
    dst->z = src->z;
}

static inline float distXZ(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static void func_000E6CA0(char *self, char *cam, int arg)
{
    Blk *next = (Blk *)(self + 0xE0);
    Blk *prev = (Blk *)(self + 0x160);
    Blk *base = (Blk *)(self + 0xA0);
    Blk *cur = (Blk *)(self + 0x60);
    float f;

    if (resetOrMovieOrCutout(cam) == 0 && *(int *)(self + 0x1838) != 1 && D_0017B720 != 0.0f) {
        *(float *)(self + 0x234) = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(cur->yaw, next->yaw) / D_0017B720;
        f = GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(cur->pitch, next->pitch) / D_0017B720;
    } else {
        f = 0.0f;
        *(float *)(self + 0x234) = f;
    }
    *(float *)(self + 0x238) = f;
    func_000ECCF8(self, cam, arg);
    copyBlk(prev, cur);
    copyBlk(cur, next);
    copyBlk(base, cur);
    *(float *)(self + 0x1A0) = distXZ(&cur->q1, &cur->q0);
    drop_camera_cutout_flag_game_camera_param_manager(cam + 0x50, &cur->q1);
    *(int *)(self + 4) = *(int *)(*(char **)self + 8);
    *(int *)(self + 8) = *(int *)(*(char **)self + 0xC);
}
