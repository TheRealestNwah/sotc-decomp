/* Parked draft: updates the camera target offset. Resets it when the camera is in reset/movie/
   cutout, builds the camera rotation (axis rotation by the roll at +0x1C0), derives a forward vector
   from up x offset and normalises it, rotates the offset basis, then eases the offset with
   func_000DDAC0/DDD40/E19E0 using a distance ratio. Written from the m2c draft; not yet compared
   closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 ZeroVector;
extern void CAM_reset_target_offset(void *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern int act_camera_cutout_game_camera_param_manager(int, int);
extern void func_000DD928(void *, void *, int);
extern void func_000DDAC0(void *, void *, void *, int);
extern void func_000DDD40(void *, void *, void *, void *, float, float, void *, int);
extern void func_000E19E0(void *, void *, void *, void *, float, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern void iosRotMatrixAxis(void *, void *, int, float);
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);

static inline void cross(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(Vec4 *v)
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

void CAM_doit_target_offset(char *ctl, char *cam, int a2, int a3, float f)
{
    Vec4 outA __attribute__((aligned(16)));
    Vec4 outB __attribute__((aligned(16)));
    Vec4 dyn[2] __attribute__((aligned(16)));
    Vec4 matrix[4] __attribute__((aligned(16)));
    Vec4 up __attribute__((aligned(16)));
    Vec4 fwd __attribute__((aligned(16)));
    Vec4 side __attribute__((aligned(16)));
    float ratio;
    int forced = 0;
    int r = is_reset_or_lws_movie_or_cutout_game_camera(a2);

    if (r == 1) {
        CAM_reset_target_offset(ctl);
        if (act_camera_cutout_game_camera_param_manager(a2 + 0x50, a2) == r)
            forced = 1;
        else
            return;
    }
    func_000DD928(ctl, cam, a3);
    iosRotMatrixAxis(matrix, cam + 0xC0, 1, *(float *)(cam + 0x1C0));
    cross(&fwd, (Vec4 *)matrix, &up);
    normalize(&fwd);
    iosApplyRotMatrix(&outA, matrix, &fwd);
    cross(&side, &up, &fwd);
    iosApplyRotMatrix(&outB, matrix, &side);
    func_000DDAC0(dyn, ctl, cam, a2);
    ratio = GAMEUTIL_get_dist_ratio(*(float *)(cam + 0x1020), 0.5f, dyn[1].f[0]);
    *(Vec4 *)(ctl + 0x80) = ZeroVector;
    func_000DDD40(ctl + 0x80, ctl, dyn, ctl + 0x80, ratio, f, cam + 0xC0, forced);
    func_000E19E0(ctl + 0x80, ctl, ctl + 0x80, dyn, ratio, f);
}
#endif
