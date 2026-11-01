extern char *GetLayoutClass(void *);
extern void SetJudgeVolumeInfo(void *, int, int, int, void *, void *, void *, float, float, float);
extern int CheckPositionInsideOfJudgeVolumeInfo(void *, void *);

typedef struct {
    char p0[0x40];
    float p40;
    float p44;
    float p48;
    char p4C[0x14];
    char p60[0x10];
    char p70[0x20];
    char p90[0xA4];
    int p134;
    int *p138;
    int p13C;
} LayoutClass;

int ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject(void *info, void *layout, void *pos)
{
    char tmp[0x60];
    LayoutClass *c = (LayoutClass *)GetLayoutClass(layout);
    void *v0, *v1, *v2;

    if (info == 0) {
        info = tmp;
    }
    v0 = c->p90;
    v1 = c->p70;
    v2 = c->p60;
    if (c == 0) {
        return 0;
    }
    SetJudgeVolumeInfo(info, *c->p138, c->p134, c->p13C, v0, v1, v2, c->p44, c->p40, c->p48);
    return CheckPositionInsideOfJudgeVolumeInfo(info, pos);
}
