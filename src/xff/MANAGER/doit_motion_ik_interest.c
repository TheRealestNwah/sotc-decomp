typedef int s128 __attribute__((mode(TI)));
typedef float FVEC[4] __attribute__((aligned(16)));

extern void *DldSysUndefSymbol;

typedef struct {
    float unk00;
    float unk04;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
} IkParam;

typedef struct {
    int unk00;
    int state;
    int mode;
    int reset;
    char spring[0x10];
    float speed;
    char pad24[0xC];
    FVEC goal;
    FVEC cur;
    FVEC unk50;
    char pad60[0x10];
    FVEC last;
    int done[3];
} IkInterest;

extern void doit_motion_ik_base(IkInterest *, void *, void *, float);
extern unsigned int *get_type_parameter_segment_motion_ik_base(IkInterest *);
extern void get_animation_designer_node_rotXYZ_motion_ik_base(float *, IkInterest *);
extern void func_0003E918(float *, IkInterest *, IkInterest *, void *, float *);
extern void func_0003EEC0(IkInterest *, float *, float *, IkParam *);
extern void reset_double_spring_interp_cntrl3D(void *, float *);
extern void set_param_double_spring_interp_common(void *, float, float, float, float);
extern void doit_double_spring_interp_cntrl3D(void *, float *, int, float);
extern int GAMEUTIL_is_diff_nearly_equal_zero(float, float, float);
extern int GAMEUTIL_is_between_value(int, float, float, float);
extern void update_node_by_rotXYZ_motion_ik_base(IkInterest *, float *);

static inline void *resourceModuleData(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol)
        return *(void **)(module + 0x10);
    return 0;
}

static inline void vecSub(float *d, float *a, float *b)
{
    __asm__ volatile(
        "lqc2 $vf5, 0(%1)\n"
        "lqc2 $vf6, 0(%2)\n"
        "vsub.xyz $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(float *d, float *a, float *b)
{
    __asm__ volatile(
        "lqc2 $vf5, 0(%1)\n"
        "lqc2 $vf6, 0(%2)\n"
        "vadd.xyz $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

void doit_motion_ik_interest(IkInterest *ik, void *a1, void *a2, float dt)
{
    FVEC base;
    FVEC rot;
    FVEC last;
    FVEC hi;
    FVEC diff;
    IkParam *param;
    int i;

    if (ik->state == 1) {
        doit_motion_ik_base(ik, a1, a2, dt);
        param = resourceModuleData(get_type_parameter_segment_motion_ik_base(ik));
        get_animation_designer_node_rotXYZ_motion_ik_base(rot, ik);
        func_0003E918(base, ik, ik, a2, rot);
        if (ik->reset == 1) {
            reset_double_spring_interp_cntrl3D(ik->spring, rot);
            ik->reset = 0;
            *(s128 *)ik->unk50 = *(s128 *)rot;
            *(s128 *)ik->last = *(s128 *)rot;
        }
        func_0003EEC0(ik, base, rot, param);
        if (ik->mode == 1) {
            for (i = 0; i < 3; i++) {
                if (ik->done[i] == 1) {
                    ik->cur[i] = rot[i];
                    ik->goal[i] = rot[i];
                }
            }
        }
        set_param_double_spring_interp_common(ik->spring, param->unk0C, param->unk14 * 0.017453293f, param->unk10, -1.0f);
        doit_double_spring_interp_cntrl3D(ik->spring, ik->unk50, 0, dt);
        if (ik->mode == 1) {
            float tol = ik->speed * 5.0f;
            *(s128 *)last = *(s128 *)ik->last;
            vecSub(diff, rot, ik->last);
            vecAdd(hi, rot, diff);
            for (i = 0; i < 3; i++) {
                if (ik->done[i] == 0) {
                    if (GAMEUTIL_is_diff_nearly_equal_zero(ik->cur[i], rot[i], tol) == 1
                        || GAMEUTIL_is_between_value(0, ik->cur[i], last[i], hi[i]) == 1)
                        ik->done[i] = 1;
                }
            }
            if (*(long long *)ik->done == 0x100000001LL && ik->done[2] == 1)
                ik->state = 0;
        } else {
            ik->done[2] = 0;
            ik->done[1] = 0;
            ik->done[0] = 0;
        }
        *(s128 *)ik->last = *(s128 *)rot;
        update_node_by_rotXYZ_motion_ik_base(ik, ik->cur);
    }
}
