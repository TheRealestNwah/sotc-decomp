typedef int s128 __attribute__((mode(TI)));
typedef struct Ptn Ptn;
typedef struct {
    char pad0[0x10];
    s128 dir;
    int a;
    int b;
    int *obj;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    float f44;
    char pad48[8];
} OrientWork;
extern Ptn rootPtn;
extern void func_00010CB0();
extern void func_00011448();
extern unsigned char RO_0017CA08[];
extern int *_gcCreateChildScriptObj(void *, void *, Ptn *, int, int, int, void *, void *);
extern void *iosMallocAlign(int, int, int);
extern void isysInitGroup(void *);
extern void SetScriptObjDeleteCallBackFunc(void *, void *, void *);
extern void setScriptObjArgument(void *, void *);

OrientWork *PlayDemoCameraOrient(int a, int b, s128 *dir, void *parent, int e, float f)
{
    int *obj = _gcCreateChildScriptObj(func_00010CB0, 0, &rootPtn, 0x1800, 0x50, 1, RO_0017CA08, parent);
    OrientWork *w = iosMallocAlign(*obj, 0x50, 0x10);

    w->obj = obj;
    w->dir = *dir;
    w->a = a;
    w->b = b;
    isysInitGroup(w);
    SetScriptObjDeleteCallBackFunc(obj, func_00011448, w);
    setScriptObjArgument(obj, w);
    w->f2C = -1;
    w->f34 = e;
    w->f40 = -1;
    w->f44 = f;
    w->f30 = 0;
    w->f38 = 0;
    w->f3C = 0;
    return w;
}
