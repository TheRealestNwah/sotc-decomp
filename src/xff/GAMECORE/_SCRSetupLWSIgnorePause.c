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

extern char rootPtn[];
extern int CreateScriptAnimationSequence(LWSSetup *);
static void func_00044418(void);

int _SCRSetupLWSIgnorePause(int id, int a, int b, int c, int e)
{
    LWSSetup s;
    int none = -1;

    s.id = id;
    s.ptn = rootPtn;
    s.a = a;
    s.b = b;
    s.c = c;
    s.e = e;
    s.func = func_00044418;
    s.g = 1;
    s.h = none;
    s.d = 0;
    s.f = 0;
    return CreateScriptAnimationSequence(&s);
}
