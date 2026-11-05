typedef struct { char pad[0x1C]; float val; } DSpring;
typedef struct { char pad[0x154]; float a; float b; float c; } ViewParam;
typedef struct { char pad[0x1370]; ViewParam *param; } CamWork;

extern void *get_cur_using_lws_anime_mode_base_class(CamWork *);
extern int is_view_angle_exist_lws_anime_mode_base(void *);
extern void reset_double_spring_interp_cntrl(DSpring *, float);
extern void set_param_double_spring_interp_common(DSpring *, float, float, float, float);
extern void doit_double_spring_interp_cntrl(DSpring *, float, float, int);
static float func_000E2B88(int, ViewParam **, void *);
static float func_000E2BB8(int, CamWork *, void *);

void doit_camera_view_angle_cntrl(DSpring *spr, CamWork *cam, int reset, float dt)
{
    ViewParam **pp = &cam->param;
    int exist = 0;
    void *anime;
    float rate, target;
    ViewParam *p;

    anime = get_cur_using_lws_anime_mode_base_class(cam);
    if (anime != 0) {
        exist = is_view_angle_exist_lws_anime_mode_base(anime);
    }
    if (reset == 1) {
        reset_double_spring_interp_cntrl(&spr[0], func_000E2B88(exist, pp, anime));
        reset_double_spring_interp_cntrl(&spr[1], 1.0f);
    } else {
        rate = func_000E2B88(exist, pp, anime);
        target = func_000E2BB8(exist, cam, anime);
        p = *pp;
        if (exist == 1) {
            DSpring *s1 = &spr[1];
            set_param_double_spring_interp_common(s1, p->a, p->c, p->b, -1.0f);
            doit_double_spring_interp_cntrl(s1, target, dt, 0);
            reset_double_spring_interp_cntrl(&spr[0], spr[1].val * rate);
        } else {
            set_param_double_spring_interp_common(&spr[0], p->a, p->c, p->b, -1.0f);
            doit_double_spring_interp_cntrl(&spr[0], target * rate, dt, 0);
            reset_double_spring_interp_cntrl(&spr[1], 1.0f);
        }
    }
    if (spr[0].val < 1.0f) {
        reset_double_spring_interp_cntrl(&spr[0], 1.0f);
    } else if (179.0f < spr[0].val) {
        reset_double_spring_interp_cntrl(&spr[0], 179.0f);
    }
}
