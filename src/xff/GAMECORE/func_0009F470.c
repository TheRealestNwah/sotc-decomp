extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern int AI_CheckDamage_Impact(int, void *);
extern int AI_CheckNearArrow(void *, void *, void *);
extern int getSelectWeapon(void);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int *, int);
extern char *GetScriptCharacterClass(int);
extern int AI_CheckSightOn(int, float);

#ifdef NONMATCHING /* 77 diffs: impact/arrow result flow ($v1 merge), weapon-range test and group-loop layout */
int func_0009F470(char *o)
{
    char buf[16] __attribute__((aligned(16)));
    char *pos;
    float f1, dist;
    int w, found, ent, res;
    int *e;
    int v1;

    if (*(int *)(o + 0x288) != 0)
        return 1;
    if (*(int *)(o + 0x38) == 0)
        goto tail;
    pos = o + 0x470;
    f1 = *(float *)(o + 0x324);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dist) : "r"(pos), "r"(o + 0x50) : "$2");
    if (50.0f < f1) {
        if (dist < 20.0f)
            return 1;
    }
    if (2.0f < f1) {
        if (dist < 4.0f)
            return 1;
    }
    if (f1 <= 2.0f) {
        if (dist < 3.0f)
            return 1;
    }
    {
        void *thr = isysGetThisSubThread();
        void *a1 = pos;
        int hit = 0;
        if (*(int *)(o + 0x7C4) == 0) {
            hit = AI_CheckDamage_Impact(0, thr);
        }
        if (!hit)
            hit = AI_CheckNearArrow(buf, a1, o + 0x7C8);
        if (hit)
            return 1;
    }
    w = getSelectWeapon();
    res = 0;
    if (w < 8)
    if (w >= 4) {
        found = 0;
        ent = 0;
        for (e = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); e; e = isysGroupForNext(e, 0)) {
            char *c, *t;
            ent = *e;
            c = GetScriptCharacterClass(ent);
            t = *(char **)(c + 0x1200);
            if (t == 0)
                continue;
            if (*(int *)t != 1)
                continue;
            if (*(int *)(t + 8) != *(int *)(o + 8))
                continue;
            if (*(int *)(t + 4) != *(int *)(o + 4))
                continue;
            if (*(int *)(t + 0x26C) == 0x12)
                continue;
            if (*(int *)(t + 0x260) != 0x1C)
                continue;
            if (AI_CheckSightOn(ent, *(float *)(o + 0x7C0)) == 0)
                continue;
            found = 1;
            break;
        }
        if (ent != 0)
            isysGroupForExit((int *)ent, 0);
        res = found != 0;
    }
    return res;
tail:
    v1 = *(int *)(*(char **)(o + 0x2C) + 0x288);
    return v1 != 0;
}
#endif
