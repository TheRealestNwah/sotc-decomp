extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern long charrootdyn_getCollisionAttribute(void *geometry);
extern void *getPlayerColCont2(void *);
extern void ColCont2_Release(void *);
extern void nico_resetHorseRidingStatusForHorse(void *);
extern void player_resetAvoidDangerCliffWork(void *, void *);
extern void player_resetHangPointWork(void *);
extern void player_resetSlipEffect(void *, void *);

static inline void *get_horse(void *obj)
{
    void *horse = *(void **)(GetCharacterClass(obj) + 0x950);
    if (horse != obj && *(short *)(GetCharacterClass(horse) + 0x370) == 3)
        return horse;
    return 0;
}

static void func_0007C0D0(void *obj)
{
    char *work = GetSCRCharaAIWorkPtr(obj);
    void *horse = get_horse(obj);
    if (horse)
        nico_resetHorseRidingStatusForHorse(horse);
    *(int *)(GetSCRCharaAIWorkPtr(obj) + 0xD98) = 0;
    ColCont2_Release(getPlayerColCont2(obj));
    player_resetHangPointWork(work + 0x1AC0);
    player_resetAvoidDangerCliffWork(obj, work + 0x1BB0);
    player_resetSlipEffect(obj, work + 0x1C68);
}

static int T_0007C180(void *geometry)
{
    long attr = charrootdyn_getCollisionAttribute(geometry);
    int r = 0;
    if ((attr & 3) == 1 || (attr & 4))
        r = 1;
    return r;
}
