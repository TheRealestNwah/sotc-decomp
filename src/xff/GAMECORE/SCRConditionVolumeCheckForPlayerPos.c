extern char *getSCRDataCtrlWork(void *);
extern int equipmentInvisibilityCloak(void);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, int, int);

int SCRConditionVolumeCheckForPlayerPos(void *a, int b, int c, int d, int e, int f, int g, int h, int vol)
{
    char buf[0x60] __attribute__((aligned(16)));
    char *p = *(char **)(getSCRDataCtrlWork(a) + 0x407C);
    if (equipmentInvisibilityCloak())
        return 0;
    return CheckPositionInsideOfJudgeVolumeObject(buf, a, vol, *(int *)(p + 0x134));
}
