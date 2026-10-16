typedef struct {
    int id;
    void *ptn;
    int a;
    int b;
    int c;
    int d;
    int e;
    void *func;
    int f;
    int g;
    int h;
} LWSSetup;

typedef struct {
    char pad[0x180];
    float a;
    float b;
} GVar;

extern GVar gcGlobalVar;
extern char rootPtn[];
extern void *CreateScriptAnimationSequence(LWSSetup *);
extern void PlayScriptAnimationSequence(void *, int, int, int);
extern void *get_main_cameraman_camera_obj(void);
extern void ExecObjectAnimation(void *, void *, float, float);

int _SCRPlayLWS(int id, int a, int b, int e)
{
    LWSSetup s;
    void *o;

    s.id = id;
    s.ptn = rootPtn;
    s.b = a;
    s.c = b;
    s.e = e;
    s.g = 1;
    s.h = -1;
    s.a = 0;
    s.d = 0;
    s.func = 0;
    s.f = 0;
    o = CreateScriptAnimationSequence(&s);
    if (o != 0) {
        PlayScriptAnimationSequence(o, 0, -1, 3);
        ExecObjectAnimation(o, get_main_cameraman_camera_obj(), gcGlobalVar.a, gcGlobalVar.b);
    }
    return 1;
}
