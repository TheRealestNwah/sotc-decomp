extern int B_00183B50;
extern int activedemoInfo[];
extern int rootPtn;
extern int ScrIntrDef_START_ACTIVE_DEMO;
extern void func_0000E828(void);
extern void bgmPlay(int, float);
extern int createScriptObj(void (*)(void), int, int *, int, int, int, int, int);
extern void scriptIntrSignal(int);

void activeDemoStart(int arg)
{
    bgmPlay(B_00183B50, 100.0f);
    if (activedemoInfo[3] == 0) {
        activedemoInfo[2] = arg;
        activedemoInfo[3] = createScriptObj(func_0000E828, 0, &rootPtn, 0x1000, 0, 1, 0, 0);
    }
    scriptIntrSignal(ScrIntrDef_START_ACTIVE_DEMO);
}
