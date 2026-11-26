/* Parked: 2 diffs, same size. Remaining: the prologue stores the sq to 0x10
 * before the 0x418 store, where the Original stores 0x418 first (no statement
 * order or store type changes it). Pinning lst (w+0x2038) to s4 and oa/ob to
 * s3/s2 fixes the retry loop's s4/s5 swap. Setting tries before the
 * execPointListSort call fixes that call's delay slot. */

#ifdef NONMATCHING

typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u128 q; Vec4 f; } VecQ;
typedef union { u128 q; int i[4]; } QI;

extern char *GetCharacterClass(int);
extern int GetStageAreaNumberByPos(void *);
extern void setDataHeaderFromAreaIdx(char *);
extern int func_000F6228(char *);
extern int func_000F46B8(char *);
extern void resetPassageWork(char *);
extern void execPointListSort(char *, void *, void *);
extern int getNearPoint(char *, int, int *, int *, void *, void *, int, int);
extern int func_000FA870(char *, int, int, void *, int, int, int, int);
extern float *getPointDataByAreaIdx(char *, int, int);
extern int memcmp(const void *, const void *, unsigned int);
extern char *getPassageWork(char *, unsigned int);
extern char *getLineDataByAreaIdx(char *, int, int);
extern int func_000FA658(char *, void *, int, int);
extern void func_000FA168(char *, int, int, void *, int);
extern int getPathColiGroupByType(int);
extern int pathDetectCollision(char *, void *, void *, void *, int);
extern int pathDetectCollision2(char *, void *, void *, void *, int);
extern void func_000F5D30(char *);
extern void func_000F4AC0(char *, int);
extern int func_000FAC10(char *, char *, char *);
extern void func_000FA1D0(char *, int, int, int);
extern void func_000FA2C0(char *);
extern void func_000F4148(char *);
extern int func_000F69B8(char *, char *, char *);

#define W(type, o) (*(type *)(w + (o)))

