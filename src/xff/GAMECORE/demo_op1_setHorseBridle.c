extern char gcGlobalVar[];
extern int *SkelFocusDef_PLAYER_HAND_A_L, *SkelFocusDef_PLAYER_HAND_A_R;
extern float RO_0017DF30[], RO_0017DF40[];
extern void *SCRGetFirstObj(void *);
extern void nico_setHorseRidingStatusForHorseIndep(void *, void *, int, float *, int, float *);

void demo_op1_setHorseBridle(void)
{
    void *p = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    nico_setHorseRidingStatusForHorseIndep(p, SCRGetFirstObj(gcGlobalVar + 0x2B0), SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017DF30, SkelFocusDef_PLAYER_HAND_A_R[2], RO_0017DF40);
}
