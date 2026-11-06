extern int GAMEUTIL_is_inside_of_region_yaw(void *, void *, float, float, float);
extern int GAMEUTIL_is_inside_of_region_pitch(void *, void *, float, float, float);
extern float D_0017B720;

static void func_000ED058(char *w, char *cam, char *prm)
{
    float pitch;

    if (*(int *)(w + 0x88) != 0)
        return;
    pitch = *(float *)(prm + 0x14);
    if (GAMEUTIL_is_inside_of_region_yaw(0, 0, *(float *)(cam + 0x110), *(float *)(prm + 0x10), *(float *)(prm + 0x2C)) &&
        GAMEUTIL_is_inside_of_region_pitch(0, 0, *(float *)(cam + 0x114), pitch, *(float *)(prm + 0x58))) {
        *(float *)(w + 0x8C) += D_0017B720;
        if (*(float *)(prm + 0x20) <= *(float *)(w + 0x8C))
            *(int *)(w + 0x88) = 1;
    } else {
        *(float *)(w + 0x8C) = 0.0f;
    }
}

typedef int s128 __attribute__((mode(TI)));

extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void reset_double_spring_interp_cntrl3D(char *, s128 *);
extern void doit_double_spring_interp_cntrl3D(char *, s128 *, int, int, float);

#ifdef NONMATCHING
typedef struct {
    int state;
    char pad4[0xC];
    s128 pos;
    char spring[1];
} SpringPos;

static void func_000ED110(SpringPos *w, float *prm, int on, s128 *pos)
{
    char one;

    set_param_double_spring_interp_common(w->spring, prm[0], prm[2], prm[1], -1.0f);
    one = 1;
    if (w->state == 0) {
        if (on == 1) {
            w->state = on;
            w->pos = *pos;
            reset_double_spring_interp_cntrl3D(w->spring, pos);
        }
    } else {
        if (on == one)
            w->pos = *pos;
        doit_double_spring_interp_cntrl3D(w->spring, &w->pos, 0, 1, D_0017B720);
    }
}
#endif
