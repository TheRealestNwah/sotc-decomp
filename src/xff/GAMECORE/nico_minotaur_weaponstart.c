extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern void *GetLayoutClass(void *);
extern void UpdateLayoutClassPastSimpleGeometry(void *);
extern void UpdateLayoutClassParentGeometry(void *, int, int);
extern void UpdateLayoutClassSimpleGeometry(void *, float);
extern void scrRun(void);

void nico_minotaur_weaponstart(void)
{
    void *l = GetLayoutClass(isysGetThisSubThread());
    char *g = gcGlobalVar;

    for (;;) {
        UpdateLayoutClassPastSimpleGeometry(l);
        UpdateLayoutClassParentGeometry(l, 0, 0);
        UpdateLayoutClassSimpleGeometry(l, *(float *)(g + 0x184));
        scrRun();
    }
}
