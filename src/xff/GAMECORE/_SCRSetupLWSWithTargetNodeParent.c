typedef struct {
    int id;
    void *ptn;
    void *a;
    void *b;
    void *c;
    int d;
    int e;
    void *func;
    int f;
    int g;
    int h;
} LWSSetup;

extern char rootPtn[];
extern char B_0018A680[];
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern int CreateScriptAnimationSequence(LWSSetup *);

int _SCRSetupLWSWithTargetNodeParent(int id, int e, int *def)
{
    LWSSetup s;

    SetGeometryPointerNodePosState(B_0018A680, e, def[2], IdentityQuaternion, ZeroPoint);
    s.id = id;
    s.ptn = rootPtn;
    s.a = B_0018A680;
    s.b = ZeroPoint;
    s.c = IdentityQuaternion;
    s.e = e;
    s.g = 1;
    s.h = -1;
    s.d = 0;
    s.func = 0;
    s.f = 0;
    return CreateScriptAnimationSequence(&s);
}
