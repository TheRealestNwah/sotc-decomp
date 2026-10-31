typedef struct {
    char p0[0xA0];
    long tA0;
    long tA8;
    char pB0[0xD0];
    float f180;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void doit_wind_manager(float);
extern void scrRun(void);

static void func_0000B298(void)
{
    for (;;) {
        gcGlobalVar.tA0 = iosGetTCountExtension();
        doit_wind_manager(gcGlobalVar.f180);
        gcGlobalVar.tA8 = iosGetTCountExtension();
        scrRun();
    }
}
