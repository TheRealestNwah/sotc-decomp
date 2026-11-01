static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
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
static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

typedef float Vec4[4] __attribute__((aligned(16)));

extern void GAMEUTIL_get_direction_by_yaw(float *, float);
extern int CAM_get_target_obj(void *);
extern char *GetLayoutClass(int);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern float func_000DAD60(void *, int);
extern int CAM_get_target_riding_obj(void *);
extern void CAM_act_ray_check_for_camera(void *, float *, float *, int, int, int);

void act_approach_judge_ray_check_camera_target_approach(void *a0, float *pos, float *look, char *st, char *cam, int t1)
{
    Vec4 dir;
    Vec4 tmp;
    char *c = cam + 0x23C;
    float *base = (float *)(st + 0x10);
    float d;

    GAMEUTIL_get_direction_by_yaw(dir, *(float *)(st + 0x40));
    vecScale(dir, dir, -1.0f);
    vecSubXYZ(tmp, *(float **)(GetLayoutClass(CAM_get_target_obj(c)) + 0x134), base);
    d = vecDot(tmp, dir);
    vecScale(tmp, dir, d);
    vecAddXYZ(pos, base, tmp);
    pos[1] += 0.6f;
    vecScale(tmp, dir, func_000DAD60(c, GAMEUTIL_get_cur_status_status_manager(st)));
    vecAddXYZ(look, pos, tmp);
    CAM_act_ray_check_for_camera(a0, pos, look, t1, 0, CAM_get_target_riding_obj(c));
}
