/* Parked: 8 diffs, same size. Remaining: argument scheduling (mov.s
 * $f12/$f14 from $f23 issues before the daddu a2/a0 copies of w at the
 * region-check and func_000E16F0 calls) and the pitch branch's
 * temporaries ($f25/$f21 in the Original, $f22/$f21 here; reordering the
 * statements or using separate locals doesn't change them). Folding the
 * yaw branch's scaled step back into hi keeps it in $f21 like the Original.
 * The hp pointer to half is a permuter find that fixes the half/0.5f
 * registers. A 9-minute permuter run from here found nothing better. */

#ifdef NONMATCHING

extern int CAM_is_inside_of_region_aim_angle_rot(float *, float *, void *, float, float, float);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern int func_000DCC98(float *, void *, float, float, float);
extern float func_000E15F8(float, float);
extern void func_000E1650(void *);
extern void func_000E1658(void *, float, float, float, float);
extern float func_000E16F0(void *, float, float, float);
extern float powf(float, float);

typedef struct {
    int pitch;
    int active;
    int done;
    float maxVel;
    char pad10[0x10];
    int busy;
    char ratio[1];
} AimRot;

float CAM_doit_aim_angle_rot(AimRot *w, int mode, float cur, float center, float a2, float width,
                             float velA, float velB, float range, float expo, float dt)
{
    float *hp;
    register float W __asm__("$f20") = width;
    register float VB __asm__("$f22") = velB;
    register float VA __asm__("$f21") = velA;
    float rs, re;
    float out;
    float r, vA, vB, target, vel, lo, hi, half, d;
    int ret;

    out = cur;
    if (mode == 1 && w->busy == 0) {
        GAMEUTIL_doit_interp_ratio_cntrl(w->ratio, dt);
    } else if (GAMEUTIL_doit_interp_ratio_cntrl(w->ratio, -dt) <= 0.0f) {
        w->busy = 0;
        GAMEUTIL_reset_interp_ratio_cntrl(w->ratio);
    }
    func_000E1658(w, cur, center, a2, W);
    if (w->active == 0) {
        w->done = 1;
    } else {
        w->done = 0;
        hp = &half;
        ret = CAM_is_inside_of_region_aim_angle_rot(&rs, &re, w, cur, center, W);
        if (ret == 1) {
            w->done = ret;
            w->active = 0;
        } else {
            r = GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(w->ratio);
            VA = r * VA;
            VB = r * VB;
            target = func_000E16F0(w, rs, re, cur);
            if (w->pitch == 0) {
                half = range * 0.5f * 0.017453292519943295f;
                lo = VB * 0.017453292519943295f;
                hi = VA * 0.017453292519943295f;
                d = GAMEUTIL_get_difference_yaw_and_yaw(cur, target);
                hi = hi - lo;
                hi = hi * powf(func_000E15F8(d, half), expo);
                vel = lo + hi;
            } else {
                float t;
                half = range * 0.5f * 0.017453292519943295f;
                hi = VA * 0.017453292519943295f;
                d = GAMEUTIL_get_difference_pitch_and_pitch(cur, target);
                lo = VB * 0.017453292519943295f;
                t = 1.0f;
                if (!(*hp <= d))
                    t = d / half;
                vel = lo + (hi - lo) * powf(t, expo);
            }
            if (w->maxVel >= 0.0f && w->maxVel < vel)
                vel = w->maxVel;
            ret = func_000DCC98(&out, w, cur, vel * dt, target);
            if (ret == 1) {
                w->done = ret;
                w->active = 0;
            }
            if (GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(w->ratio) <= 0.0f)
                w->active = 0;
        }
    }
    if (w->active == 0 && w->done == 1) {
        func_000E1650(w);
        w->busy = 0;
        GAMEUTIL_reset_interp_ratio_cntrl(w->ratio);
    }
    return out;
}

#endif
