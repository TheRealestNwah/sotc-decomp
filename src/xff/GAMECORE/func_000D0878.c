typedef struct { char pad[0x170]; float dt; } GcGlobal;
typedef struct { char pad[0x20]; float f20; float f24; } Obj2;
extern GcGlobal gcGlobalVar;
extern float D_0017B3A8;
extern char RO_00180BE0[];

extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(int, int);
extern float SpriteMenuGetFadeByLayer(int, int);
extern void func_000CFFA0(int, void *, void *, float);
extern void func_000D0490(void);
extern void func_000D05F8(int, void *, void *);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void scrRun(void);
extern void screenBlur(int, int, int, int, float, float, int, int, int);

static void func_000D0878(int arg0, void *arg1, Obj2 *arg2, int arg3)
{
    float t;
    float zero = 0.0f;
    float fade;
    int n;

    func_000D0490();
    (*(void (**)(int, int, int, int, float))((char *)arg1 + 0x28))(arg0, 0, 0, 0, gcGlobalVar.dt);
    func_000D05F8(arg0, arg1, arg2);
    iosDlPushLayer(0x1A);
    t = (1.1f - D_0017B3A8) * 10.0f;
    if (t > zero) {
        func_000CFFA0(arg0, arg1, arg2, t);
    }
    iosDlPopLayer();
    D_0017B3A8 += D_0017B3A8 * arg2->f20 * 30.0f * gcGlobalVar.dt;
    arg2->f20 = arg2->f20 * arg2->f24;
    if (D_0017B3A8 > 4.0f) {
        D_0017B3A8 = 4.0f;
    }
    if (arg3 != 0) {
        n = (int)(D_0017B3A8 * 5.0f);
        fade = SpriteMenuGetFadeByLayer(arg0, SpriteMenuGetLayerNoByHash(arg0, MakeStrHashValue(RO_00180BE0)));
        fade = fade * 128.0f;
        screenBlur(0x1C, 0x200, 0x200, (n < 0x11) ? n : 0x10, zero, ((D_0017B3A8 - 1.0f) * 0.15f) + 1.0f, 0, 0, (int)(fade * 64.0f / 128.0f));
    }
    scrRun();
}
