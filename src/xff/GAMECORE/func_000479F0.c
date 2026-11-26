/* 161 words incl. the split tail func_00047C40 tail call. Path-follow state update: when A0 < A4 re-derives the heading (normalised via VU0 unless AI_CheckNormZero fails, then ZUnitVector), randomises it by f21, scales by -f20 and by the speed ratio (o+0x354 / o+0x350) with qmtc2 multiplies, refreshes A0/A4 from gcGlobalVar.f190 * o+0x350, calls the three AI_GetAccel*3XYZ helpers, then position/velocity. The floats go straight into the qmtc2 asm as "r" operands, so gcc emits and schedules the mfc1 itself (mfc1 asm outputs cost 4 more diffs; memory round trips cost 67). Setting s5 after the second accel call fixes most argument-move order. The p+0x80 copy goes through a temp pinned to $v1 with an empty asm (memory clobber) so the lq issues before the gcGlobalVar address, and the first accel call takes s7 through a $t1 pin so that move comes first. */
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern struct {
    char pad[0x190];
    float f190;
} gcGlobalVar;
extern Vec ZUnitVector;
extern int AI_CheckNormZero(void *);
extern float iosGetRandom(void);
extern void AI_GetAccelA3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelB3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelC3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetPosition3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetVelocity3XYZ(char *, char *, char *, char *, char *, float);

static void func_000479F0(char *o, char *p, float f21, float f22, float f20)
{
    struct {
        Vec n;
        Vec t;
        Vec k;
    } L __attribute__((aligned(16)));
    char *s3;
    char *fp;
    char *s5;
    char *s6;
    char *s4;
    char *s7;
    char *s0;
    char *s1;
    float lim;
    float ratio;

    float a4 = *(float *)(p + 0xA4);

    if (*(float *)(p + 0xA0) < a4) {
        L.n.q = *(s128 *)(p + 0x90);
        L.n.x = 0.0f;
        L.n.y = 0.0f;
        if (AI_CheckNormZero(&L.n) != 0) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "vmul.xyz vf7, vf5, vf5\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7w\n"
                                 "vwaitq\n"
                                 "vmulq.xyz vf5, vf5, Q\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 :
                                 : "r"(&L.n)
                                 : "memory");
        } else {
            L.n.q = ZUnitVector.q;
        }
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&L.k) : "memory");
        L.k.x = (2.0f * iosGetRandom() - 1.0f) * f21;
        {
            float nf = -f20;


            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyzw vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 :
                                 : "r"(&L.n), "r"(nf), "r"(&L.t)
                                 : "memory");
        }
        *(s128 *)(p + 0x60) = L.k.q;
        *(s128 *)(p + 0x40) = L.t.q;
        s7 = p + 0x70;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(s7) : "memory");
        s3 = p + 0x30;
        ratio = *(float *)(o + 0x354) / *(float *)(o + 0x350);
        fp = p + 0x90;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(fp), "r"(ratio), "r"(s3)
                             : "memory");
        { register s128 c asm("$3") = *(s128 *)(p + 0x80); __asm__ ("" : "+r"(c) : : "memory"); *(float *)(p + 0xA0) = f22; *(s128 *)(p + 0x50) = c; }
        *(float *)(p + 0xA4) = gcGlobalVar.f190 * *(float *)(o + 0x350);
        lim = gcGlobalVar.f190 * *(float *)(o + 0x350);
        if (f22 < lim)
            *(float *)(p + 0xA0) = lim;
        s6 = p + 0x20;
        s4 = p + 0x50;
        s0 = p + 0x60;
        s1 = p + 0x40;
        { register char *t1 asm("$9") = s7; AI_GetAccelC3XYZ(s6, s3, s1, s4, s0, t1, *(float *)(p + 0xA0)); }
        AI_GetAccelA3XYZ(p, s3, s4, s0, s7, s6, *(float *)(p + 0xA0));
        s5 = p + 0x10;
        AI_GetAccelB3XYZ(s5, s3, s1, s4, s0, s6, *(float *)(p + 0xA0));
    } else {
        s3 = p + 0x30;
        fp = p + 0x90;
        s6 = p + 0x20;
        s4 = p + 0x50;
        s5 = p + 0x10;
    }
    AI_GetPosition3XYZ(p + 0x80, p, s5, s6, s4, s3, *(float *)(p + 0xA4));
    AI_GetVelocity3XYZ(fp, p, s5, s6, s3, *(float *)(p + 0xA4));
}
