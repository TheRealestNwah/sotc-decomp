/* Attack trigger scan: walks the 0x54-byte attack entries of the script data work (+0x40C0) while each entry's ref at +0x24 resolves; the first entry whose condition, range check, judge volume and func_00114A80 test all pass sets the script control status of its two refs (+0x34, +0x38) and, when +0x40 resolves, the pin-attack IK target, then returns. */
extern int *DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern char *GetLayoutClass(void *);
extern char *getSCRDataCtrlWork(void *);
extern int execCondition(void *, void *);
extern int func_00114480(void *, void *);
extern void *func_00114C00(void *, void *);
extern int func_00114A80(void *, void *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRSetCharacterObjPinAttackIKTargetInfo(void *, int, void *, void *, int);

static void func_00114170(void *obj, void *arg)
{
    int buf[24];
    char *lay = GetLayoutClass(arg);
    char *p = *(char **)(getSCRDataCtrlWork(obj) + 0x40C0);
    int *a;
    int *b;

    while (dldResolve((unsigned int *)(p + 0x24)) != 0) {
        if (dldResolve((unsigned int *)(p + 0x24)) != 0 && execCondition(obj, p + 0x1C) != 0 && func_00114480(obj, p + 0xC) != 0 &&
            CheckPositionInsideOfJudgeVolumeObject(buf, obj, func_00114C00(obj, p), *(void **)(lay + 0x134)) != 0 &&
            func_00114A80(obj, p) != 0) {
            a = (int *)dldResolve((unsigned int *)(p + 0x34));
            b = (int *)dldResolve((unsigned int *)(p + 0x38));
            if (a != 0)
                CharaCtrlSetScriptCtrlStatus(obj, a[1]);
            if (b != 0)
                CharaCtrlSetScriptCtrlStatus(obj, b[1]);
            if (dldResolve((unsigned int *)(p + 0x40)) != 0)
                SCRSetCharacterObjPinAttackIKTargetInfo(obj, ((int *)dldResolve((unsigned int *)(p + 0x40)))[2], *(void **)(lay + 0x134), p + 0x44, 0);
            return;
        }
        p += 0x54;
    }
}
