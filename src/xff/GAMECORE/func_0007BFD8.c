extern char *GetSCRCharaAIWorkPtr(void *);
extern void ColCont2_Release(void *);
extern void player_resetHangPointWork(void *);
extern void player_resetAvoidDangerCliffWork(void *, void *);
extern void unloadObj(void *);
extern void nico_ResetCharacterObjFallDownInfo(void *);
extern void player_resetSlipEffect(void *, void *);

static void func_0007BFD8(void *obj)
{
    char *work = GetSCRCharaAIWorkPtr(obj);
    void **child;
    ColCont2_Release(work + 0xDD0);
    player_resetHangPointWork(work + 0x1AC0);
    player_resetAvoidDangerCliffWork(obj, work + 0x1BB0);
    child = (void **)(GetSCRCharaAIWorkPtr(obj) + 0x1C60);
    if (*child) {
        unloadObj(*child);
        *child = 0;
    }
    nico_ResetCharacterObjFallDownInfo(obj);
    player_resetSlipEffect(obj, work + 0x1C68);
}
