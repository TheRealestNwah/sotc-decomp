extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassParentGeometry(char *, int, int);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void FlushCollisionWork(void *);
extern void scrRun(void);

void nico_updatescript(void)
{
    void *t = isysGetThisSubThread();
    char *l = GetLayoutClass(t);
    char *g = gcGlobalVar;
    for (;;) {
        UpdateLayoutClassPastSimpleGeometry(l);
        UpdateLayoutClassParentGeometry(l, 0, 0);
        UpdateLayoutClassSimpleGeometry(l, *(float *)(g + 0x184));
        FlushCollisionWork(t);
        scrRun();
    }
}
