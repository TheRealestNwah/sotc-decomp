typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4s __attribute__((aligned(8)));
typedef union { s128 q; float f[4]; } Vec4;

extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, Vec4s *, float, Vec4s *);
/* The Original's call sites load the float arguments before the axis, as gcc does when the
 * prototype lists the int last (same EABI registers as GAMEUTIL_act_pitch_rot's definition). */
extern int GAMEUTIL_act_pitch_rot(Vec4 *, Vec4 *, float, float, float, int);

int GAMEUTIL_get_rot_dir_for_near_to_aim_pitch_dir(Vec4 *out, Vec4 *cur, Vec4 *aim, int axis,
                                                   float speed, float a, float b)
{
    Vec4s c = {cur->f[1], 0, cur->f[2], 0};
    Vec4s t = {aim->f[1], 0, aim->f[2], 0};
    int r;

    r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, &c, 0.0f, &t);
    if (out != 0) {
        if (r == 0)
            out->q = cur->q;
        else if (r == 1)
            GAMEUTIL_act_pitch_rot(out, cur, speed, a, b, axis);
        else
            GAMEUTIL_act_pitch_rot(out, cur, -speed, a, b, axis);
    }
    return r;
}
