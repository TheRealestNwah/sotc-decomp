extern void *GetScriptLayoutClass(void *);
extern void SkipCutDemoCameraOrient(void *);
extern void CancelCaptionSubThreadAll(void);

void demoManSkip(void *a, void *b)
{
    void *l = GetScriptLayoutClass(a);
    SkipCutDemoCameraOrient(b);
    CancelCaptionSubThreadAll();
    l = 0;
}
