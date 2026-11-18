typedef struct { char pad[0x180]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern float func_0000E370(int, int, int, int, float, float, float);
extern float GAMEUTIL_get_new_velocity(float, float, float, float, float);
extern float GAMEUTIL_get_new_velocity_by_brake_abs(float, float, float, float);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);

static float func_0000E1D8(float *out, int on, int lock, int left, int right, float range, float d, float cur, float accel,
                           float maxv, float brake, int unused, float scale, float angle, float in, float lim)
{
    float spd = cur;
    float target;
    float vel;
    float dir;

    if (cur < 0.0f)
        spd = -cur;
    target = func_0000E370(on, lock, left, right, range, d, scale);
    if (spd <= target)
        vel = GAMEUTIL_get_new_velocity(spd, accel, maxv, target, gcGlobalVar.dt);
    else
        vel = GAMEUTIL_get_new_velocity_by_brake_abs(spd, brake, target, gcGlobalVar.dt);
    if (target <= 0.0f && 0.0f < spd)
        dir = cur;
    else
        dir = d;
    if (!GAMEUTIL_is_nearly_equal_zero(in, 0.0001f) && 0.0f <= dir * in) {
        if (lim * scale < vel)
            vel = lim * scale;
    }
    *out = vel;
    if (dir < 0.0f)
        *out = -vel;
    return *out * gcGlobalVar.dt;
}
