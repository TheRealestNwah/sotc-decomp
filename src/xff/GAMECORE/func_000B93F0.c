extern int AI_UpdateVelocity(float *vel, float target, float accel);

static inline void move(char *o, float speed)
{
    float t = *(float *)(o + 0x18C);
    float *vel = (float *)(o + 0x26C);

    if (t <= *(float *)(o + 0x188))
        *vel = *(float *)(o + 0x2AC) + *(float *)(o + 0x2A4) * 0.16666666f * t * t * t +
               *(float *)(o + 0x2A8) * 0.5f * t * t;
    else
        AI_UpdateVelocity(vel, speed, *(float *)(*(char **)(o + 0x64) + 0x5C));
}

static void func_000B93F0(char *o, int a, int b)
{
    float speed = *(float *)(o + 0x2A0);

    if (a == 0x13) {
        if (b == 0x11)
            move(o, speed);
        else if (b == 0x12)
            move(o, -speed);
    } else if (a == 0x14) {
        if (b == 0x11)
            move(o, -speed);
        else if (b == 0x12)
            goto last;
    }
    return;
last:
    move(o, speed);
}
