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

int _SCRSetupLWS(int id, int a, int b, int c, int e)
{
    LWSSetup s;

    s.id = id;
    s.ptn = rootPtn;
    s.a = a;
    s.b = b;
    s.c = c;
    s.e = e;
    s.g = 1;
    s.h = -1;
    s.d = 0;
    s.func = 0;
    s.f = 0;
    return CreateScriptAnimationSequence(&s);
}
