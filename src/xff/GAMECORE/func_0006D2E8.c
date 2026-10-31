typedef struct {
    char pad0[0x180];
    float frameTime;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern void scrRunM(int);

static void func_0006D2E8(void)
{
    float t = 0.0f;

    isysGetThisSubThread();
    do {
        t += gcGlobalVar.frameTime;
        scrRunM(1);
    } while (t < 5.0f);
}
