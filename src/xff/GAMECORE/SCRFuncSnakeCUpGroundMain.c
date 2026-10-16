extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

void SCRFuncSnakeCUpGroundMain(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(a);

    if (*(int *)(ai + 0x5A90) != 0 && *(int *)(ai + 0x3DF4) == 0) {
        unsigned int v = *h;
        int voff = v & 0x3FFFF;
        char *t = voff != 0 ? *(char **)((char *)h - voff) : 0;
        char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

        if (p != 0)
            CharaCtrlSetScriptCtrlStatus(a, *(int *)(p + 4));
        *(int *)(ai + 0x5A90) = 0;
    }
}
