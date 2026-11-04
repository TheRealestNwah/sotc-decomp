extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);
extern int getPassageNum(char *);

int SCRConditionExecGazeToPlayer(void *obj)
{
    char *w = getSCRDataCtrlWork(obj);
    char *p = w + 0x3CC0;
    char *x = *(char **)(GetCharacterClass(obj) + 0x110C);

    if (*(int *)(p + 0x14) != 0) {
        if (*(int *)(p + 0x30) == *(int *)(w + 0x4078))
            return *(int *)(x + 0x68);
    } else if (getPassageNum(w) < 2 && *(int *)(w + 0x3A0) == 0) {
        if (*(int *)(w + 0x94) == *(int *)(w + 0x4078))
            return *(int *)(x + 0x68);
    }
    return 0;
}
