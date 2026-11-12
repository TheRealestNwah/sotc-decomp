typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float GAMEUTIL_get_interp_value(float, float, float);
extern float GAMEUTIL_get_interp_yaw(float, float, float);
extern float GAMEUTIL_get_interp_pitch(float, float, float);
extern void GAMEUTIL_check_and_get_normalize_vector(void *, float *, void *);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);

static inline void vsub3(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void lerp3(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    register int ti __asm__("$8");
    __asm__("mfc1 %0, %1" : "=r"(ti) : "f"(t));
    __asm__ __volatile__("qmtc2.ni %3, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "r"(ti) : "memory");
}

static inline void scaleAdd(Vec4 *out, Vec4 *base, Vec4 *dir, float s, Vec4 *tmp)
{
    register Vec4 *tp __asm__("$2") = tmp;
    __asm__ __volatile__("mfc1 $3, %4\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "qmtc2.ni $3, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(base), "r"(dir), "r"(tp), "f"(s) : "$3", "memory");
}

void CAM_get_interp_cam_and_look_at_posi(Vec4 *outCam, Vec4 *outLook, Vec4 *cam0, Vec4 *cam1,
                                         Vec4 *look0, Vec4 *look1, int flag, float ra, float rb)
{
    Vec4 d0, d1, dir, t0, t1;
    float len0, len1, yaw0, pitch0, yaw1, pitch1, len, yaw, pitch;

    if (ra <= 0.0f && rb <= 0.0f) {
        outCam->q = cam0->q;
        outLook->q = cam1->q;
        return;
    }
    if (ra >= 1.0f && rb >= 1.0f) {
        outCam->q = look0->q;
        outLook->q = look1->q;
        return;
    }
    vsub3(&d0, cam1, cam0);
    GAMEUTIL_check_and_get_normalize_vector(&d0, &len0, &d0);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw0, &pitch0, &d0);
    vsub3(&d1, look1, look0);
    GAMEUTIL_check_and_get_normalize_vector(&d1, &len1, &d1);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw1, &pitch1, &d1);
    len = GAMEUTIL_get_interp_value(len1, len0, rb);
    yaw = GAMEUTIL_get_interp_yaw(yaw0, yaw1, ra);
    pitch = GAMEUTIL_get_interp_pitch(pitch0, pitch1, ra);
    GAMEUTIL_get_direction_by_yaw_pitch(&dir, yaw, pitch);
    if (flag == 0) {
        lerp3(outCam, look0, cam0, rb);
        scaleAdd(outLook, outCam, &dir, len, &t0);
    } else {
        lerp3(outLook, look1, cam1, ra);
        scaleAdd(outCam, outLook, &dir, -len, &t1);
    }
}
