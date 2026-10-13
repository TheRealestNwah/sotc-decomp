extern void *GetCharacterClass(int);
extern void *getSCRDataCtrlWork();
extern int nico_GetPlayerCharacterRidingHorseObject(int);

signed char SCRConditionPlayerWaterIn(void)
{
    int temp_v0_2;
    int var_a0;
    void *temp_v0;

    temp_v0 = getSCRDataCtrlWork();
    temp_v0_2 = nico_GetPlayerCharacterRidingHorseObject((*(int *)((char *)(temp_v0) + 0x4078)));
    var_a0 = (*(int *)((char *)(temp_v0) + 0x4078));
    if (temp_v0_2 != 0) {
        var_a0 = temp_v0_2;
    }
    return (*(signed char *)((char *)(GetCharacterClass(var_a0)) + 0x362));
}
