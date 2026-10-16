extern int DldSysUndefSymbol;
extern int execCondition(void *, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

void SCRFuncConditionSendKey(void *a, int b, int c, int d, int e, int f, int cond, int i, unsigned int *h)
{
    if (execCondition(a, cond)) {
        unsigned int v = *h;
        int off = v & 0x3FFFF;
        char *t = off != 0 ? *(char **)((char *)h - off) : 0;
        char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

        if (p != 0)
            CharaCtrlSetScriptCtrlStatus(a, *(int *)(p + 4));
    }
}
