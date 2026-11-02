extern int *DldSysUndefSymbol;
extern int SeList_hp_max;
extern int SeList_grip_max;
extern int ControlMode_GEX_TAIL_DEATH;
extern char *ScriptCtrlDef_SCREnd;
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetScriptClass(void *);
extern char *GetCharacterClass(void *);
extern void sePlaySystemSound(int);
extern void addPlayerMaxHp(float);
extern float getPlayerMaxHp(void);
extern void addPlayerMaxGrip(float);
extern void addPlayerHp(float);
extern void addPlayerGrip(float);
extern void nico_setFruitsFlag(void *);
extern void isysRequestDeleteObj(void *);
extern char *getSObjNodeBySubObj(void *);
extern unsigned char SetLayoutObjAccessSwitch(void *, int);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);
extern void tailsFlagSet(int, int);
extern void setTailCutTime(void);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static void T_00078DA0(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);
    float *p = (float *)dldBase(*(unsigned int **)(GetScriptClass(*(void **)(ai + 0x14C)) + 0x48));
    char *node;
    float d;
    int *mode;

    if (p != 0) {
        if (p[0] != 0.0f)
            sePlaySystemSound(SeList_hp_max);
        if (p[1] != 0.0f)
            sePlaySystemSound(SeList_grip_max);
        addPlayerMaxHp(p[0]);
        d = 100.0f - getPlayerMaxHp();
        if (0.0f < d)
            addPlayerMaxHp(d);
        addPlayerMaxGrip(p[1]);
        addPlayerHp(p[2]);
        addPlayerGrip(p[3]);
    }
    mode = &ControlMode_GEX_TAIL_DEATH;
    if (*mode != *(int *)(GetCharacterClass(*(void **)(ai + 0x14C)) + 0x750)) {
        nico_setFruitsFlag(*(void **)(ai + 0x14C));
        isysRequestDeleteObj(*(void **)(ai + 0x14C));
        *(void **)(ai + 0x14C) = 0;
    } else {
        node = getSObjNodeBySubObj(*(void **)(ai + 0x14C));
        SetLayoutObjAccessSwitch(*(void **)(ai + 0x14C), 0);
        CharaCtrlSetOutsideScriptCtrlStatus(*(void **)(ai + 0x14C), *(int *)(ScriptCtrlDef_SCREnd + 0x4));
        do {
            if (node != 0) {
                tailsFlagSet(*(short *)(node + 0x50), *(int *)(node + 0xC));
                setTailCutTime();
            }
        } while (0);
        *(void **)(ai + 0x14C) = 0;
    }
    *(int *)(ai + 0x148) = 0;
}
