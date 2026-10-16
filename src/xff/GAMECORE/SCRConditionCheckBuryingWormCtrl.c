extern void *getSCRDataCtrlWork(void *);
extern int getBuryingWormCtrlWork(void *);

int SCRConditionCheckBuryingWormCtrl(void *actor)
{
    char *work;

    work = getSCRDataCtrlWork(actor);
    if (*(int *)(work + 0x4090) == 3) {
        return getBuryingWormCtrlWork(work + 0x3D10);
    }
    return 0;
}
