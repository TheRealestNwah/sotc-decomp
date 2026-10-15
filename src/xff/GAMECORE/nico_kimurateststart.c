extern char padManagerData[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void scrRun(void);
extern void iosSetCurrentMatrix(void *);
extern void iosRotCurrentMatrixZ(float);
extern void iosGetCurrentMatrix(void *);

void nico_kimurateststart(void)
{
    char *l;
    char *pd;
    l = GetLayoutClass(isysGetThisSubThread());
    scrRun();
    pd = padManagerData;
    for (;;) {
        if (*(int *)(pd + 0xF98) & 2) {
            iosSetCurrentMatrix(*(void **)(l + 0x158));
            iosRotCurrentMatrixZ(0.0034888885f);
            iosGetCurrentMatrix(*(void **)(l + 0x158));
        }
        scrRun();
    }
}
