extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);
extern int _gameIWorkChk(int);
extern void _gameIWorkSet(int, int);
extern int execCondition(void *, void *);
extern void execSCRBaseFunc(void *, void *);

struct HintEntry {
    unsigned int ref;
    int cond2;
    float firstTime;
    float nextTime;
    int cond;
    int func;
    int unk18;
};

struct HintWork {
    struct HintEntry *table;
    int count;
    int stage;
    float timer;
    int flag;
};

void updateHintWork(void *obj)
{
    struct HintWork *hint = (struct HintWork *)(getSCRDataCtrlWork(obj) + 0x40E0);
    struct HintEntry *e;
    unsigned int v;
    int off;
    char *t;
    char *p;

    if (hint->table == 0)
        return;
    hint->flag = 0;
    if (_gameIWorkChk(14) == -1)
        return;
    if (_gameIWorkChk(14) >= hint->count)
        return;
    if (*(int *)(getSCRDataCtrlWork(obj) + 0x4170) == *(int *)(GetCharacterClass(obj) + 0x750))
        return;

    e = &hint->table[_gameIWorkChk(14)];
    v = e->ref;
    off = v & 0x3FFFF;
    t = off != 0 ? *(char **)((char *)e - off) : 0;
    p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    if (p != 0 && execCondition(obj, e) == 0)
        return;

    if (execCondition(obj, &e->cond) != 0) {
        execSCRBaseFunc(obj, &e->func);
        _gameIWorkSet(14, _gameIWorkChk(14) + 1);
        hint->stage = 0;
        hint->timer = 0.0f;
        return;
    }

    hint->timer += *(float *)(gcGlobalVar + 0x190);
    if ((hint->stage == 0 && e->firstTime <= hint->timer) || (hint->stage > 0 && e->nextTime <= hint->timer)) {
        if (execCondition(obj, &e->cond2) != 0) {
            hint->flag = 1;
            hint->timer = 0.0f;
            hint->stage++;
        }
    }
}
