extern char *getSCRDataCtrlWork(void *);
extern void resetAttackWork(void *);
void createAttackWork(void *actor)
{
    char *w = getSCRDataCtrlWork(actor) + 0x40C0;
    *(int *)(w + 0x0) = 0;
    *(int *)(w + 0x14) = 0;
    resetAttackWork(actor);
}
