typedef struct ScriptObj ScriptObj;
typedef struct Ptn Ptn;

extern Ptn rootPtn;
extern ScriptObj *gcCreateScriptObj(void (*func)(void), int arg1, Ptn *parent, int stackSize,
                                    int arg4, int arg5, const char *name);
extern void scrRun(void);
extern void usbdevFrameInit(void);

static void gcMainLoop(void);

ScriptObj *initgcmain(void)
{
    return gcCreateScriptObj(gcMainLoop, 0, &rootPtn, 0x1000, 0, 1, "st_mainloop");
}

static void gcMainLoop(void)
{
    scrRun();
    while (1) {
        usbdevFrameInit();
        scrRun();
    }
}
