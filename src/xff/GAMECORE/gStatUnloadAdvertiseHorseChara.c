typedef struct {
    int a;
    int flag;
    int stage;
    int b;
    int set;
} HorseType;

extern int SH_HorseTypeDEFAULT[];
extern int _omakeSelectFlagChk(int);

static inline HorseType *findHorse(void)
{
    int *sh = SH_HorseTypeDEFAULT;
    int n = sh[3];
    HorseType *e = (HorseType *)sh[4];
    HorseType *base = e;
    int i;

    n--;
    e++;

    for (i = 0; i < n; i++, e++) {
        if (_omakeSelectFlagChk(e->flag))
            return e;
    }
    return base;
}

extern void _omakeSelectFlagSet(int);
extern void _omakeSelectFlagCls(int);

void gStatUnloadAdvertiseHorseChara(void)
{
    HorseType *e = findHorse();

    if (e->set != 0)
        _omakeSelectFlagSet(e->set);
    else
        _omakeSelectFlagCls(e->flag);
}
