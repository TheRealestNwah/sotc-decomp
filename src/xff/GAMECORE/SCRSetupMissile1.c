typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int ScriptLayoutObjDef_MISSILE_TYPE1;
extern char gcGlobalVar[];
typedef struct { int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o; } MParam;
extern void *initScriptLayoutObj(Ptn *, int, MParam *, int, int, void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void SCRSetupMissile1(void *a, int b, int c, int d)
{
    MParam s;
    void *o;
    s.a = 0;
    s.b = b;
    s.c = c;
    s.d = 0;
    s.i = 0;
    s.e = 0;
    s.f = 0;
    s.g = 0;
    s.h = 1;
    s.j = 0;
    s.k = 0;
    s.l = 1;
    s.m = 0;
    s.n = 0;
    s.o = 0;
    o = initScriptLayoutObj(&rootPtn, ScriptLayoutObjDef_MISSILE_TYPE1, &s, d, 4, a, 0);
    if (o != 0)
        isysAddGroupWithLinkParam(o, gcGlobalVar + 0x280, 0, 0);
}
