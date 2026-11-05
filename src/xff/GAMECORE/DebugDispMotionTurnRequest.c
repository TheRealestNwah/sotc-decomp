typedef struct {
    char pad[0x20];
    int x20;
    char pad24[0xC];
} TurnReq;

extern int D_001798B8;
extern TurnReq D_00179930[];
extern char rootPtn[];
extern void func_00004E50(void);
extern void *createScriptObj(void *, void *, void *, int, int, int, int, int);

#ifdef NONMATCHING
static inline int chk(int i)
{
    if (i < 6 && i > 0) {
        return 1;
    }
    return 0;
}

void DebugDispMotionTurnRequest(char *obj)
{
    int idx = *(int *)(obj + 0xC54);
    int ok = chk(idx);
    short k;

    if ((unsigned)(D_001798B8 - 1) < 2 && ok) {
        D_00179930[idx].x20 = *(int *)(obj + 0x134);
        k = *(short *)(obj + 0x370);
        if (k == 2 || k == 4 || k == 3) {
            createScriptObj(func_00004E50, &D_00179930[*(int *)(obj + 0xC54)], rootPtn, 0x1000, 0, 1, 0, 0);
        }
    }
}
#endif
