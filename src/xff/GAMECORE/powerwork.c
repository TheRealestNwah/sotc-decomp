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
static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (*(void * *)&DldSysUndefSymbol)) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}
extern float B_00188604;
#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : (x) < (lo) ? (lo) : (x))
extern float _gameFWorkChk(int);
extern void playerlifebar_sethp(float);
extern float gStatGetPlayerAccessoriesDamgeRaitoToPlayer(void);
extern void _gameFWorkSet(int, float);
extern void playerlifebar_effect(int);
extern float B_00188600;
extern void setgrip(float);
extern void startGaugeMaxAddEffect(void);
extern float D_0017A304;

float getPlayerMaxHp(void);
void resetAttackPower(void);
float getAttackPowerRatio(void);

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

int chkMotionList(void *motion, char *list)
{
    int count = *(int *)(list + 0xC);
    unsigned int *refs = *(unsigned int **)(list + 0x10);
    int i;

    for (i = 0; i < count; i++, refs++) {
        if (motion == resourceData(refs))
            return 1;
    }
    return 0;
}

float getPlayerHp(void)
{
    return B_00188604;
}

void setPlayerHp(float hp)
{
    hp = CLAMP(hp, 0.0f, _gameFWorkChk(11));
    B_00188604 = hp;
    playerlifebar_sethp(getPlayerHp() / getPlayerMaxHp());
}

void addPlayerHp(float add)
{
    float v;
    float r;

    if (add < 0.0f)
        add *= gStatGetPlayerAccessoriesDamgeRaitoToPlayer();
    v = B_00188604 + add;
    if (_gameFWorkChk(11) < v)
        r = _gameFWorkChk(11);
    else if (v < 0.0f)
        r = 0.0f;
    else
        r = v;
    B_00188604 = r;
    playerlifebar_sethp(getPlayerHp() / getPlayerMaxHp());
}

float _getPlayerHpRatio(void)
{
    float temp_f20;

    temp_f20 = getPlayerHp();
    return temp_f20 / getPlayerMaxHp();
}

float getPlayerHpRatio(void) {
    float temp_f20;

    temp_f20 = getPlayerHp();
    return (temp_f20 / getPlayerMaxHp()) * 100.0f;
}

float getPlayerMaxHp(void)
{
    return _gameFWorkChk(11);
}

void setPlayerMaxHp(float hp)
{
 float limit = 570.0f < hp ? 570.0f : hp;
 _gameFWorkSet(11, limit);
}

void addPlayerMaxHp(float add)
{
    int old = _gameFWorkChk(11);
    float v = _gameFWorkChk(11) + add;
    float r;

    if (v > 570.0f)
        r = 570.0f;
    else
        r = v;
    _gameFWorkSet(11, r);
    if (_gameFWorkChk(11) > old)
        playerlifebar_effect(1);
}

float getPlayerGrip(void)
{
    return B_00188600;
}

void setPlayerGrip(float g)
{
    g = CLAMP(g, 0.0f, _gameFWorkChk(12));
    B_00188600 = g;
    setgrip(g / _gameFWorkChk(12));
}

void addPlayerGrip(float add)
{
    float v = B_00188600 + add;

    v = _gameFWorkChk(12) < v ? _gameFWorkChk(12) : (v < 0.0f ? 0.0f : v);
    B_00188600 = v;
    setgrip(v / _gameFWorkChk(12));
}

float getPlayerMaxGrip(void)
{
    return _gameFWorkChk(12);
}

void setPlayerMaxGrip(float grip)
{
    float clamped;
    if (700.0f < grip) clamped = 700.0f;
    else if (grip < 100.0f) clamped = 100.0f;
    else clamped = grip;
    _gameFWorkSet(12, clamped);
}

void addPlayerMaxGrip(float add)
{
    float v = _gameFWorkChk(12) + add;
    _gameFWorkSet(12, v > 700.0f ? 700.0f : v < 100.0f ? 100.0f : v);
    if (add > 0.0f)
        startGaugeMaxAddEffect();
}

float getPlayerMaxGripRatio(void)
{
    return _gameFWorkChk(12) / 100.0f;
}

float getPlayerO2(void)
{
    return D_0017A304;
}

void setPlayerO2(float fparg0)
{
    float var_f0;

    var_f0 = 100.0f;
    if (!(fparg0 > 100.0f)) {
        var_f0 = 0.0f;
        if (!(fparg0 < 0.0f)) {
            var_f0 = fparg0;
        }
    }
    D_0017A304 = var_f0;
}

void addPlayerO2(float add)
{
    float v = D_0017A304 + add;
    float r;
    if (100.0f < v)
        r = 100.0f;
    else if (v < 0.0f)
        r = 0.0f;
    else
        r = v;
    D_0017A304 = r;
}

void initPowerWork(void)
{
    (*(int *)&B_00188608) = 0;
}

void resetAttackPower(void)
{
    (*(int *)&B_00188608) = 0;
}

float getAttackPowerRatio(void)
{
    return B_00188608 * 0.01f;
}
