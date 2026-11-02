extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncBuddhaMissileMain2(void *actor, int aim, int count, int a3, int a4, int a5, int a6, int a7, unsigned int *h,
                               float interval, float angle, float wait)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *e;

    if (*(int *)(ai + 0x41BC) != 0) {
        if (*(float *)(ai + 0x41B8) <= 0.0f) {
            e = dldElem(h);
            if (e != 0)
                CharaCtrlSetScriptCtrlStatus(actor, *(int *)(e + 4));
            if (aim == 0) {
                *(int *)(ai + 0x41C4) = 2;
            } else {
                *(float *)(ai + 0x41C8) = angle;
                *(int *)(ai + 0x41C4) = 3;
            }
            *(float *)(ai + 0x41B8) = interval;
            if (++*(int *)(ai + 0x41C0) >= count) {
                *(float *)(ai + 0x41B4) = 0.0f;
                *(int *)(ai + 0x41BC) = 0;
                *(float *)(ai + 0x41B8) = 0.0f;
                *(int *)(ai + 0x41C0) = 0;
            }
        }
        *(float *)(ai + 0x41B8) -= *(float *)(gcGlobalVar + 0x180);
    } else {
        if (wait <= *(float *)(ai + 0x41B4))
            *(int *)(ai + 0x41BC) = 1;
        *(float *)(ai + 0x41B4) += *(float *)(gcGlobalVar + 0x180);
    }
}
