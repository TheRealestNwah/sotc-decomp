extern void ChangeCharacterObjControlTarget(int, int);
extern void ChangeCharacterObjControlledTarget(int, int, int, int);
extern void *GetCharacterClass(void *);
extern void *GetSCRCharaAIWorkPtr(void *);
extern void nico_resetHorseRidingStatusForHorse(int);

extern void ResetCharacterClassSyncMode(void *);
extern unsigned char InitialGeometryPointer[];

void nico_ResetPlayerHorseRidingControl(void *arg0) {
    void *temp_s0;
    void *temp_s2;

    temp_s0 = (*(void **)((char *)(GetCharacterClass(arg0)) + 0x960));
    temp_s2 = GetCharacterClass(temp_s0);
    ChangeCharacterObjControlTarget((int) temp_s0, (int) temp_s0);
    ChangeCharacterObjControlledTarget((int) arg0, (int) arg0, (int) InitialGeometryPointer, 0);
    ResetCharacterClassSyncMode(temp_s2);
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(temp_s0)) + 0xD98)) = 0;
    nico_resetHorseRidingStatusForHorse((int) arg0);
}
