extern int rootPtn;
extern void InitFogColMan(void);
extern void CreateFogColMan(void *);
extern void *get_main_cameraman_camera_obj(void);
extern void ExecFogColMan(void *);
extern void scrRun(void);

static void T_0000B560(void)
{
    InitFogColMan();
    CreateFogColMan(&rootPtn);
    for (;;) {
        ExecFogColMan(get_main_cameraman_camera_obj());
        scrRun();
    }
}
