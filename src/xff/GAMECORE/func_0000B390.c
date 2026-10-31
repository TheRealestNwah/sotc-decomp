typedef struct {
    char p0[0x60];
    long t60;
    long t68;
    char p70[0x110];
    float f180;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern int D_00179E90;
extern int D_00179E94;
extern long iosGetTCountExtension(void);
extern void *get_main_cameraman(void);
extern void *get_camera_obj(void *);
extern void *get_clip_screen(void *);
extern void set_scissor_screen_size(void *, int, int, int);
extern void update_clip_screen(void *);
extern void doit_cameraman_manager(float);
extern void scrRun(void);

static void func_0000B390(void)
{
    float f;
    void *clip;

    for (;;) {
        gcGlobalVar.t60 = iosGetTCountExtension();
        f = gcGlobalVar.f180;
        clip = get_clip_screen(get_camera_obj(get_main_cameraman()));
        set_scissor_screen_size(clip, 0, D_00179E90, D_00179E90);
        set_scissor_screen_size(clip, 1, D_00179E94, D_00179E94);
        update_clip_screen(clip);
        doit_cameraman_manager(f);
        gcGlobalVar.t68 = iosGetTCountExtension();
        scrRun();
    }
}
