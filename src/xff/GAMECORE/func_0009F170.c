/* Decides whether a creature is out of reach, by its state, height and distance thresholds. */
#ifdef NONMATCHING
/* Parked attempt: 4 differing words (bne/bnel at 0xC, $f2/$f0 for scale588,
 * bc1fl/bc1f at 0x58). Permuter 25 min found nothing better. */
static inline float distXYZ(const float *a, const float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

typedef struct {
    int type;
    char pad4[0x20 - 4];
    float *param;
    char pad24[0x158 - 0x24];
    float range158;
    char pad15C[0x1B0 - 0x15C];
    float f1B0;
    char pad1B4[4];
    float f1B8;
    char pad1BC[0x218 - 0x1BC];
    float range218;
    char pad21C[0x274 - 0x21C];
    int mode;
    char pad278[0x298 - 0x278];
    float f298;
    char pad29C[0x2E8 - 0x29C];
    float f2E8;
    char pad2EC[4];
    float f2F0;
    char pad2F4[0x580 - 0x2F4];
    int flag580;
    char pad584[4];
    float scale588;
    char pad58C[4];
    float posA[4] __attribute__((aligned(16)));
    char pad5A0[0x10];
    float posB[4] __attribute__((aligned(16)));
} Creature;

static int func_0009F170(Creature *c)
{
    float limit;
    float *p;
    float *q;

    if (c->type == 8) {
        if ((unsigned)(c->mode - 12) < 2) return 0;
        limit = c->range158;
        q = c->param;
        goto compare;
    }
    if (c->type == 6) {
        limit = c->range218 * c->scale588;
        q = c->param;
    compare:
        if (q[1] < limit) return 1;
        return 0;
    }
    if (c->flag580) {
        int steep;
        limit = c->range218;
        p = c->param;
        if (limit < p[1]) return 0;
        if (c->f1B8 < 0.0f) return 0;
        if (c->f1B0 < 15.0f) return 0;
        if (c->f298 < 3.0f) return 0;
        if (c->f2F0 < 0.5f) return 0;
        if (c->f2E8 < 5.0f) return 0;
        if (c->f1B0 < 50.0f) {
            steep = 0.5f < (c->posB[1] - c->posA[1]) / distXYZ(c->posB, c->posA);
            if (steep) return 0;
        }
        return 1;
    }
    limit = c->range158;
    p = c->param;
    return p[1] < limit;
}
#endif
