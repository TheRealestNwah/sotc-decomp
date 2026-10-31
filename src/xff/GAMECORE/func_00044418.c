typedef struct {
    char pad0[0x170];
    float animA;
    float animB;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern void isysSleepSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern int ExecObjectAnimation(void *th, void *cam, float a, float b);

static void func_00044418(void)
{
    void *th = isysGetThisSubThread();

    while (!ExecObjectAnimation(th, get_main_cameraman_camera_obj(), gcGlobalVar.animA, gcGlobalVar.animB))
        isysSleepSubThread();
}
