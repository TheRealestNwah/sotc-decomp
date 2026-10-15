extern char *GetSCRCharaAIWorkPtr(void *);
extern void setWallStopHorseCtrlWork(void *, int);

void setHorseSemiAutomaticCtrl(void *actor, int on)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    *(int *)(w + 0x41F4) = on;
    if (on != 0)
        setWallStopHorseCtrlWork(w + 0x3D20, 0);
    else
        setWallStopHorseCtrlWork(w + 0x3D20, 1);
}
