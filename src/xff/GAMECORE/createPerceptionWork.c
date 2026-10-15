extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern void scrRun(void);

void createPerceptionWork(void *a, int b)
{
    char *w = getSCRDataCtrlWork(a) + 0x4030;
    while ((*(void **)(w + 0x48) = SCRGetFirstObj(gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    *(char **)(w + 0x4C) = GetLayoutClass(*(void **)(w + 0x48));
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w + 0x10) : "memory");
    *(int *)(w + 0x44) = b;
    *(int *)(w + 0x40) = 0;
}
