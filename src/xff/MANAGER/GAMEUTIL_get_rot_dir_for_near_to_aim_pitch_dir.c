typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4s __attribute__((aligned(8)));
typedef union { s128 q; float f[4]; } Vec4;

extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, Vec4s *, float, Vec4s *);
extern int GAMEUTIL_act_pitch_rot(Vec4 *, Vec4 *, int, float, float, float);

#define XZ(dst, p) { Vec4s tmp_; tmp_.x = (p)[1]; tmp_.y = 0; tmp_.z = (p)[2]; tmp_.w = 0; dst = tmp_; }

#ifdef NONMATCHING
/* 21 diffs: the Original builds c's xz vector in t's slot (sp+0x10) and t's at sp+0x20; ours builds both at sp+0x20. */
int GAMEUTIL_get_rot_dir_for_near_to_aim_pitch_dir(Vec4 *out, Vec4 *cur, Vec4 *aim, int axis,
                                                   float speed, float a, float b)
{
    Vec4s c, t;
    int r;

    XZ(c, cur->f);
    XZ(t, aim->f);
    r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, &c, 0.0f, &t);
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
