/* Parked: 5 diffs, same size. Chooses the attain point for the wind attack: with 2 or 3 passage points, ray-casts between the first two (ClipCollisionDirectCallBack with pathJudgeFunc) and uses -Y as the direction, with one passage point uses the normalised vector from the layout position to the AI work's +0x41F0; then offsets +0x41F0 by -f times that direction, re-checks the collision, flags +0x41C8 when the layout is within 3f, and returns setAttainmentPosAndDir's result. The hit buffer is 0x50 bytes at sp+0x10. VU0 runs match word for word. Remaining: the first branch computes &L.p60 before &YUnitVector, and the Original tail block computes &L.p60 into s3 before the mfc1 of -f, and the mfc1 goes to v1 (the C uses a0). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern Vec YUnitVector;
extern int pathJudgeFunc(void);
extern char *GetSCRCharaAIWorkPtr(void);
extern int getSCRDataCtrlWork(void *);
extern int getPassageNum(int);
extern char *getPassageWork(int, int);
extern int getPathColiGroup(int);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int, int, int, void *, int);
extern int setAttainmentPosAndDir(int, void *, void *);

int SCRFuncYamoriBSetAttainPointForWindAttack(void *obj, float f)
{
    struct {
        char hit[0x50];
        Vec p60;
        Vec p70;
        Vec p80;
    } L __attribute__((aligned(16)));
    char *ai;
    int data;
    int found;
    char *a;
    char *b;
    char *pos;
    int bits;
    register int r0 __asm__("$2");
    float lim;
    float d;
    register char *p7 __asm__("$2");

    ai = GetSCRCharaAIWorkPtr();
    data = getSCRDataCtrlWork(obj);
    r0 = *(int *)(ai + 0x41C8);
    if (r0 != 0)
        return r0;
    found = 0;
    if (getPassageNum(data) < 4 && getPassageNum(data) >= 2) {
        a = getPassageWork(data, 0);
        b = getPassageWork(data, 1);
        if (ClipCollisionDirectCallBack(L.hit, a, b, getPathColiGroup(data), 0, 0, 0, pathJudgeFunc, 0) != 0) {
            float m1 = -1.0f;

            __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(m1));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyzw vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 :
                                 : "r"(&YUnitVector), "r"(bits), "r"(&L.p60)
                                 : "memory");
            found = 1;
            goto have;
        }
    }
    if (getPassageNum(data) == 1) {
        register char *pp __asm__("$3") = *(char **)(GetLayoutClass(obj) + 0x134);
        register char *q __asm__("$4") = ai + 0x41F0;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%2)\n"
                             "lqc2 vf5, 0x0(%2)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(q), "r"(pp), "r"(&L.p60)
                             : "memory");
        found = 1;
    }
have:
    p7 = (char *)&L.p70;
    if (found == 0)
        return (int)p7;
    {
        float nf = -f;
        char *s0;
        char *s1;
        char *s3 = (char *)&L.p60;
        int r;

        __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(nf));
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(s3), "r"(bits), "r"(p7)
                             : "memory");
        s1 = (char *)&L.p80;
        s0 = ai + 0x41F0;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(s0), "r"(p7), "r"(s1)
                             : "memory");
        L.p80.w = 1.0f;
        L.p60.w = 1.0f;
        r = ClipCollisionDirectCallBack(L.hit, s0, s1, getPathColiGroup(data), 0, 0, 0, pathJudgeFunc, 0);
        if (r != 0)
            return r;
        lim = f * 3.0f;
        { register char *pq __asm__("$3") = *(char **)(GetLayoutClass(obj) + 0x134);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             ".word 0x4BA703BD\n"
                             "vwaitq\n"
                             "cfc2.ni %0, $vi22\n"
                             : "=&r"(bits)
                             : "r"(s0), "r"(pq)
                             : "memory"); }
        { register int bb __asm__("$2") = bits; __asm__("mtc1 %1, %0" : "=f"(d) : "r"(bb)); }
        if (d < lim)
            *(int *)(ai + 0x41C8) = 1;
        return setAttainmentPosAndDir(data, s1, s3);
    }
}
#endif
