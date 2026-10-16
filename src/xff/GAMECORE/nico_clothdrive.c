typedef struct {
    char pad0[0x180];
    float wind;
    float scale;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassParentGeometry(char *, int, int);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void GetLayoutClassWindGeometry(char *, void *);
extern void GetClothDynamics(void *, int, int, float, float);
extern void scrRun(void);

void nico_clothdrive(void)
{
    void *th = isysGetThisSubThread();
    char *c = GetLayoutClass(th);
    GlobalVar *g = &gcGlobalVar;

    for (;;) {
        if (*(int *)(c + 0x124) != 0) {
            UpdateLayoutClassPastSimpleGeometry(c);
            UpdateLayoutClassParentGeometry(c, 0, 0);
            UpdateLayoutClassSimpleGeometry(c, g->scale);
        }
        GetLayoutClassWindGeometry(c, c + 0x30);
        GetClothDynamics(th, 1, 0, g->wind, g->scale);
        scrRun();
    }
}