static inline void quatDir(void *dst, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
}
static inline float vecDist(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
static inline void vecAdd(float *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void updateUserPathWork(int owner, char *w)
{
    char *cls = GetCharacterClass(owner);
    int pa, pb;

    W(QI, 0x10).q = W(u128, 0x0);
    W(int, 0x400) = 0;
    W(int, 0x418) = 0;
    W(int, 0x42C) = -1;
    W(int, 0x430) = -1;
    W(QI, 0x0).q = *(u128 *)*(int *)(cls + 0x134);
    quatDir(w + 0x20, *(void **)(cls + 0x13C));
    W(int, 0x3AC) = W(int, 0x3A8);
    W(int, 0x3A8) = GetStageAreaNumberByPos(w);
    setDataHeaderFromAreaIdx(w);
    if (!func_000F6228(w)) {
        W(int, 0x80) = -1;
        W(int, 0x84) = -1;
        W(int, 0x41C) = -1;
        W(int, 0x420) = -1;
        W(int, 0x424) = -1;
        W(int, 0x428) = -1;
        W(int, 0x42C) = -1;
        W(int, 0x430) = -1;
        W(int, 0x88) = -1;
        W(int, 0x8C) = -1;
        switch (W(int, 0x3A4)) {
        case 0:
            W(int, 0x408) = 0;
            func_000F46B8(w);
            break;
        case 1:
            resetPassageWork(w);
            break;
        }
    }
    execPointListSort(w, w + 0x434, w);
    {
        register int oa asm("$19") = W(int, 0x41C);
        register int ob asm("$18") = W(int, 0x420);
        getNearPoint(w, 0, &W(int, 0x41C), &W(int, 0x420), w + 0x434, w, W(int, 0x39C) == 0, 0);
        if (oa != -1 && ob != -1 && W(int, 0x41C) != oa && W(int, 0x420) != ob
            && func_000FA870(w, oa, ob, w, 0, 1, 0, 0)) {
            float *p = getPointDataByAreaIdx(w, W(int, 0x41C), W(int, 0x420));
            float *q = getPointDataByAreaIdx(w, oa, ob);
            if (p != 0 && q != 0) {
                float d = vecDist(w, p) + 0.5f;
                if (vecDist(w, q) < d) {
                    W(int, 0x41C) = oa;
                    W(int, 0x420) = ob;
                }
            }
        }
    }
    if (W(int, 0x388) != W(int, 0x384)) {
        W(int, 0x408) = 0;
        func_000F46B8(w);
    }
    if (W(int, 0x94) != 0) {
        int id = W(int, 0x94);
        if (W(int, 0xA4) == 0) {
            W(int, 0x94) = 0;
            id = 0;
        }
        if (id != 0) {
            char *c2 = GetCharacterClass(id);
            VecQ v;
            vecAdd(v.f, *(void **)(c2 + 0x134), w + 0xD0);
            v.f[3] = 1.0f;
            if ((W(int, 0x3C50) != 1 || *(char *)(c2 + 0x10C0) != 0) && memcmp(w + 0x70, v.f, 0xC) != 0) {
                W(int, 0x90) = 1;
                W(u128, 0x60) = v.q;
                W(int, 0x410) = 0;
                W(int, 0x408) = 0;
            }
        }
    }
    if (W(int, 0x3A0) == 0 && W(int, 0x90) != 0) {
        char *tgt = w + 0x60;
        register char *lst asm("$20") = w + 0x2038;
        int tries;
        char *cp;
        tries = 0;
        execPointListSort(w, lst, tgt);
        for (;;) {
            if (getNearPoint(w, 0, &pa, &pb, lst, tgt, W(int, 0x39C) == 0, 1)) {
                if (pa == W(int, 0x80) && pb == W(int, 0x84)) {
                    cp = getPassageWork(w, W(int, 0x380) - 1);
                    if (cp != 0) {
                        if (memcmp(w + 0x70, cp, 0xC) == 0) {
                            int ok = 0;
                            char *ln = getLineDataByAreaIdx(w, *(short *)(cp + 0x16), *(int *)(cp + 0x1C));
                            if (W(int, 0x380) != 1 || ln == 0 || *(unsigned short *)(ln + 0xE) < 0x81
                                || func_000FA658(w, tgt, *(short *)(cp + 0x16), *(int *)(cp + 0x1C)))
                                ok = 1;
                            if (memcmp(w + 0xC0, w + 0xB0, 0xC) != 0 && W(int, 0xA8) != 0)
                                ok = 0;
                            if (ok) {
                                ((QI *)cp)->q = W(u128, 0x60);
                                W(int, 0x90) = 0;
                            }
                        } else if (W(int, 0x384) == 0 && W(int, 0x3C50) == 1) {
                            ((QI *)cp)->q = *(u128 *)tgt;
                            W(int, 0x90) = 0;
                        }
                    }
                } else {
                    unsigned int i;
                    for (i = 0; i < W(unsigned int, 0x380); i++) {
                        char *q = getPassageWork(w, i);
                        if (*(int *)(q + 0x10) != 0 && pa == *(short *)(q + 0x14) && pb == *(int *)(q + 0x1C)) {
                            W(int, 0x380) = i + 1;
                            func_000FA168(w, W(int, 0x80), W(int, 0x84), tgt, -1);
                            W(int, 0x90) = 0;
                            break;
                        }
                    }
                }
                break;
            }
            if (W(int, 0x414) == 0)
                break;
            if (tries == 0) {
                if (W(int, 0x414) == 1 && pathDetectCollision(w, w + 0x60, w, w + 0x60, getPathColiGroupByType(W(int, 0x3C50))))
                    W(int, 0x410) = 1;
                else if (W(int, 0x414) == 2 && pathDetectCollision2(w, w + 0x60, w, w + 0x60, getPathColiGroupByType(W(int, 0x3C50))))
                    W(int, 0x410) = 1;
                else
                    break;
            }
            tries++;
            if (tries >= 2)
                break;
        }
        W(int, 0x80) = pa;
        W(int, 0x84) = pb;
        W(u128, 0x70) = W(u128, 0x60);
    }
    if (W(int, 0x3A0) != W(int, 0x3A4)) {
        switch (W(int, 0x3A0)) {
        case 0:
            W(int, 0x408) = 0;
            func_000F46B8(w);
            break;
        case -1:
            W(int, 0x408) = 0;
            break;
        case 1:
            func_000F5D30(w);
            break;
        }
    }
    switch (W(int, 0x3A0)) {
    case 0:
        if (W(int, 0x90) != 0) {
            W(int, 0x408) = 0;
            if (!func_000F46B8(w))
                break;
        }
        if (W(int, 0x408) == 0)
            func_000F4AC0(w, owner);
        break;
    case 1:
        if (W(int, 0x40C) == 0) {
            if (W(int, 0x380) == 0)
                func_000F5D30(w);
            if (W(int, 0x40C) == 0)
                goto search;
        }
        if (!func_000FAC10(w, w, w + 0x70)) {
            W(int, 0x40C) = 0;
            W(int, 0x80) = -1;
            W(int, 0x84) = -1;
            resetPassageWork(w);
            func_000FA1D0(w, W(int, 0x88), W(int, 0x8C), -1);
            func_000FA2C0(w);
        } else {
            func_000F4AC0(w, owner);
        }
        if (W(int, 0x40C) == 0)
        search:
            func_000F4148(w);
        break;
    }
    if (W(int, 0x3A0) == 0)
        W(int, 0x90) = 0;
    if (W(int, 0x3A0) != -1) {
        char *pw = getPassageWork(w, 0);
        if (pw != 0) {
            while (func_000F69B8(w, cls, cls))
                ;
            if (W(int, 0x3A0) == 1 && W(int, 0x40C) != 0
                && (W(int, 0x380) == 0 || W(int, 0x80) == *(short *)(pw + 0x14))) {
                W(int, 0x40C) = 0;
                W(int, 0x80) = -1;
                W(int, 0x84) = -1;
                resetPassageWork(w);
                func_000FA1D0(w, *(short *)(pw + 0x14), *(int *)(pw + 0x1C), -1);
                func_000FA2C0(w);
            }
        }
    }
    W(int, 0x3A4) = W(int, 0x3A0);
    W(int, 0x388) = W(int, 0x384);
    W(u128, 0xC0) = W(u128, 0xB0);
}

#endif
