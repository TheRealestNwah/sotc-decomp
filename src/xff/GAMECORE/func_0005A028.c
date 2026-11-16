/* Parked: 2 diffs. Horse slow-down script condition: below the speed threshold, cancels any accelerate/dash/shift-up request (zeroing the input fields and clearing the shift-up, repeat-accelerate and kicked control bits) and sets the slow-down bit. Remaining: the original loads the ScriptCtrlDef_SCRHorseShiftUp pointer before the 64-bit control-flag load; ours swaps those two loads. Store order, helper inlines, mask locals and type changes did not move it. The volatile header read makes each check reload the handle word like the original. */
#ifdef NONMATCHING
extern int *DldSysUndefSymbol;
extern char *ScriptCtrlDef_SCRAccel;
extern char *ScriptCtrlDef_SCRHorseDash;
extern char *ScriptCtrlDef_SCRDash;
extern char *ScriptCtrlDef_SCRHorseShiftUp;
extern char *ScriptCtrlDef_SCRHorseSuperShiftUp;
extern char *ScriptCtrlDef_SCRHorseRepeateAccele;
extern char *ScriptCtrlDef_SCRHorseKicked;
extern char *ScriptCtrlDef_SCRSlowDown;

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *(volatile unsigned int *)h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_0005A028(char *a, int *b, char *c, char *d, float f)
{
    unsigned int *h;

    if (f < *(float *)(a + 0x1C)) {
        if (c != 0) {
            h = (unsigned int *)(c + 4);
            if (dldElem(h) == ScriptCtrlDef_SCRAccel || dldElem(h) == ScriptCtrlDef_SCRHorseDash
                || dldElem(h) == ScriptCtrlDef_SCRDash || dldElem(h) == ScriptCtrlDef_SCRHorseShiftUp
                || dldElem(h) == ScriptCtrlDef_SCRHorseSuperShiftUp) {
                b[13] = 0;
                b[14] = 0;
                b[15] = 0;
                b[16] = 0;
                b[17] = 0;
                b[1] = 0;
                *(long *)(d + 0x1C0) &= ~(1L << *(int *)(ScriptCtrlDef_SCRHorseShiftUp + 4));
                *(long *)(d + 0x1C0) &= ~(1L << *(int *)(ScriptCtrlDef_SCRHorseRepeateAccele + 4));
                *(long *)(d + 0x1C0) &= ~(1L << *(int *)(ScriptCtrlDef_SCRHorseKicked + 4));
            }
        }
        *(long *)(d + 0x1C0) |= 1L << *(int *)(ScriptCtrlDef_SCRSlowDown + 4);
        return 1;
    }
    return 0;
}
#endif
