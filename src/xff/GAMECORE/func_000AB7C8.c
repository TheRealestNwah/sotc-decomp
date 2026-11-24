/* Matched (153 words): update of an AI actor's wander/speed fields (actor o, config block P = o+0x34, a3 = the second argument): picks a random velocity (AI_GetRandomVelocity) or copies the preset one, smooths it with AI_UpdateVelocity, derives o+0x2D0 by remapping o+0x2C8 from [P+0x20,P+0x24] to [P+0x28,P+0x2C], gets the motion velocity into o+0x330, updates o+0x2E0/0x2F8/0x2DC/0x2F4, sets the sign of o+0x314 from a3+0x10, and then either clears o+0x31C (target within P[0]/P[1] range) or draws a new random one clamped to <= 0. Fixed: float stores to 0x28C/0x27C (alias barrier so P is reloaded), a $f3-pinned 1.0 (no gcse into f20), P pinned to $3 in the range test and the div block, and a memory barrier between the o+0x2F0 store and the div. The o+0x2F8 pointer is computed into a local before the o+0x2D0 remap, so $f12 is loaded before $f13 for AI_UpdateVelocity(o+0x2F8, o[0x340], o[0x2E0]) like the Original. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern void AI_GetRandomVelocity(float *, void *, void *, float, float, float, float);
extern void AI_UpdateVelocity(float *, float, float);
extern void AI_GetMotionBasicVelocity(Vec4 *, void *, float);

#define PP (*(float **)(o + 0x34))
static void func_000AB7C8(char *o, char *a3)
{
    Vec4 vel;
    char *cc;
    float *p;
    float f;
    int t;
    float *nv;

    cc = GetCharacterClass(isysGetThisSubThread());
    if (*(int *)(o + 0x2C) != 0) {
        *(float *)(o + 0x28C) = 0.0f;
        *(float *)(o + 0x27C) = 0.0f;
        *(float *)(o + 0x2C4) = PP[0x1C / 4];
    } else {
            AI_GetRandomVelocity((float *)(o + 0x2C8), o + 0x27C, o + 0x28C, PP[0x20 / 4], PP[0x24 / 4], 1.0f, PP[0x14 / 4]);
        AI_UpdateVelocity((float *)(o + 0x2C4), *(float *)(o + 0x2C8), PP[0x4C / 4]);
    }
    nv = (float *)(o + 0x2F8);
    *(float *)(o + 0x2D0) = (*(float *)(o + 0x2C8) - PP[0x20 / 4]) * (PP[0x2C / 4] - PP[0x28 / 4]) / (PP[0x24 / 4] - PP[0x20 / 4]) + PP[0x28 / 4];
    AI_GetMotionBasicVelocity(&vel, cc + 0x9E0, *(float *)(o + 0x2C4));
    (*(Vec4 *)(o + 0x330)).q = vel.q;
    *(float *)(o + 0x340) = PP[0xC / 4] * *(float *)(o + 0x2D0);
    AI_UpdateVelocity((float *)(o + 0x2E0), PP[0x54 / 4], PP[0x50 / 4]);
    AI_UpdateVelocity(nv, *(float *)(o + 0x340), *(float *)(o + 0x2E0));
    {
        register float *q __asm__("$3") = PP;
        float n = *(float *)(o + 0x2F8);
        float dd = q[0xC / 4];
        *(int *)(o + 0x2F0) = 0;
        __asm__ __volatile__("" ::: "memory");
        *(float *)(o + 0x2CC) = n / dd;
    }
    {
        register float k __asm__("$f3") = 1.0f;
        f = k - (*(float *)(a3 + 0x50) + k) * 0.5f;
    }
    if (*(float *)(o + 0x2F0) < *(float *)(a3 + 0x10))
        f = -f;
    *(float *)(o + 0x314) = f;
    AI_UpdateVelocity((float *)(o + 0x2DC), 0.5f, 0.5f);
    AI_UpdateVelocity((float *)(o + 0x2F4), 1.5f, *(float *)(o + 0x2DC));
    {
        register float *q __asm__("$3") = PP;
        t = *(float *)(a3 + 0x48) - q[0] < -q[1];
    }
    if (t) {
        *(float *)(o + 0x31C) = 0.0f;
        *(float *)(o + 0x274) = 3.0f;
        AI_UpdateVelocity((float *)(o + 0x318), *(float *)(o + 0x31C), 0.1f);
    } else {
        p = (float *)(o + 0x31C);
        AI_GetRandomVelocity(p, o + 0x274, o + 0x284, -1.0f, 1.0f, 0.2f, 3.0f);
        if (0.0f < *p)
            *p = 0.0f;
        AI_UpdateVelocity((float *)(o + 0x318), *p, 0.1f);
    }
}
