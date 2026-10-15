typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *getSCRDataCtrlWork(void *);
extern int getPointDataFromEvent(char *, int, Vec4 *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, int, int);

int SCRConditionVolumeCheckForPointPos(void *a, int ev, int c, int d, int e, int f, int g, int h, int vol)
{
    char buf[0x60] __attribute__((aligned(16)));
    Vec4 pt;
    int r = getPointDataFromEvent(getSCRDataCtrlWork(a), ev, &pt);
    if (r == 0)
        return 0;
    return CheckPositionInsideOfJudgeVolumeObject(buf, a, vol, r);
}
