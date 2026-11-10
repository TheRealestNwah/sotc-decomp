typedef struct { char pad[0xC8]; float yaw; float pitch; } Pose;

#ifdef NONMATCHING /* 16 diffs: structure matches, only float register numbering differs (original $f5/$f3/$f1/$f4/$f2, ours $f3/$f2/$f5/$f4/$f1) */
static void func_000F2610(Pose *out, Pose *a, Pose *b, float wa, float wb)
{
    float fb = b->yaw;
    float fa = a->yaw;
    float x = fb;
    float y = fa;
    float d = x - y;
    float r;

    if (d < 0.0f ? d >= -180.0f : d <= 180.0f) {
        r = wa * fa + wb * fb;
    } else {
        if (fa < 0.0f) {
            y = fa + 360.0f;
        } else if (fb < 0.0f) {
            x = fb + 360.0f;
        }
        r = wa * y + wb * x;
        if (r > 180.0f) {
            r = r - 360.0f;
        }
    }
    out->yaw = r;
    out->pitch = wa * a->pitch + wb * b->pitch;
}
#endif
