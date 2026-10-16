extern char gcGlobalVar[];
extern int *SkelFocusDef_PLAYER_HAND_A_L, *SkelFocusDef_PLAYER_HAND_A_R;
extern float RO_0017DF50[], RO_0017DF60[];
extern void *gStatGetHorseDemoISYSObj(void);
extern void *SCRGetFirstObj(void *);
extern void nico_setHorseRidingStatusForHorseIndep(void *, void *, int, float *, int, float *);

void demo_op2_setHorseBridle(void)
{
    void *h = gStatGetHorseDemoISYSObj();

    if (h != 0)
        nico_setHorseRidingStatusForHorseIndep(h, SCRGetFirstObj(gcGlobalVar + 0x2B0), SkelFocusDef_PLAYER_HAND_A_L[2],
                                               RO_0017DF50, SkelFocusDef_PLAYER_HAND_A_R[2], RO_0017DF60);
}
