extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsColStatus(void *, long, long);
extern int getNearPointPosUserPathWork(char *, float *, int, int, int);
extern void setAttainmentPos(char *, float *);
extern void setAttainmentObj(char *, int);

#define PLAYER_COL(w, v) ColCont2_IsColStatus(getPlayerColCont2(*(int *)((w) + 0x4078)), 0xFE00L << 38, (long)(v) << 38)

int SCRFuncSetPlayerAttainForHorse(void *a, int b, int c, int d, int e)
{
    float pos[4];
    char *w = getSCRDataCtrlWork(a);

    if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), d, e)) {
        if (getNearPointPosUserPathWork(w, pos, *(int *)(*(char **)(w + 0x407C) + 0x134), 1, b)) {
            setAttainmentPos(w, pos);
            return;
        }
    } else if (PLAYER_COL(w, 0x9600) || PLAYER_COL(w, 0x9800) || PLAYER_COL(w, 0x9A00) || PLAYER_COL(w, 0x9C00)) {
        if (getNearPointPosUserPathWork(w, pos, *(int *)(*(char **)(w + 0x407C) + 0x134), 1, 0x20)) {
            setAttainmentPos(w, pos);
            return;
        }
    }
    setAttainmentObj(w, *(int *)(w + 0x4078));
}
