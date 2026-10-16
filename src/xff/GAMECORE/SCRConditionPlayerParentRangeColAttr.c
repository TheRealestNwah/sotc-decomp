extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsColStatus(void *, long, long);

int SCRConditionPlayerParentRangeColAttr(void *actor, int a1, int a2, int a3, long type, long from, long to)
{
    char *w = getSCRDataCtrlWork(actor);
    long step = 0x200000;
    long x;

    if (type != 0x1E00000) {
        step = 0x800000000000L;
        if (type != 0x3F800000000000L)
            return 0;
    }
    for (x = from; x <= to; x += step) {
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), type, x))
            return 1;
    }
    return 0;
}
