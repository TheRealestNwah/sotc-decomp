extern void *GetCharacterClass();
extern void *GetLayoutClass(int);
extern int getSCRDataCtrlWork(int);
extern void setAttainmentPos(int, int);

void SCRFuncHorseBossDetectStop(int arg0)
{
    int temp_s0;
    void *temp_v0;

    temp_v0 = GetCharacterClass();
    if ((*(int *)((char *)(temp_v0) + 0xFF0)) == 0) {
        return;
    }
    if ((*(int *)((char *)(temp_v0) + 0xFF4)) == 0) {
        return;
    }
    temp_s0 = getSCRDataCtrlWork(arg0);
    setAttainmentPos(temp_s0, (*(int *)((char *)(GetLayoutClass(arg0)) + 0x134)));
}
