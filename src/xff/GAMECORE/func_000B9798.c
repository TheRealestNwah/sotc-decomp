extern int isysGetThisSubThread(void);
extern int AI_UpdateVelocity(float *, float, float);
extern void *GetCharacterClass(int);
extern void AI_GetTimeOfCurrMotion(void *, float);

#define F(o, x) (*(float *)((char *)(o) + (x)))

static void func_000B9798(char *o)
{
    float *v = (float *)(o + 0x238);
    int th = isysGetThisSubThread();
    float t;
    float s;
    float d;

    s = F(*(char **)(o + 0x64), 0x68);
    F(o, 0x260) = s;
    AI_UpdateVelocity((float *)(o + 0x264), s, F(*(char **)(o + 0x64), 0x6C));
    if ((unsigned int)(*(int *)(o + 0x178) - 0x1E) < 2) {
        t = F(o, 0x18C);
        F(o, 0x210) = F(o, 0x2B8) + F(o, 0x2B0) * 0.5f * t * t + F(o, 0x2B4) * t;
        AI_UpdateVelocity(v, F(*(char **)(o + 0x64), 0x40), F(*(char **)(o + 0x64), 0x3C));
        AI_UpdateVelocity((float *)(o + 0x218), 0.0f, *v);
        return;
    }
    t = F(o, 0x18C);
    if (t <= F(o, 0x2BC))
        F(o, 0x210) = F(o, 0x2B8) + F(o, 0x2B0) * 0.5f * t * t + F(o, 0x2B4) * t;
    else
        AI_UpdateVelocity((float *)(o + 0x210), 0.0f, 0.1f);
    t = F(o, 0x18C);
    if (F(o, 0x2CC) <= t) {
        d = t - F(o, 0x2CC);
        F(o, 0x218) = F(o, 0x2C8) + F(o, 0x2C0) * 0.5f * d * d + F(o, 0x2C4) * d;
    }
    if (*(int *)(o + 0xC) != 0)
        return;
    AI_GetTimeOfCurrMotion(GetCharacterClass(th), 1.0f);
}

