extern int DldSysUndefSymbol;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

void SCRFuncSendKeyToGameObj(void *a, int b, int c, int d, int e, int *obj, int g, int i, unsigned int *h)
{
    int ooff = *obj & 0x3FFFF;
    int *ot = ooff != 0 ? *(int **)((char *)obj - ooff) : 0;
    int *o = (ot != 0 && ot != (int *)DldSysUndefSymbol) ? (int *)ot[4] : 0;
    unsigned int v = *h;
    int voff = v & 0x3FFFF;
    char *t = voff != 0 ? *(char **)((char *)h - voff) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    if (o != 0 && o[2] != 0 && p != 0)
        CharaCtrlSetScriptCtrlStatus((void *)o[2], *(int *)(p + 4));
}
