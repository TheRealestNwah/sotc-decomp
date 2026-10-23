typedef struct {
    int target;
    int a;
    int b;
    float c;
    int d;
    float max;
    float min;
    int e;
    int f;
    char interp[32];
} AimRot;

extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(void *, int);
extern void func_000E1620(AimRot *);

static inline void initAimRot(AimRot *r, int target)
{
    r->target = 0;
    r->a = 0;
    r->b = 0;
    r->c = -1.0f;
    r->d = 1;
    r->max = 1.483529806137085f;
    r->min = -1.483529806137085f;
    r->e = 1;
    r->f = 0;
    GAMEUTIL_constructor_interp_ratio_cntrl(r->interp);
    GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(r->interp, 1);
    r->target = target;
    func_000E1620(r);
}

typedef struct {
    int state;
    float yawAngle;
    float pitchAngle;
    AimRot yaw;
    AimRot pitch;
    float param1;
    float param2;
} ViewCut;

extern void CAM_set_param_view_cut_avoid_cntrl(ViewCut *, float, float);

void CAM_reset_view_cut_avoid_cntrl(ViewCut *p, int mode)
{
    p->state = 0;
    p->yawAngle = p->pitchAngle = 0.0f;
    initAimRot(&p->yaw, 0);
    initAimRot(&p->pitch, 1);
    if (mode == 1)
        CAM_set_param_view_cut_avoid_cntrl(p, 0.0f, 0.0f);
}
