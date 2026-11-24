/* Animal approach state machine: switch on w[0] (table of six entries starting at 1; 4 and anything else end). State 1 first tries func_000A01D0 (-> 2) and func_000A0390 (-> 5), then compares xz distances (VU0 vmul.xz / vsqrt runs) from the leader's layout and the work position to the animal's position and, through AI_CheckInAnimalLayout checks, decides whether to flag w[2]; 2 and 3 use AI_CheckPathPoint (3.0 / 5.0 radius, 100.0 height) to move on to 3 / 6; 5 defers to func_000A04C8 (-> 6); 6 re-checks func_000A0390 then the path point and finally resets the state to 0 with w[2] = 1 (the tail). The leader position pointer is loaded once for both distance runs; case 2's path-point call sits in an inline helper so the 3.0 constant is not shared across the call in f20; each VU0 distance run moves its result through $2 with mtc1 inside the asm (a $2 clobber), which puts the pointer in v1 and orders mtc1 as in the Original. The empty asm clobbering $2 on case 2's fall-through marks v0 dead there, so reorg steals the `v0 = 3` into a plain bnez delay slot instead of a bnel. */
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern int AI_CheckInAnimalLayout(void *, void *);
extern int AI_CheckPathPoint(void *, void *, float, float);
extern int func_000A01D0(char *, char *);
extern int func_000A0390(char *, char *);
extern int func_000A04C8(char *, char *);

static inline float xzDist2(void *a, void *b)
{
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f)
                         : "r"(a), "r"(b)
                         : "$2", "memory");
    return f;
}

static inline float xzDist(void *a, void *b)
{
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f)
                         : "r"(a), "r"(b)
                         : "$2", "memory");
    return f;
}

static inline int atPoint(int *w)
{
    return AI_CheckPathPoint(isysGetThisSubThread(), (char *)w + 0x50, 3.0f, 100.0f);
}

static void func_000A0888(char *obj, int *w)
{
    char *s1;
    char *lay;
    float d1;
    float d2;
    float d3;
    int v;
    int r;

    switch (w[0]) {
    case 1:
        if (func_000A01D0(obj, (char *)w)) {
            w[0] = 2;
            break;
        }
        if (func_000A0390(obj, (char *)w)) {
            w[0] = 5;
            break;
        }
        s1 = obj + 0x560;
        lay = GetLayoutClass(isysGetThisSubThread());
        {
            char *p = *(char **)(lay + 0x134);
            d1 = xzDist2(p, s1);
            d2 = xzDist2((char *)w + 0x30, s1);
            d3 = xzDist(p, (char *)w + 0x30);
        }
        if (!AI_CheckInAnimalLayout((char *)w + 0x30, obj + 0x50))
            v = 1;
        else if (AI_CheckInAnimalLayout(s1, *(char **)(lay + 0x134)))
            v = 0;
        else if (d2 < d1)
            v = 1;
        else
            v = (100.0f < *(float *)(w + 0x10) - d3) ? 1 : 0;
        if (v != 0) {
            w[2] = 1;
            break;
        }
        if (*(float *)(w + 3) > *(float *)(w + 4))
            w[2] = 1;
        break;
    case 2:
        if (atPoint(w) == 0) {
            __asm__("" ::: "$2");
            if (func_000A0390(obj, (char *)w)) {
                w[0] = 5;
                break;
            }
            if (3.0f < *(float *)(w + 7))
                r = 1;
            else
                r = w[10] == 0;
            if (r == 0)
                break;
        }
        w[0] = 3;
        break;
    case 3:
        r = AI_CheckPathPoint(isysGetThisSubThread(), (char *)w + 0x70, 5.0f, 100.0f);
        if (r == 0)
            break;
        w[0] = 6;
        break;
    case 5:
        r = func_000A04C8(obj, (char *)w);
        if (r == 0)
            break;
        w[0] = 6;
        break;
    case 6:
        if (func_000A0390(obj, (char *)w)) {
            w[0] = 5;
            break;
        }
        if (AI_CheckPathPoint(isysGetThisSubThread(), (char *)w + 0x70, 5.0f, 100.0f) == 0)
            break;
        w[0] = 0;
        w[2] = 1;
        break;
    }
}
