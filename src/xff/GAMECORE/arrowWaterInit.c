/* Parked: 27 diffs, same size (131 words). Arrow water spawn init: builds the effect work (func_00052EA8 edit-work init), 25 particles each placed by AI_GetRandomCircleOfsXZ plus the object's position (VU0 vadd.xyz), random sin/cos and sqc2 vf0 quad clears, then the free-list of 0x40-byte entries and the B_0018AD70 slot table. Float constant 2*pi is 6.2831854f (0x40C90FDA). The free-list next pointer is stored as int so the count is re-read after it (type-based aliasing). Remaining: load order of the count/array/position, store order inside the particle loop, and register roles in the free-list loop ($a1 for the next pointer, header store through $a0). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern char B_0018AD70[];
extern char *getSpecialEffectObjWork(void);
extern void func_00052EA8(char *, char *);
extern void AI_GetRandomCircleOfsXZ(char *, float, float);
extern float iosGetRandom(void);
extern void iosGetSinCosf(char *, float);

void arrowWaterInit(char *obj)
{
    s128 base;
    char *w;
    char *ew;
    char *p;
    char *arr;
    char *end;
    char *q;
    register char *ent __asm__("$3");
    float f20;
    float f21;
    int n;
    register int i __asm__("$6");
    int k;
    register char *e __asm__("$4");

    n = 0x18;
    w = getSpecialEffectObjWork();
    ew = w + 0x10;
    *(char **)(w + 4) = w + 0x170;
    *(char **)w = ew;
    func_00052EA8(ew, obj);
    k = *(int *)(ew + 0xF4);
    arr = *(char **)(w + 4);
    end = arr + (k << 7);
    p = arr;
    *(char **)(w + 8) = end;
    base = *(s128 *)(obj + 0x20);
    f20 = *(float *)(*(char **)(obj + 0x1C) + 0x34);
    f21 = *(float *)(*(char **)(obj + 0x1C) + 0x38);
    do {
        AI_GetRandomCircleOfsXZ(p + 0x20, f20, f21);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             :
                             : "r"(&base), "r"(p + 0x20)
                             : "memory");
        iosGetSinCosf(p + 0x30, iosGetRandom() * 6.2831854f);
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(p + 0x50) : "memory");
        q = p + 0x60;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(q) : "memory");
        *(int *)(q + 0x18) = 1;
        n--;
        *(int *)(q + 0x10) = 0;
        *(int *)(q + 0x14) = 0;
        *(int *)(p + 8) = 0;
        *(int *)(p + 0xC) = 0;
        *(int *)(p + 0x14) = 0;
        *(float *)(p + 0x10) = 1.0f;
        *(int *)(p + 0x18) = 0;
        *(int *)(p + 4) = 0;
        *(s128 *)(p + 0x40) = *(s128 *)(p + 0x20);
        *(int *)p = *(int *)w;
        *(float *)(p + 8) = iosGetRandom();
        p += 0x80;
    } while (n >= 0);
    e = ew + 0x120;
    ent = end;
    i = 0;
    *(char **)(e + 4) = ent;
    if (*(int *)e > 0) {
        do {
            __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(ent) : "memory");
            *(int *)(ent + 0x38) = 0;
            *(int *)(ent + 0x20) = 0;
            *(int *)(ent + 0x24) = 0;
            *(int *)(ent + 0x28) = 0;
            *(int *)(ent + 0x30) = 0;
            *(int *)(ent + 0x2C) = 0;
            {
                register int c __asm__("$2") = i < *(int *)e - 1;
                i++;
                if (c)
                    *(int *)(ent + 0x38) = (int)(ent + 0x40);
                else
                    *(int *)(ent + 0x38) = 0;
            }
            ent += 0x40;
        } while (i < *(int *)e);
    }
    {
        char *b = B_0018AD70;
        int m = 0x18;
        do {
            m--;
            *(int *)b = 0;
            *(int *)(b + 8) = 0;
            *(int *)(b + 0xC) = 0;
            *(int *)(b + 0x10) = 1;
            b += 0x14;
        } while (m >= 0);
    }
}
#endif
