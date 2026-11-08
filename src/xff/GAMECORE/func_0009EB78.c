#ifdef NONMATCHING
/* 47 diffs: branch layout of the two inlined path-state checks (original shares one 'a1 = 1' exit and uses b+nop where gcc uses beql). Early-return inlines are the closest form so far. */
extern void *isysGetThisSubThread(void);
extern void CharaCtrlResetAllScriptCtrlStatus(void *thread);
extern void SCRCharaTurnDirectInput(void *thread, float x);
extern void Kite_ResetEventFrameCheck(void *work);
extern int Kite_CmpPathPoint(void *a, void *b);
extern void AI_UpdateLeaderPathWork(void *a, void *b);
extern void AI_UpdateChildPathWork(void *work);
extern void setDataHeaderFromAreaIdx(void *work);
extern char *GetLayoutClass(void *thread);

static inline int leaderActive(char *w)
{
    int s;

    if (*(int *)(w + 0x26C) == 0x12)
        return 0;
    s = *(int *)(w + 0x274);
    if (s == 0xE)
        return 0;
    if (*(int *)(w + 0x3C) == 0x24)
        return 1;
    if (*(int *)(w + 0x38) == 0)
        return 0;
    if (*(int *)(w + 0x288) == 0)
        return 0;
    if (s == 9 || s == 0xB || s == 0xC || s == 0xD)
        return 1;
    if (Kite_CmpPathPoint(w + 0x600, w + 0x620))
        return 1;
    return 0;
}

static inline int childActive(char *w)
{
    int s;

    if (*(int *)(w + 0x26C) == 0x12)
        return 0;
    if (*(int *)(w + 0x38) != 0)
        return 0;
    if (*(int *)(w + 0x3C) == 0x24)
        return 0;
    if (*(int *)(w + 0x288) == 0)
        return 0;
    s = *(int *)(w + 0x274);
    if (s == 9 || s == 0xB || s == 0xC || s == 0xD)
        return 1;
    if (Kite_CmpPathPoint(w + 0x600, w + 0x620))
        return 1;
    return 0;
}

static void func_0009EB78(char *w)
{
    void *thread = isysGetThisSubThread();
    char *layout;
    char *pos;

    CharaCtrlResetAllScriptCtrlStatus(thread);
    SCRCharaTurnDirectInput(thread, 0.0f);
    Kite_ResetEventFrameCheck(w + 0x6A0);

    if (leaderActive(w)) {
        AI_UpdateLeaderPathWork(*(void **)(w + 0x360), w + 0x370);
    } else if (*(int *)(w + 0x360) != 0) {
        setDataHeaderFromAreaIdx(w + 0x370);
    }

    if (childActive(w))
        AI_UpdateChildPathWork(w + 0x370);

    layout = GetLayoutClass(thread);
    pos = *(char **)(layout + 0x134);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(pos), "r"(w + 0x8E0) : "memory");
}
#endif
