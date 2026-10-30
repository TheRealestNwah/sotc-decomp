typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);

static int func_000DB328(Vec4 *out, float *outYaw, float *outPitch, float *dir, float yawDefault)
{
    Vec4 n;
    float yaw;
    float pitch;

    if (GAMEUTIL_check_and_get_normalize_vector(n.f, 0, dir) == 1) {
        if (GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, n.f) == 0)
            yaw = yawDefault;
        if (pitch > 1.48352981f)
            pitch = 1.48352981f;
        if (pitch < -1.48352981f)
            pitch = -1.48352981f;
        GAMEUTIL_get_direction_by_yaw_pitch(n.f, yaw, pitch);
        out->q = n.q;
        *outYaw = yaw;
        *outPitch = pitch;
        return 1;
    }
    return 0;
}
