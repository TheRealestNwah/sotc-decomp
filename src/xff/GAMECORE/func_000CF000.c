typedef struct {
    char pad0[0x170];
    float frameTime;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_0017B37C;
extern float D_0017B380[4];
extern void func_000CEAE0(void *, void *);
extern void func_000CE620(void *);
extern void func_000CED18(void *);
extern void func_000CE058(void *);
extern void func_000CE428();
extern void func_000CE878(void *);
extern void func_000CD810(void *, int, float, float, float, float);
extern int getGameClearCnt(void);
extern int _omakeSelectFlagChk(int);
extern void getSmallAnimalSaveTypePos(void *, void *);
extern float texAnimationOne(int, float, float);

#define W(type, o) (*(type *)(menu + (o)))

static void func_000CF000(void *unused, void *arg, char *menu)
{
    func_000CEAE0(arg, menu);
    func_000CE620(menu);
    func_000CED18(menu);
    if (getGameClearCnt() > 0) {
        if (_omakeSelectFlagChk(0x1A))
            func_000CE058(menu);
        if (_omakeSelectFlagChk(0x1B))
            getSmallAnimalSaveTypePos(func_000CE428, menu);
    }
    func_000CD810(menu, 1, D_0017B380[0] / 255.0f, D_0017B380[1] / 255.0f, D_0017B380[2] / 255.0f,
                  W(float, 0x14) * D_0017B380[3] * 0.0078125f);
    if (D_0017B37C == 0)
        func_000CE878(menu);
    texAnimationOne(W(int, 0x64), W(float, 0x5C), gcGlobalVar.frameTime);
    texAnimationOne(W(int, 0x6C), W(float, 0x5C), gcGlobalVar.frameTime);
    W(float, 0x5C) = texAnimationOne(W(int, 0x68), W(float, 0x5C), gcGlobalVar.frameTime);
}
