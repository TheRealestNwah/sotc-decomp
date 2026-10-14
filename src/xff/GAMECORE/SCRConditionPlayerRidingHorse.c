extern void *getSCRDataCtrlWork(void *);
extern int nico_GetPlayerCharacterRidingHorseObject(int);

int SCRConditionPlayerRidingHorse(void *actor)
{
    return nico_GetPlayerCharacterRidingHorseObject((*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x4078))) != 0;
}
