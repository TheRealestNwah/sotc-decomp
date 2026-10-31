extern long iosGetTCountExtension(void);
extern float getFadeValue(void);
extern void *get_main_cameraman_camera_obj(void);
extern void DispDispObjGroupModel(void *);
extern void scrRun(void);
extern unsigned int __gameMode;
typedef struct {
    char p0[0x30];
    long t30;
    long t38;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;

static void func_0000B130(void)
{
    for (;;) {
        gcGlobalVar.t30 = iosGetTCountExtension();
        if (getFadeValue() != 1.0f) {
            DispDispObjGroupModel(get_main_cameraman_camera_obj());
        }
        gcGlobalVar.t38 = iosGetTCountExtension();
        while (__gameMode & 0x10) {
            scrRun();
        }
        scrRun();
    }
}
