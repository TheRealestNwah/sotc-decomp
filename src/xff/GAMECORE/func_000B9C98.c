extern int isysGetThisSubThread(void);
extern float iosGetRandom(void);

static inline int isNear(char *o)
{
    return *(float *)(o + 0x114) <= *(float *)(o + 0x30) * 0.8f;
}

static int func_000B9C98(char *o)
{
    int behind;
    int dir;
    int back;
    float rnd;

    behind = isNear(o) ? 0 : *(float *)(o + 0x120) < -0.98480771f;
    if (behind) {
        dir = 0.0f <= *(float *)(o + 0xE8) ? 0x11 : 0x12;
        back = *(float *)(o + 0x120) < -0.2f;
        if (back) {
            return dir == 0x11 ? 0x1E : 0x1F;
        }
    } else if (!isNear(o)) {
        dir = 0.0f <= *(float *)(o + 0xE8) ? 0x11 : 0x12;
    } else {
        rnd = iosGetRandom();
        dir = *(int *)(o + 0x170);
        if (*(float *)(o + 0x190) < *(float *)(o + 0x194)) {
            if (rnd < 0.5f) {
                dir = 0x11;
            } else if (rnd < 1.0f) {
                dir = 0x12;
            } else {
                dir = 0x10;
            }
        }
    }
    return dir == 0x11 ? 0x1C : 0x1D;
}

static int func_000B9E08(char *o)
{
    int near;
    int wide;
    int dir;

    isysGetThisSubThread();
    near = *(float *)(o + 0x114) <= *(float *)(o + 0x30) * 0.8f;
    if (near) {
        if (*(float *)(o + 0xB0) < 8.0f) {
            dir = *(float *)(o + 0x88) >= 0.0f ? 0x16 : 0x15;
        } else {
            dir = *(float *)(o + 0x88) >= 0.0f ? 0x16 : 0x15;
        }
        if (dir == 0x15) {
            return 0x1C;
        }
        if (dir == 0x16) {
            return 0x1D;
        }
        if (dir == 0x17) {
            return 0x1E;
        }
        if (dir == 0x18) {
            return 0x1F;
        }
    } else {
        wide = 0.70710665f <= *(float *)(o + 0x120);
        if (!wide) {
            return func_000B9C98(o);
        }
    }
    return 0x1A;
}
