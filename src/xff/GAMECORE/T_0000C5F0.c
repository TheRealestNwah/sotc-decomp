extern void InitLightColMan(void);
extern void CreateLightColMan(void *);
extern void TaskExecLightColMan(void);
extern void scrRun(void);
extern char rootPtn[];

static void T_0000C5F0(void)
{
    InitLightColMan();
    CreateLightColMan(rootPtn);
    for (;;) {
        TaskExecLightColMan();
        scrRun();
    }
}
