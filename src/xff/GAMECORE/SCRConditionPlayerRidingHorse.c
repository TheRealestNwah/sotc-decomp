extern void *getSCRDataCtrlWork();
extern int nico_GetPlayerCharacterRidingHorseObject(int);

int SCRConditionPlayerRidingHorse(void)
{
    return nico_GetPlayerCharacterRidingHorseObject((*(int *)((char *)(getSCRDataCtrlWork()) + 0x4078))) != 0;
}
