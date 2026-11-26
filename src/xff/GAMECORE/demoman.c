extern char rootPtn[];
extern char *GetScriptLayoutClass(void *);
extern void *createScriptObj(void (*)(void), int, void *, int, int, int, int, int);
extern void CancelCaptionSubThreadAll(void);
extern void SetDisplayModelNearClippingSwitch(int);
extern void SkipCutDemoCameraOrient(void *);
extern char SH_StageDataDEFAULT[];
extern int sheetMgrUnloadSegmentIndex();

static int func_000D4768(int a, int b, int c, int d);

void demoManEnd(void *o)
{
    char *w = *(char **)(GetScriptLayoutClass(o) + 0x2D8);

    if (*(int *)(w + 0x20) > 0)
        createScriptObj(func_000D4768, *(int *)(w + 0x20), rootPtn, 0x1000, 0, 1, 0, 0);
    if (*(int *)(w + 0x2C) > 0)
        createScriptObj(func_000D4768, *(int *)(w + 0x2C), rootPtn, 0x1000, 0, 1, 0, 0);
    *(int *)(w + 0x10) = 1;
    CancelCaptionSubThreadAll();
    SetDisplayModelNearClippingSwitch(1);
}

int demoManChkLoadFinish(void *actor)
{
    int *d=*(int **)(GetScriptLayoutClass(actor) + 0x2D8);
    if (d[0x4C/4] < d[0x50/4] - 1) return 1;
    return d[0] == 6;
}

void demoManSkip(void *a, void *b)
{
    void *l = GetScriptLayoutClass(a);
    SkipCutDemoCameraOrient(b);
    CancelCaptionSubThreadAll();
    l = 0;
}

int IsForwardTime__DemoMan(void *context, float time)
{
    void *work = *(void **)((char *)GetScriptLayoutClass(context) + 0x2D8);

    if (*(int *)((char *)work + 0x2C) <= 0) {
        goto yes;
    }
    if (!(*(float *)((char *)work + 0x34) <= time)) {
        goto no;
    }
    if (!(time <= *(float *)((char *)work + 0x40))) {
        goto no;
    }

yes:
    return 1;
no:
    return 0;
}

int ForwardTime__DemoMan(void *actor, float fparg0)
{
    float temp_f1;
    void *temp_v1;

    temp_v1 = (*(void **)((char *)(GetScriptLayoutClass(actor)) + 0x2D8));
    temp_f1 = fparg0 - (*(float *)((char *)(temp_v1) + 0x34));
    (*(float *)((char *)(temp_v1) + 0x38)) = fparg0;
    (*(float *)((char *)(temp_v1) + 0x34)) = fparg0;
    (*(float *)((char *)(temp_v1) + 0x3C)) = (float) (fparg0 * 30.0f);
    (*(float *)((char *)(temp_v1) + 0x24)) = (float) ((*(float *)((char *)(temp_v1) + 0x24)) + temp_f1);
    return 1;
}

static int func_000D4768(int a, int b, int c, int d)
{
    return sheetMgrUnloadSegmentIndex((int)SH_StageDataDEFAULT, a, 0, d);
}
