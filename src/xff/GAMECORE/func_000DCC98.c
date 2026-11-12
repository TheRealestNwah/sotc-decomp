#ifdef NONMATCHING
/* Parked: 9 words differ (prologue saves s0 before s2/f20, and gcc threads the st!=1 branch past the dispatch's first test). */
typedef struct {
    int mode;
    int state;
    char pad8[8];
    int request;
    float high;
    float low;
    int clip;
} AimCtl;

extern int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *, float, float, float);
extern int GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(float, float, float, float, float, float *, int);
extern float GAMEUTIL_increase_yaw(int *, float, float);
extern int GAMEUTIL_is_reach_aim_yaw_angle(float *out, float a, float b, float aim);
extern int GAMEUTIL_is_reach_aim_pitch_angle(float *out, float from, float next, float aim);

static int func_000DCC98(float *out, AimCtl *s, float from, float step, float aim)
{
    int st;

    *out = from;
    if (s->mode == 0) {
        if (s->request == 1) {
            s->state = 1;
            st = 1;
        } else {
            st = s->state;
            if (s->state == 1) {
                int dir = GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(0, from, 1.0f, aim);
                if (dir == st) {
                    s->state = 2;
                    st = 2;
                } else if (dir == -1) {
                    s->state = 3;
                    st = 3;
                } else {
                    s->state = 0;
                    st = 0;
                }
            }
        }
        if (st == 1) {
            GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(out, from, step, aim);
        } else if (st == 2) {
            *out = GAMEUTIL_increase_yaw(0, from, step);
        } else if (st == 3) {
            *out = GAMEUTIL_increase_yaw(0, from, -step);
        } else {
            __asm__ __volatile__("break 0");
        }
        return GAMEUTIL_is_reach_aim_yaw_angle(out, from, *out, aim);
    }
    GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(from, step, aim, s->high, s->low, out, s->clip);
    return GAMEUTIL_is_reach_aim_pitch_angle(out, from, *out, aim);
}
#endif
