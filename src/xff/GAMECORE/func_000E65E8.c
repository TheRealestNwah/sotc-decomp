/* Parked attempt: 5 differing words (entry scheduling only). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern int act_camera_cutout_game_camera_param_manager(void *, void *);
extern int CAM_get_camera_space_axisXY(void *, void *, void *, float);
extern float GAMEUTIL_get_spring_damp_offset(float, float, float, float, float, float, float, float, float);
extern int is_leave_camera_dist_to_look_at(void *);
extern int GAMEUTIL_get_offset_position_by_option_space(void *, void *, void *, int, void *, void *, void *);
extern void CAM_doit_target_offset(void *, void *, void *, int, float);
extern int GAMEUTIL_is_diff_nearly_equal_zero3D(void *, void *, float);
extern int CAM_doit_follow_rot(void *, void *, void *, float);
extern void CAM_get_camera_position_by_look_at(void *, void *, void *, float);
extern float D_0017B720;

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))

static inline float dotVector(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void subVector(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void addVector(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distVector(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline int isFixMode(char *b)
{
    int m = I(b, 0x1360);
    if (m == 0 || m == 8)
        return 1;
    return 0;
}

static inline int isNoFollow(char *b)
{
    if (isFixMode(b) == 1 || act_camera_cutout_game_camera_param_manager(b + 0x50, b) == 1)
        return 1;
    return 0;
}

static void func_000E65E8(char *a, char *b, int arg)
{
    s128 tgt[1];
    s128 sum[1];
    s128 ax[1];
    s128 ay[1];
    s128 az[1];
    s128 diff[1];
    float offs[4];
    float d[4];
    float e[4];
    int flag;
    char *cd;
    char *base;
    char *p;
    char *q;
    int m;
    int c;
    int r;

    cd = a + 0xA0;
    base = a + 0xFC0;
    flag = 0;
    tgt[0] = Q(base, 0x10);
    if (isNoFollow(b) == 1) {
        if (I(b, 0x1360) == 8)
            tgt[0] = Q(b, 0x3720);
        Q(a, 0x1010) = tgt[0];
    } else {
        az[0] = Q(cd, 0x20);
        CAM_get_camera_space_axisXY(ax, ay, az, F(a, 0x1C0));
        p = a + 0xF40;
        e[0] = dotVector(base + 0x20, ax);
        e[1] = dotVector(base + 0x20, ay);
        e[2] = dotVector(base + 0x20, az);
        subVector(diff, tgt, (a + 0x1010));
        d[0] = dotVector(diff, ax);
        d[1] = dotVector(diff, ay);
        d[2] = dotVector(diff, az);
        offs[0] = GAMEUTIL_get_spring_damp_offset(F(p, 0x70), d[0], F(p, 0x30), 0.0f, 0.0f, e[0], -1.0f, 0.001f, D_0017B720);
        offs[1] = GAMEUTIL_get_spring_damp_offset(F(p, 0x74), d[1], F(p, 0x34), 0.0f, 0.0f, e[1], -1.0f, 0.001f, D_0017B720);
        offs[2] = GAMEUTIL_get_spring_damp_offset(F(p, 0x78), d[2], F(p, 0x38), 0.0f, 0.0f, e[2], -1.0f, 0.001f, D_0017B720);
        if (is_leave_camera_dist_to_look_at(a) == 1)
            F(cd, 0x38) += offs[2];
        GAMEUTIL_get_offset_position_by_option_space((a + 0x1010), (a + 0x1010), offs, 1, ax, ay, az);
    }
    F(a, 0x1020) = distVector((a + 0x1010), cd);
    CAM_doit_target_offset(a + 0x1030, a, b, arg, D_0017B720);
    addVector(sum, (a + 0x1010), a + 0x10B0);
    q = cd + 0x10;
    if (GAMEUTIL_is_diff_nearly_equal_zero3D(q, sum, 0.001f) == 0) {
        flag = 1;
        Q(q, 0) = sum[0];
    }
    if (CAM_doit_follow_rot(a + 0x14A0, a, b, D_0017B720) == 1)
        flag = 1;
    if (flag == 1)
        CAM_get_camera_position_by_look_at(cd, cd + 0x20, q, F(cd, 0x38));
}
#endif
