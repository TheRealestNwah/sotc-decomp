typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { float x, y, z, w; } Vec4s;

extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, Vec4s, Vec4s, float);
extern int GAMEUTIL_act_pitch_rot(Vec4 *, Vec4 *, int, float, float, float);

#ifdef NONMATCHING
/* 65 diffs: original builds the xz vectors in temporaries and copies them into the by-value argument slots */
int GAMEUTIL_get_rot_dir_for_near_to_aim_pitch_dir(Vec4 *out, Vec4 *cur, Vec4 *aim, int axis,
                                                   float speed, float a, float b)
{
    Vec4s c, t;
    int r;

    c.x = cur->f[1];
    c.y = 0;
    c.z = cur->f[2];
    c.w = 0;
    t.x = aim->f[1];
    t.y = 0;
    t.z = aim->f[2];
    t.w = 0;
    r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, c, t, t.y);
    if (out != 0) {
        if (r == 0)
            out->q = cur->q;
        else if (r == 1)
            GAMEUTIL_act_pitch_rot(out, cur, axis, speed, a, b);
        else
            GAMEUTIL_act_pitch_rot(out, cur, axis, -speed, a, b);
    }
    return r;
}
#endif
