typedef struct { char pad[0xC8]; float yaw; float pitch; } Pose;

static void func_000F2610(Pose *out, Pose *a, Pose *b, float wa, float wb)
{
    float fb = b->yaw;
    float fa = a->yaw;
    register float x __asm__("$f1") = fb;
    register float y __asm__("$f4") = fa;
    register float d __asm__("$f2") = x - y;
    float r;

    if (d < 0.0f ? d >= -180.0f : d <= 180.0f) {
        r = wa * fa + wb * fb;
    } else {
        if (fa < 0.0f) {
            { register float k __asm__("$f0") = 360.0f; y = fa + k; }
        } else if (fb < 0.0f) {
            { register float k __asm__("$f0") = 360.0f; x = fb + k; }
        }
        { register float p __asm__("$f0") = wa * y; r = p + wb * x; }
        if (r > 180.0f) {
            r = r - 360.0f;
        }
    }
    out->yaw = r;
    out->pitch = wa * a->pitch + wb * b->pitch;
}
