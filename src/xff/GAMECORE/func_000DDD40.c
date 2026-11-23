typedef int s128 __attribute__((mode(TI)));

extern float GAMEUTIL_get_interp_value(float, float, float);
extern void GAMEUTIL_get_offset_position_by_option_space(void *, void *, float *, int, void *, void *, void *);
extern int GAMEUTIL_get_riding_horse_object(int);
extern int act_horse_look_at_ofst_decrease_camera_place_status(void *);
extern int act_look_at_ofst_cut_camera_place_status(void *);
extern float doit_double_spring_interp_cntrl(void *, int, float, float);
extern void *doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern float func_000DE0A8(void *, void *, void *, int, float);
extern int func_000E1AD0(void *, void *);
extern void set_param_double_spring_interp_common(void *, float, float, float, float);
extern char ZeroPoint[];

static void func_000DDD40(void *out, char *obj, float *prm, void *add, float ratio, float dt,
                          char *cam, int forced, void *m1, void *m2, void *pos, int opt)
{
    float v[4];
    float *p;
    char *q;
    float a, b, ofs, w, s;
    int mode;
    char *dst;
    void *r;

    p = (float *)(cam + 0x14);
    q = cam + 0xFC0;
    ofs = func_000DE0A8(obj, prm, cam, forced, dt);
    w = 1.0f;
    mode = *(int *)(*(char **)cam + 0x18);
    a = p[2];
    b = p[4];
    if (mode == 1) {
        if (act_look_at_ofst_cut_camera_place_status(cam + 0x1270) == mode) {
            b = 0.0f;
            a = b;
        } else if (act_horse_look_at_ofst_decrease_camera_place_status(cam + 0x1270) == mode &&
                   GAMEUTIL_get_riding_horse_object(*(int *)(cam + 0x23C)) != 0) {
            a *= 0.5f;
            b *= 0.5f;
        }
    }
    v[0] = ofs * (p[1] + a * *(float *)(q + 0x40)) + (p[3] + b * *(float *)(q + 0x40));
    v[1] = p[5] + p[6] * *(float *)(q + 0x44);
    v[2] = v[3] = 0.0f;
    if (*(int *)(obj + 0x144) == 1) {
        float l0, l1;
        char *c = *(char **)cam;
        l0 = *(float *)(c + 0x44);
        if (l0 >= 0.0f) {
            if (v[0] < 0.0f ? l0 < -v[0] : l0 < v[0]) {
                if (v[0] >= 0.0f)
                    v[0] = l0;
                else
                    v[0] = -l0;
            }
        }
        l1 = *(float *)(c + 0x48);
        if (l1 >= 0.0f) {
            if (v[1] < 0.0f ? l1 < -v[1] : l1 < v[1]) {
                if (v[1] >= 0.0f)
                    v[1] = l1;
                else
                    v[1] = -l1;
            }
        }
    }
    GAMEUTIL_get_offset_position_by_option_space(obj + 0x60, ZeroPoint, v, 1, m1, m2, pos);
    if (func_000E1AD0(p, cam) == 1) {
        dst = obj + 0x70;
        v[0] *= *(float *)(obj + 0x17C);
        GAMEUTIL_get_offset_position_by_option_space(dst, ZeroPoint, v, 1, m1, m2, pos);
        w = GAMEUTIL_get_interp_value(1.0f, prm[3], *(float *)(obj + 0x17C));
    } else {
        *(s128 *)(obj + 0x70) = *(s128 *)(obj + 0x60);
        dst = obj + 0x70;
    }
    s = doit_double_spring_interp_cntrl(obj + 0x90, 0, w, dt);
    set_param_double_spring_interp_common(obj, s * prm[0], s * prm[2], s * prm[1], -1.0f);
    r = doit_double_spring_interp_cntrl3D(obj, dst, opt, dt);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(add), "r"(r) : "memory");
}
