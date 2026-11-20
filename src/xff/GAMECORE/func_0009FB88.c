extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetScriptCharacterClass(int);
extern int Kite_CmpPathPoint(void *, void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern int AI_CheckDamage_Impact(int, int);
extern int AI_CheckNearArrow(void *, void *, void *);
extern int AI_CheckSightOn(int, float);
extern int getSelectWeapon(void);

static inline float distXYZ(void *a, void *b)
{
    float d;
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
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline int inRange(char *w, float h, float d)
{
    if (h > 10.0f && d < *(float *)(*(char **)(w + 0x20) + 0xD8))
        return 1;
    if (h > 2.0f && d < *(float *)(*(char **)(w + 0x20) + 0xD4))
        return 1;
    if (h <= 2.0f) {
        int r = d < *(float *)(*(char **)(w + 0x20) + 0xD0);
        if (r)
            return 1;
    }
    if (*(int *)(w + 0x274) == 8 && *(int *)(w + 0x798) == 0 && *(float *)(w + 0x90) < 50.0f)
        return 1;
    return 0;
}

static inline int arrowNear(char *w, char *pos)
{
    char buf[16] __attribute__((aligned(16)));
    int th = isysGetThisSubThread();

    if (*(int *)(w + 0x7C4) == 0 && AI_CheckDamage_Impact(0, th) != 0)
        return 1;
    return AI_CheckNearArrow(buf, pos, w + 0x7C8);
}

static inline int partnerSees(char *w)
{
    int wp = getSelectWeapon();
    int *g;
    int id;
    int found;
    char *o;

    if (wp < 8) if (wp >= 4) {
        found = 0;
        id = 0;
        for (g = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); g != 0; g = isysGroupForNext(g, 0)) {
            id = *g;
            o = *(char **)(GetScriptCharacterClass(id) + 0x1200);
            if (o != 0 && *(int *)o == 1 && *(int *)(o + 8) == *(int *)(w + 8)
                && *(int *)(o + 4) == *(int *)(w + 4) && *(int *)(o + 0x26C) != 0x12
                && *(int *)(o + 0x260) == 0x1C && AI_CheckSightOn(id, *(float *)(w + 0x7C0)) != 0) {
                found = 1;
                break;
            }
        }
        if (id != 0)
            isysGroupForExit(id, 0);
        if (found)
            return 1;
    }
    return 0;
}

static int func_0009FB88(char *w)
{
    int *g;
    int id;
    int res;
    char *o;
    char *pos;
    char *k;
    float h;

    if (*(int *)(w + 0x38) != 0) {
        if (*(int *)(w + 0x260) != 0x1C)
            goto ret0;
        res = 1;
        id = 0;
        for (g = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); g != 0; g = isysGroupForNext(g, 0)) {
            id = *g;
            o = *(char **)(GetScriptCharacterClass(id) + 0x1200);
            if (o != 0 && *(int *)o == 1 && *(int *)(o + 8) == *(int *)(w + 8)
                && *(int *)(o + 4) == *(int *)(w + 4) && *(int *)(o + 8) != -1
                && *(int *)(o + 0x26C) != 0x12) {
                if (Kite_CmpPathPoint(w + 0x640, o + 0x600) != 0)
                    res = -1;
                else if (Kite_CmpPathPoint(w + 0x660, o + 0x600) != 0)
                    res = -1;
                else {
                    if (*(int *)(w + 0x274) != *(int *)(o + 0x274))
                        res = 0;
                    if (Kite_CmpPathPoint(w + 0x600, o + 0x600) == 0)
                        res = 0;
                }
            }
        }
        if (id != 0)
            isysGroupForExit(id, 0);
        h = *(float *)(w + 0x324);
        if (inRange(w, h, distXYZ(w + 0x600, w + 0x50)))
            return 1;
        if (arrowNear(w, w + 0x600))
            return 1;
        if (res == -1)
            return 1;
        if (partnerSees(w))
            return 1;
        return *(float *)(w + 0x298) < *(float *)(w + 0x294) ? 0 : res != 0;
    }
    if (*(int *)(w + 0x28) == 0)
        goto ret0;
    k = *(char **)(w + 0x2C);
    if (k == 0)
        goto ret0;
    if (*(int *)(w + 0x278) == 0xE)
        goto ret0;
    if (*(int *)(w + 0x260) == 0x20)
        goto ret0;
    pos = w + 0x600;
    if (*(int *)(w + 0x26C) == 0xE)
        goto ret0;
    if (Kite_CmpPathPoint(k + 0x680, pos) != 0) {
        if (*(int *)(w + 0x260) == 0x1C) {
            if (*(int *)(*(char **)(w + 0x2C) + 0x6AC) != 0)
                *(float *)(w + 0x2CC) = 0.0f;
            if (!(*(float *)(w + 0x2CC) > *(float *)(w + 0x2BC)))
                goto ret0;
        }
        return 1;
    }
    if (*(int *)(w + 0x260) != 0x1C)
        goto ret0;
    if (Kite_CmpPathPoint(*(char **)(w + 0x2C) + 0x600, pos) != 0)
        goto ret0;
    if (Kite_CmpPathPoint(*(char **)(w + 0x2C) + 0x640, pos) != 0)
        goto ret0;
    return Kite_CmpPathPoint(*(char **)(w + 0x2C) + 0x660, pos) == 0;
ret0:
    return 0;
}
