extern char gcGlobalVar[];
extern void reset_double_spring_interp_cntrl(char *, float);
extern void doit_double_spring_interp_cntrl(char *, float, float, int);
extern int is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl(char *);
extern float get_base_yaw_nico_yaw_pitch_cntrl(char *);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

static void func_0006F578(char *w, int reset, float speed)
{
    int dir;
    float v;
    char *ctl;

    if (reset == 1) {
        reset_double_spring_interp_cntrl(w + 0x20C, 0.0f);
        return;
    }
    ctl = w + 0xC;
    v = 0.0f;
    dir = 0;
    if (*(int *)w == 1) {
        if (is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl(ctl) == 1) {
            if (v < speed) {
                dir = 1;
            } else {
                dir = -1;
            }
        }
    } else {
        float radi = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(get_base_yaw_nico_yaw_pitch_cntrl(ctl),
                                                              *(float *)(w + 0x150));
        if (0.34906587f <= radi) {
            dir = 1;
        } else if (radi <= -0.34906587f) {
            dir = -1;
        }
    }
    if (dir == 1) {
        v = *(float *)(w + 0x2A8);
    } else if (dir == -1) {
        v = *(float *)(w + 0x2AC);
    } else {
        float lo = *(float *)(w + 0x2A0);
        float lim = *(float *)(w + 0x228);
        float hi;
        if (lo < lim) {
            v = lo;
        } else if (lim < (hi = *(float *)(w + 0x2A4))) {
            v = hi;
        } else {
            v = lim;
        }
    }
    doit_double_spring_interp_cntrl(w + 0x20C, v, *(float *)(gcGlobalVar + 0x180), 0);
}
