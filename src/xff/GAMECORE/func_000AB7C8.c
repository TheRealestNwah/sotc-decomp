#ifdef NONMATCHING
/* ~110 diffs, same length (153 words). Draft from the asm: update of an AI actor's wander/speed fields (actor o, config block P = o+0x34, a3 = the second argument): picks a random velocity (AI_GetRandomVelocity) or copies the preset one, smooths it with AI_UpdateVelocity, derives o+0x2D0 by remapping o+0x2C8 from [P+0x20,P+0x24] to [P+0x28,P+0x2C], gets the motion velocity into o+0x330, updates o+0x2E0/0x2F8/0x2DC/0x2F4, sets the sign of o+0x314 from a3+0x10, and then either clears o+0x31C (target within P[0]/P[1] range) or draws a new random one clamped to <= 0. The Original keeps no callee-saved float (no f20) and loads the 1.0 constant right where it is used; ours hoists it into f20 before the first mul (frame is the same 0x40), which shifts the scheduling of everything after it. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern void AI_GetRandomVelocity(float *, void *, void *, float, float, float, float);
extern void AI_UpdateVelocity(float *, float, float);
extern void AI_GetMotionBasicVelocity(Vec4 *, void *, float);

#define PP (*(float **)(o + 0x34))
#define PPX PP
static void func_000AB7C8(char *o, char *a3)
{
    Vec4 vel;
    char *cc;
    float *p;
    float f;

    cc = GetCharacterClass(isysGetThisSubThread());
    if (*(int *)(o + 0x2C) != 0) {
        *(int *)(o + 0x28C) = 0;
        *(int *)(o + 0x27C) = 0;
        *(float *)(o + 0x2C4) = PP[0x1C / 4];
    } else {
            AI_GetRandomVelocity((float *)(o + 0x2C8), o + 0x27C, o + 0x28C, PP[0x20 / 4], PP[0x24 / 4], 1.0f, PP[0x14 / 4]);
        AI_UpdateVelocity((float *)(o + 0x2C4), *(float *)(o + 0x2C8), PP[0x4C / 4]);
    }
    *(float *)(o + 0x2D0) = (*(float *)(o + 0x2C8) - PP[0x20 / 4]) * (PP[0x2C / 4] - PP[0x28 / 4]) / (PP[0x24 / 4] - PP[0x20 / 4]) + PP[0x28 / 4];
    AI_GetMotionBasicVelocity(&vel, cc + 0x9E0, *(float *)(o + 0x2C4));
    *(Vec4 *)(o + 0x330) = vel;
    *(float *)(o + 0x340) = PP[0xC / 4] * *(float *)(o + 0x2D0);
    AI_UpdateVelocity((float *)(o + 0x2E0), PP[0x54 / 4], PP[0x50 / 4]);
    AI_UpdateVelocity((float *)(o + 0x2F8), *(float *)(o + 0x340), *(float *)(o + 0x2E0));
    *(int *)(o + 0x2F0) = 0;
    *(float *)(o + 0x2CC) = *(float *)(o + 0x2F8) / PP[0xC / 4];
    f = 1.0f - (*(float *)(a3 + 0x50) + 1.0f) * 0.5f;
    if (*(float *)(o + 0x2F0) < *(float *)(a3 + 0x10))
        f = -f;
    *(float *)(o + 0x314) = f;
    AI_UpdateVelocity((float *)(o + 0x2DC), 0.5f, 0.5f);
    AI_UpdateVelocity((float *)(o + 0x2F4), 1.5f, *(float *)(o + 0x2DC));
    if (*(float *)(a3 + 0x48) - PP[0] < -PP[1]) {
        *(int *)(o + 0x31C) = 0;
        *(float *)(o + 0x274) = 3.0f;
        AI_UpdateVelocity((float *)(o + 0x318), *(float *)(o + 0x31C), 0.1f);
    } else {
        p = (float *)(o + 0x31C);
        AI_GetRandomVelocity(p, o + 0x274, o + 0x284, -1.0f, 1.0f, 0.2f, 3.0f);
        if (0.0f < *p)
            *p = 0.0f;
    }
}
#endif
