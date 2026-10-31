typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    Vec4 dir;
    char pad20[0x30 - 0x20];
    Vec4 pos;
} CamTarget;

typedef struct {
    char pad0[0x23C];
    char riding[0x520 - 0x23C];
    Vec4 eye;
} Camera;

extern float get_mode_common_data_filter_base_dist_to_look_at(Camera *);
extern void *CAM_get_target_riding_obj(void *);
extern int CAM_act_ray_check_for_camera(void *, void *, void *, void *, void *, void *);

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distSq(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static int func_000DB418(CamTarget *obj, Camera *cam, void *coll)
{
    struct { Vec4 pos; char pad10[0x20]; } hit;
    Vec4 target;
    Vec4 tmp;
    float f;
    float *eye = cam->eye.f;

    f = -get_mode_common_data_filter_base_dist_to_look_at(cam);
    vecScale(tmp.f, obj->dir.f, f);
    vecAdd(target.f, eye, tmp.f);
    if (CAM_act_ray_check_for_camera(&hit, eye, &target, coll, 0,
                                     CAM_get_target_riding_obj(cam->riding)) == 1) {
        obj->pos.q = target.q;
        return 1;
    }
    if (0.02f * 0.02f <= distSq(eye, hit.pos.f)) {
        vecScale(tmp.f, obj->dir.f, 0.01f);
        vecAdd(obj->pos.f, hit.pos.f, tmp.f);
        return 1;
    }
    return 0;
}
