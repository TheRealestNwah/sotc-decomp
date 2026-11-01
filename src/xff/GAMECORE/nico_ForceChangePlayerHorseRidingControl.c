extern char gcGlobalVar[];
extern float IdentityQuaternion[];
extern float ZeroPoint[];
extern void *SCRGetFirstObj(void *);
extern void SetGeometryPointerNodePosState(void *, void *, int, float *, float *);
extern void *GetSCRCharaAIWorkPtr(void *);
extern void *GetGeometryPointerObject(char *);
extern int SendCharaControlChangeMsg(void *, int);
extern int SendCharaControlledChangeMsg(void *, void *, void *);
extern int SendCharaAddMotionSyncStartMsg(void *, int);
extern int SendCharaNodeParentSetMsg(void *, void *, int);
extern void nico_setHorseRidingStatusForHorse(void *, void *, int, const float *, float);
extern int *SkelFocusDef_PLAYER_HAND_A_L;
extern const float RO_0017E250[];

void nico_ForceChangePlayerHorseRidingControl(unsigned char *actor)
{
    char geometry[0x40];
    void *horse;

    horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    if (horse != 0) {
        char *work;
        void *parent;

        SetGeometryPointerNodePosState(geometry, horse, 0, IdentityQuaternion, ZeroPoint);
        work = (char *)GetSCRCharaAIWorkPtr(actor);
        parent = GetGeometryPointerObject(geometry);
        SendCharaControlChangeMsg(actor, (int)parent);
        SendCharaControlledChangeMsg(parent, actor, geometry);
        SendCharaAddMotionSyncStartMsg(actor, (int)parent);
        SendCharaNodeParentSetMsg(actor, GetGeometryPointerObject(geometry), 0x10000);
        nico_setHorseRidingStatusForHorse(parent, actor, SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017E250, 0.035f);
        *(int *)(work + 0xD98) = 1;
    }
}
