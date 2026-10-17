extern char *GetLayoutClass(unsigned char *);
extern void *GetCharacterClass(void *);
extern void *GetSCRCharaAIWorkPtr(void *);
extern void *GetGeometryPointerObject(char *);
extern int SendCharaControlChangeMsg(void *, int);
extern int SendCharaControlledChangeMsg(void *, void *, void *);
extern int SendCharaAddMotionSyncStartMsg(void *, int);
extern int SendCharaNodeParentSetMsg(void *, void *, int);
extern void nico_setHorseRidingStatusForHorse(void *, void *, int, const float *, float);
extern int *SkelFocusDef_PLAYER_HAND_A_L;
extern const float RO_0017E250[];
void nico_ChangePlayerHorseRidingControlWithParentObj(unsigned char *actor)
{
    char *layout = GetLayoutClass(actor);

    if (*(int *)(layout + 0x124) != 0) {
        char *geometry = layout + 0xC0;
        char *work = (char *)GetSCRCharaAIWorkPtr(actor);
        void *parent = GetGeometryPointerObject(geometry);
        SendCharaControlChangeMsg(actor, (int)parent);
        SendCharaControlledChangeMsg(parent, actor, geometry);
        SendCharaAddMotionSyncStartMsg(actor, (int)parent);
        SendCharaNodeParentSetMsg(actor, GetGeometryPointerObject(geometry), 0x10000);
        nico_setHorseRidingStatusForHorse(parent, actor, SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017E250, 0.035f);
        *(int *)(work + 0xD98) = 1;
    }
}


void nico_ChangePlayerHorseRidingControlWithVCol(unsigned char *actor)
{
    char *character = (char *)GetCharacterClass(actor);

    if (*(int *)(character + 0xF3C) != 0) {
        char *geometry = character + 0xEF0;
        char *work = (char *)GetSCRCharaAIWorkPtr(actor);
        void *parent = GetGeometryPointerObject(geometry);
        SendCharaControlChangeMsg(actor, (int)parent);
        SendCharaControlledChangeMsg(parent, actor, geometry);
        SendCharaAddMotionSyncStartMsg(actor, (int)parent);
        SendCharaNodeParentSetMsg(actor, GetGeometryPointerObject(geometry), 0x10000);
        nico_setHorseRidingStatusForHorse(parent, actor, SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017E250, 0.035f);
        *(int *)(work + 0xD98) = 1;
    }
}



void nico_ChangePlayerHorseRidingControlWithHCol(unsigned char *actor)
{
    char *character = (char *)GetCharacterClass(actor);

    if (*(int *)(character + 0xFBC) != 0) {
        char *geometry = character + 0xF70;
        char *work = (char *)GetSCRCharaAIWorkPtr(actor);
        void *parent = GetGeometryPointerObject(geometry);
        SendCharaControlChangeMsg(actor, (int)parent);
        SendCharaControlledChangeMsg(parent, actor, geometry);
        SendCharaAddMotionSyncStartMsg(actor, (int)parent);
        SendCharaNodeParentSetMsg(actor, GetGeometryPointerObject(geometry), 0x10000);
        nico_setHorseRidingStatusForHorse(parent, actor, SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017E250, 0.035f);
        *(int *)(work + 0xD98) = 1;
    }
}
