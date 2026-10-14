extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(int);
extern void player_SetGripDamage(int, float);

void SCRFuncSetGripDamage(int actor, float d)
{
    char *w = getSCRDataCtrlWork(actor);

    player_SetGripDamage(*(int *)(w + 0x4078), d * *(float *)(gcGlobalVar + 0x180));
}
