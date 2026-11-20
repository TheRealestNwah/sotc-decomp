typedef struct {
    char pad[0xC];
    int n;
    unsigned int *tab;
} MotList;

typedef struct {
    int cur;
    int next;
    char pad[0x14];
    float speed;
} AnimClass;

typedef struct {
    char pad[0x180];
    float dt;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int DldSysUndefSymbol;
extern float B_00188608;
extern MotList SH_JumpupMotListDEFAULT;
extern MotList SH_HeapupMotListDEFAULT;
extern MotList SH_HeapupMotList2DEFAULT;
extern MotList SH_HeapSuccessMotListDEFAULT;
extern AnimClass *GetAnimationClass(int);
extern char *GetCharacterClass(int);
extern float getAttackPowerRatio(void);
extern void resetAttackPower(void);
extern void startAttackEffect(float);

static inline int dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(int *)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int inMotList(MotList *l, int mot)
{
    int i;
    unsigned int *p = l->tab;
    int n = l->n;

    for (i = 0; i < n; i++) {
        if (mot == dldResolve(p))
            return 1;
        p++;
    }
    return 0;
}

int updatePowerWork(int obj, float heap, float heap2, float jump)
{
    int jc;
    int jn;
    short start = 0;
    short cont = 0;
    int mode = 0;
    AnimClass *anim;
    float add = 0.0f;

    anim = GetAnimationClass(obj);
    jc = inMotList(&SH_JumpupMotListDEFAULT, anim->cur);
    jn = inMotList(&SH_JumpupMotListDEFAULT, anim->next);
    if (jc) {
        start = jc;
        cont = jn;
        mode = 1;
        add = GetAnimationClass(obj)->speed * gcGlobalVar.dt * (100.0f / jump);
    } else if (inMotList(&SH_HeapupMotListDEFAULT, anim->cur) || inMotList(&SH_HeapupMotListDEFAULT, anim->next)) {
        start = inMotList(&SH_HeapupMotListDEFAULT, anim->cur);
        cont = inMotList(&SH_HeapupMotListDEFAULT, anim->next);
        mode = 2;
        add = GetAnimationClass(obj)->speed * gcGlobalVar.dt * (100.0f / heap);
    } else if (inMotList(&SH_HeapupMotList2DEFAULT, anim->cur) || inMotList(&SH_HeapupMotList2DEFAULT, anim->next)) {
        start = inMotList(&SH_HeapupMotList2DEFAULT, anim->cur);
        cont = inMotList(&SH_HeapupMotList2DEFAULT, anim->next);
        mode = 3;
        add = GetAnimationClass(obj)->speed * gcGlobalVar.dt * (100.0f / heap2);
    }
    if (*(signed char *)(GetCharacterClass(obj) + 0x360) != 0) {
        if (jc) {
            if (jn)
                goto skip;
        } else if (!jn)
            goto skip;
        resetAttackPower();
    skip:;
    }
    if (start) {
        B_00188608 += add;
    } else if (cont && *(signed char *)(GetCharacterClass(obj) + 0x360) != 0) {
        B_00188608 += add;
        if (B_00188608 > 100.0f)
            B_00188608 = 100.0f;
        if (mode == 2) {
            if (inMotList(&SH_HeapSuccessMotListDEFAULT, anim->cur))
                startAttackEffect(getAttackPowerRatio());
            else
                resetAttackPower();
        }
    }
    if (B_00188608 > 100.0f)
        B_00188608 = 100.0f;
    return jc;
}
