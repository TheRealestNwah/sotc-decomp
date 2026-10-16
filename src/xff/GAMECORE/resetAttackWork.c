extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);
extern int SetCharacterObjMotionShiftCallBackEntry(void *, int, int, int, int, int);

void resetAttackWork(void *obj)
{
    int i = 0;
    char *w = getSCRDataCtrlWork(obj) + 0x40C0;
    int n = *(int *)(GetCharacterClass(obj) + 0x2C8);

    *(int *)(w + 0x4) = 0;
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0x10) = 0;
    *(int *)(w + 0xC) = 0;
    for (; i < n; i++)
        SetCharacterObjMotionShiftCallBackEntry(obj, i, 0, 0, 0, 0);
}
