extern void D_000BC4F0(void *obj, int arg);
extern int D_0017AFD0, D_0017AFD4;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void initSScriptSystem(void *);
extern void initSmallManager(void);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*func)(void *obj, int arg), int);
extern void scrRunM(int);
extern void isysJumpSubThread(void *, int);
static void func_000BC250(void);

void nico_soundScriptStart(void)
{
    void *t = isysGetThisSubThread();
    scrInit(t);
    initSScriptSystem(t);
    initSmallManager();
    SetScriptObjDeleteCallBackFunc(t, D_000BC4F0, 0);
    scrRunM(1);
    D_0017AFD0 = 0;
    D_0017AFD4 = 0;
    isysJumpSubThread(func_000BC250, 0);
}
