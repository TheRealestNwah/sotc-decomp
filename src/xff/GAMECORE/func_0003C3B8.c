extern int bossStatGetActiveBoss(void);
extern char *GetLayoutClass(void *);
extern void _SCRPlayLWS(int, void *, void *, void *);
extern char IdentityQuaternion[];
extern int BossStatus_MINOTOUR;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_MINO_A;
extern int BossStatus_MAMMOTH;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_MAMMOTH;
extern int BossStatus_KNIGHT;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_KNIGHT;
extern int BossStatus_BIRD;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_BIRD;
extern int BossStatus_KIRIN;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_KIRIN;
extern int BossStatus_MINOTOUR_B;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_MINO_B;
extern int BossStatus_EEL;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_EEL;
extern int BossStatus_YAMORI_B;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_YAMORI_B;
extern int BossStatus_TORTOISE;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_TORTOISE;
extern int BossStatus_NARGA;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_NARGA;
extern int BossStatus_LEO;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_LEO;
extern int BossStatus_POSEIDON;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_POSEIDON;
extern int BossStatus_SNAKE_C;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_SNAKE;
extern int BossStatus_CERBERUS;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_CERBERUS;
extern int BossStatus_MINOTOUR_C;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_MINO_C;
extern int BossStatus_EVIS;
extern int ScriptAnimationObjDef_SE_WEAKPOINT_EVIS;

static void func_0003C3B8(void *obj)
{
    int boss = bossStatGetActiveBoss();
    char *l = GetLayoutClass(obj);

    if (BossStatus_MINOTOUR == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_MINO_A, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_MAMMOTH == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_MAMMOTH, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_KNIGHT == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_KNIGHT, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_BIRD == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_BIRD, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_KIRIN == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_KIRIN, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_MINOTOUR_B == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_MINO_B, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_EEL == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_EEL, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_YAMORI_B == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_YAMORI_B, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_TORTOISE == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_TORTOISE, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_NARGA == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_NARGA, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_LEO == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_LEO, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_POSEIDON == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_POSEIDON, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_SNAKE_C == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_SNAKE, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_CERBERUS == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_CERBERUS, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_MINOTOUR_C == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_MINO_C, *(void **)(l + 0x134), IdentityQuaternion, obj);
    else if (BossStatus_EVIS == boss)
        _SCRPlayLWS(ScriptAnimationObjDef_SE_WEAKPOINT_EVIS, *(void **)(l + 0x134), IdentityQuaternion, obj);
}
