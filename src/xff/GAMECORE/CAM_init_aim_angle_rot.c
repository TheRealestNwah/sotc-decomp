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
    char interp[1];
} AimRot;

extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(void *, int);
extern void func_000E1620(AimRot *);

void CAM_init_aim_angle_rot(AimRot *r, int target)
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
