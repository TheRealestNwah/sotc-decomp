typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void *CAM_get_target_obj(void *);
extern float GAMEUTIL_get_object_move_noise(void *);
extern void GAMEUTIL_set_parameter_col_plane_info_filter(char *, float, float);
extern void GAMEUTIL_doit_col_plane_info_filter(char *, char *, float);
extern void func_000DA3E0(char *, char *, float *, int, float);
extern void func_000DA4D0(char *, char *, float *);
extern void func_000DA288(char *, char *);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void doit_double_spring_interp_cntrl(char *, int, float, float);
static inline void vecNormalize(void *v)
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

void CAM_doit_slope_cntrl(char *w, char *cam, int mode, float dt)
{
    Vec4 dir;
    void *obj;
    char *p;

    obj = CAM_get_target_obj(cam + 0x23C);
    dir.q = *(s128 *)(cam + 0xC0);
    dir.f[1] = 0.0f;
    vecNormalize(&dir);
    GAMEUTIL_set_parameter_col_plane_info_filter(w + 0x40, GAMEUTIL_get_object_move_noise(obj), 0.5f);
    GAMEUTIL_set_parameter_col_plane_info_filter(w + 0xC0, GAMEUTIL_get_object_move_noise(obj), 0.5f);
    GAMEUTIL_doit_col_plane_info_filter(w + 0x40, cam + 0x1440, dt);
    GAMEUTIL_doit_col_plane_info_filter(w + 0xC0, cam + 0x1440, dt);
    func_000DA3E0(w, cam, dir.f, mode, dt);
    func_000DA4D0(w, cam, dir.f);
    func_000DA288(w, cam);
    p = *(char **)cam;
    set_param_double_spring_interp_common(w, *(float *)(p + 0xD4), *(float *)(p + 0xDC), *(float *)(p + 0xD8), -1.0f);
    doit_double_spring_interp_cntrl(w, 0, *(float *)(w + 0x38), dt);
}
