typedef struct {
    char p0[0x22C];
    char v22C[4];
    char v230[0x44];
    char v274[4];
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern int rootPtn;
extern int D_00179E90;
extern int D_00179E94;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void *create_cameraman(void *, float, void *, void *, void *, void *, int, int);
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);
extern void func_0000B390(void);
extern void init_cameraman_manager(void);
extern void *get_camera_obj(void *);
extern void *get_clip_screen(void *);
extern void set_scissor_screen_size(void *, int, int, int);
extern void update_clip_screen(void *);
extern void *employ_cameraman(void *);
extern void change_main_cameraman(void *);

static void func_0000A990(int arg)
{
    int w = getDrawScreenWidth();
    int h = getDrawScreenHeight();
    void *cm = create_cameraman(&rootPtn, 45.0f, gcGlobalVar.v274, gcGlobalVar.v22C, gcGlobalVar.v230,
                                gcGlobalVar.v230, w, h);
    void *clip;

    gcCreateScriptObj(func_0000B390, 0, &rootPtn, 0x3000, 0, arg, "cameraman_manager_task");
    init_cameraman_manager();
    clip = get_clip_screen(get_camera_obj(cm));
    set_scissor_screen_size(clip, 0, D_00179E90, D_00179E90);
    set_scissor_screen_size(clip, 1, D_00179E94, D_00179E94);
    update_clip_screen(clip);
    change_main_cameraman(employ_cameraman(cm));
}
