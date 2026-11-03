typedef struct { int pad0[2]; int *result; int padC; } SpriteParam;
typedef struct { char pad0[0x28]; void (*exec)(unsigned char *, float, int, void (*)(void), void *); void (*draw)(unsigned char *); } SpriteMenu;
typedef struct { char pad[0x168]; float time; int pad16C; float speed; } GcGlobal;
typedef struct {
    unsigned char *thread;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    float start;
    float time;
    int *result;
} OptionMenu;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void *texSearchMopByName(char *);
extern float texAnimationOne(void *, float, float);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern char RO_0017E1A0[];
extern void func_00072618(void);
extern int func_000743B8(unsigned char *, SpriteMenu *, OptionMenu *);
extern void T_00073A30(void);

void optionMenuScript(SpriteParam *parameters)
{
    OptionMenu om;
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    GcGlobal *g;
    void *mop;
    float anim;
    int ready;

    thread = isysGetThisSubThread();
    anim = 0.0f;
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    g = &gcGlobalVar;
    om.unkC = 1;
    om.unk4 = 0;
    om.unk8 = 0;
    om.unk10 = 0;
    om.time = g->time;
    om.start = g->time - 3.0f;
    om.thread = thread;
    om.result = local.result;
    if (local.result != 0) {
        *local.result = 0;
    }
    func_00072618();
    mop = texSearchMopByName(RO_0017E1A0);
    while (1) {
        ready = 3.0f <= gcGlobalVar.time - om.start;
        if (func_000743B8(thread, menu, &om)) {
            break;
        }
        menu->exec(thread, gcGlobalVar.speed, ready | om.unk10, T_00073A30, &om);
        menu->draw(thread);
        anim = texAnimationOne(mop, anim, gcGlobalVar.speed);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
