extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, float *, float, float *);
extern float iosGetACosfExact(float x);

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

float GAMEUTIL_get_move_radi_yaw_dir(float *dir, float *aim)
{
    float zero = 0.0f;
    float result;
    int rot = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, dir, zero, aim);

    if (rot == 1) {
        result = iosGetACosfExact(vecDot(dir, aim));
    } else if (rot == -1) {
        result = -iosGetACosfExact(vecDot(dir, aim));
    } else {
        result = zero;
    }
    return result;
}
