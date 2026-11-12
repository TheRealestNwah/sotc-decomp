typedef int s128 __attribute__((mode(TI)));
typedef struct { long long v[4]; } P32;

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

#ifdef NONMATCHING /* 81 diffs, same word count: float-add/constant scheduling around Kite_SetSpecialPathLayout, branch-likely form of the 0x38 test and struct-copy register choice (orig starts the 32-byte copies with $v0) */
void func_000A7360(char *o)
{
    float sp[4] __attribute__((aligned(16)));
    char *s1 = o + 0x370;
    int thr = isysGetThisSubThread();
    char *a0, *a1, *t1, *p1, *p2;
    int st;

    Kite_SetPathOfs(s1, o + 0x5D0);
    if (*(int *)o == 8) {
        *(s128 *)sp = **(s128 **)(GetLayoutClass(*(int *)(o + 0x24)) + 0x134);
        sp[1] += 20.0f;
        Kite_SetSpecialPathLayout(s1, sp, 80.0f, 5.0f);
        if (*(int *)(o + 0x274) == 7)
            *(int *)(o + 0x528) = 1;
    }
    if (*(int *)(o + 0x38) == 0 && *(int *)(o + 0x3C) == 0x24) {
        Kite_GetPassageWork(thr, *(int *)(o + 0x360), s1, s1, 1);
    } else {
        t1 = *(char **)(o + 0x2C);
        *(P32 *)(o + 0x400) = *(P32 *)(t1 + 0x600);
        *(P32 *)(o + 0x420) = *(P32 *)(t1 + 0x640);
        Kite_GetPassageWork(thr, *(int *)(t1 + 0x360), t1 + 0x370, s1, 0);
    }
    a0 = o + 0x3A0;
    a1 = o + 0x380;
    if (*(int *)(a0 + 0x10) != -1)
        *(P32 *)(o + 0x660) = *(P32 *)a0;
    if (*(int *)(a1 + 0x10) != -1) {
        *(int *)(o + 0x580) = 1;
        *(P32 *)(o + 0x620) = *(P32 *)a1;
        func_000A5B80(o);
        func_000A6260(o);
        func_000A6A68(o);
        func_000A70A0(o);
        st = *(int *)(o + 0x274);
        p1 = o + 0x600;
        if (st == 9 || st == 12 || st == 13) {
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
        *(int *)(o + 0x614) = 0;
        *(int *)(o + 0x580) = 0;
    }
}
#endif
