typedef struct {
    char pad[0x180];
    float a;
    float b;
} GVar;

extern GVar gcGlobalVar;
extern void PlayScriptAnimationSequence(void *, int, int, int);
extern char *GetScriptAnimationClass(void *);
extern void *get_main_cameraman_camera_obj(void);
extern void ExecObjectAnimation(void *, void *, float, float);

void _SCRStartLWS(void *o, int a, int b, int *done)
{
    if (o == 0)
        return;
    PlayScriptAnimationSequence(o, 0, a, b);
    if (done != 0) {
        *(int *)(GetScriptAnimationClass(o) + 0x348) = (int)done;
        *done = 0;
    }
    ExecObjectAnimation(o, get_main_cameraman_camera_obj(), gcGlobalVar.a, gcGlobalVar.b);
}
