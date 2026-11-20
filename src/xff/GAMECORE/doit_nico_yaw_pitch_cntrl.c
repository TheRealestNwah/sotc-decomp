typedef struct {
    char pad0[0x2C];
    int active;
    char pad30[0xD0 - 0x30];
    float yawVec[4];
    char padE0[0xEC - 0xE0];
    float pitchVec[4];
    char padFC[0x130 - 0xFC];
    int flipYaw;
    int flipPitch;
    float yawScale;
    float pitchScale;
} NicoYawPitchCntrl;

extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern void func_0000DCF8(NicoYawPitchCntrl *, float, float);
extern void func_0000DD58(float *, float *, NicoYawPitchCntrl *);
extern void func_0000C820(NicoYawPitchCntrl *, float);
extern void func_0000DDC0(NicoYawPitchCntrl *, float);
extern void func_0000C9E8(NicoYawPitchCntrl *, float, float *);
extern void func_0000CBA0(NicoYawPitchCntrl *, float, float *);

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static void func_0000DB18(float *a, float *b, float x, float y)
{
    float v[4] __attribute__((aligned(16)));
    float m;

    v[0] = x;
    v[1] = y;
    v[2] = 0.0f;
    v[3] = 0.0f;
    if (GAMEUTIL_check_and_get_normalize_vector(v, 0, v) == 1) {
        m = ABS(v[0]);
        if (m < ABS(v[1]))
            m = ABS(v[1]);
        m = 1.0f / m;
        *a = m * x;
        *b = m * y;
        if (ABS(*a) > 1.0f) {
            if (*a >= 0.0f)
                *a = 1.0f;
            else
                *a = -1.0f;
        }
        if (ABS(*b) > 1.0f) {
            if (*b >= 0.0f)
                *b = 1.0f;
            else
                *b = -1.0f;
        }
    } else {
        *a = x;
        *b = y;
    }
}

void doit_nico_yaw_pitch_cntrl(NicoYawPitchCntrl *c, float yaw, float pitch)
{
    float m[8];
    float a, b, y, p;

    if (c->active == 1) {
        pitch = -pitch;
        m[0] = c->yawScale * c->yawVec[0];
        m[1] = c->yawScale * c->yawVec[1];
        m[2] = c->yawScale * c->yawVec[2];
        m[3] = c->yawScale * c->yawVec[3];
        m[4] = c->pitchScale * c->pitchVec[0];
        m[5] = c->pitchScale * c->pitchVec[1];
        m[6] = c->pitchScale * c->pitchVec[2];
        m[7] = c->pitchScale * c->pitchVec[3];
        if (c->flipYaw == 1)
            yaw = -yaw;
        if (c->flipPitch == 1)
            pitch = -pitch;
        func_0000DB18(&a, &b, yaw, pitch);
                do {
func_0000DCF8(c, a, b);
        func_0000DD58(&y, &p, c);
        func_0000C820(c, y);
        func_0000DDC0(c, p);
        } while (0);
        func_0000C9E8(c, a, m);
        func_0000CBA0(c, b, m);
    }
}
