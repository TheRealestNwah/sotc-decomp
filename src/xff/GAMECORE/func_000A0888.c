/* Parked: 123 diffs, same size (incl. the split tail func_000A0B08). Animal approach state machine: switch on w[0] (table of six entries starting at 1; 4 and anything else end). State 1 first tries func_000A01D0 (-> 2) and func_000A0390 (-> 5), then compares xz distances (VU0 vmul.xz / vsqrt runs) from the leader's layout and the work position to the animal's position and, through AI_CheckInAnimalLayout checks, decides whether to flag w[2]; 2 and 3 use AI_CheckPathPoint (3.0 / 5.0 radius, 100.0 height) to move on to 3 / 6; 5 defers to func_000A04C8 (-> 6); 6 re-checks func_000A0390 then the path point and finally resets the state to 0 with w[2] = 1 (the tail). Remaining: float register numbering of the three distances (f21/f20/f22 in the Original; declaration-order permutations do not change it) and the object register (s2 vs s3). */
#ifdef NONMATCHING
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern int AI_CheckInAnimalLayout(void *, void *);
extern int AI_CheckPathPoint(void *, void *, float, float);
extern int func_000A01D0(char *, char *);
extern int func_000A0390(char *, char *);
extern int func_000A04C8(char *, char *);

static inline float xzDist2(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         : "=&r"(bits)
                         : "r"(a), "r"(b)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
}

static inline float xzDist(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=&r"(bits)
                         : "r"(a), "r"(b)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
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
        d1 = xzDist2(*(char **)(lay + 0x134), s1);
        d2 = xzDist2((char *)w + 0x30, s1);
        d3 = xzDist(*(char **)(lay + 0x134), (char *)w + 0x30);
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
        if (*(float *)(w + 4) < *(float *)(w + 3))
            w[2] = 1;
        break;
    case 2:
        if (AI_CheckPathPoint(isysGetThisSubThread(), (char *)w + 0x50, 3.0f, 100.0f) == 0) {
            if (func_000A0390(obj, (char *)w)) {
                w[0] = 5;
                break;
            }
            if (3.0f < *(float *)(w + 7))
                v = 1;
            else
                v = w[10] == 0;
            if (v == 0)
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
#endif
