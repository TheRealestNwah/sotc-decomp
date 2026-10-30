extern void *DldSysUndefSymbol;
extern char *GameObject_LAKE_ENV;
extern int SCRJudgeVolumeDef_PLAYER_WHISTLE_AREA;
extern void *GAMEUTIL_get_player_obj(void);
extern char *GetLayoutClass(void *);
extern int CheckPositionInsideOfJudgeVolumeObjectByLabel(void *out, int obj, int label, int pos);

static int func_0000B5E0(void)
{
    char buf[0x60];
    int outside = 1;

    if (DldSysUndefSymbol != &GameObject_LAKE_ENV &&
        DldSysUndefSymbol != &SCRJudgeVolumeDef_PLAYER_WHISTLE_AREA &&
        *(int *)(GameObject_LAKE_ENV + 8) != 0) {
        char *cls = GetLayoutClass(GAMEUTIL_get_player_obj());
        outside = CheckPositionInsideOfJudgeVolumeObjectByLabel(buf, *(int *)(GameObject_LAKE_ENV + 8),
                                                               SCRJudgeVolumeDef_PLAYER_WHISTLE_AREA,
                                                               *(int *)(cls + 0x134)) != 1;
    }
    return outside;
}
