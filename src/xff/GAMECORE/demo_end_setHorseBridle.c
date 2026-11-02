typedef struct { char pad[8]; void *obj; } GameObject;
typedef struct { char pad[8]; int node; } SkelFocusDef;
extern GameObject *GameObject_HORSE_B, *GameObject_SHARMAN;
extern SkelFocusDef *SkelFocusDef_Sharman_A_LeftHand, *SkelFocusDef_Sharman_A_RightHand;
extern float RO_0017D310[], RO_0017D320[];
extern GameObject *GameObject_HORSE_C, *GameObject_GUARD_A;
extern SkelFocusDef *SkelFocusDef_Guard_A_LeftHand, *SkelFocusDef_Guard_A_RightHand;
extern float RO_0017D330[], RO_0017D340[];
extern GameObject *GameObject_HORSE_D, *GameObject_GUARD_B;
extern SkelFocusDef *SkelFocusDef_Guard_B_LeftHand, *SkelFocusDef_Guard_B_RightHand;
extern float RO_0017D350[], RO_0017D360[];
extern GameObject *GameObject_HORSE_E, *GameObject_GUARD_C;
extern SkelFocusDef *SkelFocusDef_Guard_C_LeftHand, *SkelFocusDef_Guard_C_RightHand;
extern float RO_0017D370[], RO_0017D380[];
extern GameObject *GameObject_HORSE_F, *GameObject_GUARD_D;
extern SkelFocusDef *SkelFocusDef_Guard_D_LeftHand, *SkelFocusDef_Guard_D_RightHand;
extern float RO_0017D390[], RO_0017D3A0[];
extern GameObject *GameObject_HORSE_G, *GameObject_GUARD_E;
extern SkelFocusDef *SkelFocusDef_Guard_E_LeftHand, *SkelFocusDef_Guard_E_RightHand;
extern float RO_0017D3B0[], RO_0017D3C0[];
extern void nico_setHorseRidingStatusForHorseIndep(void *, void *, int, float *, int, float *);

void demo_end_setHorseBridle(void)
{
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_B->obj, GameObject_SHARMAN->obj,
        SkelFocusDef_Sharman_A_LeftHand->node, RO_0017D310, SkelFocusDef_Sharman_A_RightHand->node, RO_0017D320);
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_C->obj, GameObject_GUARD_A->obj,
        SkelFocusDef_Guard_A_LeftHand->node, RO_0017D330, SkelFocusDef_Guard_A_RightHand->node, RO_0017D340);
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_D->obj, GameObject_GUARD_B->obj,
        SkelFocusDef_Guard_B_LeftHand->node, RO_0017D350, SkelFocusDef_Guard_B_RightHand->node, RO_0017D360);
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_E->obj, GameObject_GUARD_C->obj,
        SkelFocusDef_Guard_C_LeftHand->node, RO_0017D370, SkelFocusDef_Guard_C_RightHand->node, RO_0017D380);
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_F->obj, GameObject_GUARD_D->obj,
        SkelFocusDef_Guard_D_LeftHand->node, RO_0017D390, SkelFocusDef_Guard_D_RightHand->node, RO_0017D3A0);
    nico_setHorseRidingStatusForHorseIndep(GameObject_HORSE_G->obj, GameObject_GUARD_E->obj,
        SkelFocusDef_Guard_E_LeftHand->node, RO_0017D3B0, SkelFocusDef_Guard_E_RightHand->node, RO_0017D3C0);
}
