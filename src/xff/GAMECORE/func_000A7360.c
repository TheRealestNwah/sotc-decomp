typedef int s128 __attribute__((mode(TI)));
typedef struct { long long v[4]; } P32;
typedef union { s128 q; float f[4]; } __attribute__((aligned(16))) V;

extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern void Kite_SetPathOfs(void *, void *);
extern void Kite_SetSpecialPathLayout(void *, void *, float, float);
extern void Kite_GetPassageWork(int, int, void *, void *, int);
extern int Kite_CmpPathPoint(void *, void *);
extern void func_000A5B80(char *);
extern void func_000A6260(char *);
extern void func_000A6A68(char *);
extern void func_000A70A0(char *);

/* Path update for a kite object: refreshes the path offsets, the special layout for state 8, then the passage work, and copies the next path points into place. The register variables keep the 32-byte copies alternating $v0/$v1 with the 1 for 0x580 in $v1, and the barrier keeps the func_000A5B80 argument and that store ahead of the 0x620 copy, as in the Original. */
static void func_000A7360(char *o)
{
    V sp;
    char *s1;
    char *s2;
    int thr = isysGetThisSubThread();
    char *a0, *a1, *t1, *p1, *p2;
    int st;

    s2 = o + 0x5D0;
    s1 = o + 0x370;
    Kite_SetPathOfs(s1, s2);
    if (*(int *)o == 8) {
        sp.q = **(s128 **)(GetLayoutClass(*(int *)(o + 0x24)) + 0x134);
        sp.f[1] += 20.0f;
        Kite_SetSpecialPathLayout(s1, &sp, 80.0f, 5.0f);
        if (*(int *)(o + 0x274) == 7)
            *(int *)(o + 0x528) = 1;
    }
    if (*(int *)(o + 0x38) != 0 || *(int *)(o + 0x3C) == 0x24) {
        Kite_GetPassageWork(thr, *(int *)(o + 0x360), s1, s1, 1);
    } else {
        t1 = *(char **)(o + 0x2C);
        { register long long t __asm__("$2") = *(long long *)(t1 + 0x600); *(long long *)(o + 0x400) = t; }
        *(long long *)(o + 0x408) = *(long long *)(t1 + 0x608);
        *(long long *)(o + 0x410) = *(long long *)(t1 + 0x610);
        *(long long *)(o + 0x418) = *(long long *)(t1 + 0x618);
        *(P32 *)(o + 0x420) = *(P32 *)(t1 + 0x640);
        Kite_GetPassageWork(thr, *(int *)(t1 + 0x360), t1 + 0x370, s1, 0);
    }
    a0 = o + 0x3A0;
    a1 = o + 0x380;
    if (*(int *)(a0 + 0x10) != -1)
        *(P32 *)(o + 0x660) = *(P32 *)a0;
    if (*(int *)(a1 + 0x10) != -1) {
        register char *arg __asm__("$4") = o;
        { register int one __asm__("$3") = 1; *(int *)(o + 0x580) = one; }
        __asm__ __volatile__("" : : "r"(arg) : "memory");
        { register long long t __asm__("$2") = *(long long *)(a1 + 0x0); *(long long *)(o + 0x620) = t; }
        { register long long t __asm__("$3") = *(long long *)(a1 + 0x8); *(long long *)(o + 0x628) = t; }
        { register long long t __asm__("$2") = *(long long *)(a1 + 0x10); *(long long *)(o + 0x630) = t; }
        { register long long t __asm__("$3") = *(long long *)(a1 + 0x18); *(long long *)(o + 0x638) = t; }
        func_000A5B80(arg);
        func_000A6260(o);
        func_000A6A68(o);
        func_000A70A0(o);
        st = *(int *)(o + 0x274);
        if (st == 9 || st == 12 || st == 13) {
            p1 = o + 0x600;
            p2 = o + 0x620;
            if (Kite_CmpPathPoint(p1, p2) == 0) {
                *(P32 *)(o + 0x680) = *(P32 *)(o + 0x600);
                *(int *)(o + 0x764) = 0;
            }
            *(long long *)p1 = *(long long *)p2;
            *(long long *)(o + 0x608) = *(long long *)(o + 0x628);
            *(long long *)(o + 0x610) = *(long long *)(o + 0x630);
            *(long long *)(o + 0x618) = *(long long *)(o + 0x638);
            *(P32 *)(o + 0x640) = *(P32 *)(o + 0x660);
        } else {
            p1 = o + 0x600;
            p2 = o + 0x620;
        }
        if (Kite_CmpPathPoint(p1, p2) != 0) {
            p2 = o + 0x640;
            p1 = o + 0x660;
            if (Kite_CmpPathPoint(p2, p1) == 0) {
                *(long long *)p2 = *(long long *)p1;
                *(long long *)(o + 0x648) = *(long long *)(o + 0x668);
                *(long long *)(o + 0x650) = *(long long *)(o + 0x670);
                *(long long *)(o + 0x658) = *(long long *)(o + 0x678);
            }
        }
    } else {
        *(int *)(o + 0x580) = 0;
        *(int *)(o + 0x614) = 0;
    }
}
