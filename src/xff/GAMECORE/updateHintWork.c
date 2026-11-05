extern int DldSysUndefSymbol;
typedef struct { char pad[0x190]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;

typedef struct {
    unsigned int cond0;
    unsigned int cond1;
    float t0;
    float t1;
    unsigned int cond2;
    unsigned int func[2];
} HintEntry;

typedef struct {
    HintEntry *entries;
    int count;
    int played;
    float timer;
    int flag;
} HintWork;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);
extern int _gameIWorkChk(int);
extern void _gameIWorkSet(int, int);
extern int execCondition(void *, void *);
extern void execSCRBaseFunc(void *, void *);

void updateHintWork(void *actor)
{
    HintWork *w = (HintWork *)(getSCRDataCtrlWork(actor) + 0x40E0);
    HintEntry *e;

    if (w->entries == 0)
        return;
    w->flag = 0;
    if (_gameIWorkChk(14) == -1)
        return;
    if (_gameIWorkChk(14) >= w->count)
        return;
    if (*(int *)(getSCRDataCtrlWork(actor) + 0x4170) == *(int *)(GetCharacterClass(actor) + 0x750))
        return;
    e = &w->entries[_gameIWorkChk(14)];
    if (dldResolve(&e->cond0) != 0 && execCondition(actor, &e->cond0) == 0)
        return;
    if (execCondition(actor, &e->cond2)) {
        execSCRBaseFunc(actor, e->func);
        _gameIWorkSet(14, _gameIWorkChk(14) + 1);
        w->played = 0;
        w->timer = 0;
        return;
    }
    w->timer += gcGlobalVar.dt;
    if ((w->played == 0 && e->t0 <= w->timer) || (w->played > 0 && e->t1 <= w->timer)) {
        if (execCondition(actor, &e->cond1)) {
            w->flag = 1;
            w->timer = 0;
            w->played++;
        }
    }
}
