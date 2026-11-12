/* System script thread: registers the pause/continue/ending/jump/time-attack interrupts, then loops forever running the fade tick, the player status switch and two sound flag pairs (seStop takes the SE handle) before func_00018A58 and scrRun. */
extern int ScrIntrDef_SYSTEM_PAUSE;
extern int ScrIntrDef_SYSTEM_CONTINUE;
extern int ScrIntrDef_DEMO_PAUSE;
extern int ScrIntrDef_DEMO_CONTINUE;
extern int ScrIntrDef_MENU_PAUSE;
extern int ScrIntrDef_MENU_CONTINUE;
extern int ScrIntrDef_GAME_ENDING;
extern int ScrIntrDef_JUMP_HOKORA;
extern int ScrIntrDef_JUMP_SEKIBAN;
extern int ScrIntrDef_START_ACTIVE_DEMO;
extern int ScrIntrDef_DEBUG_CHECKPOINT_LOAD;
extern int ScrIntrDef_GAME_CANCEL;
extern int ScrIntrDef_TIMEATTACK_MENU_START;
extern int ScrIntrDef_TIMEATTACK_RETRY;
extern char D_0017A098[];
extern char D_0017A0B0[];
extern char D_0017A0C8[];
extern char D_0017A0E0[];
extern char D_0017A0F8[];
extern char D_0017A110[];
extern char D_0017A128[];
extern char D_0017A140[];
extern char D_0017A158[];
extern char D_0017A170[];
extern char D_0017A188[];
extern char D_0017A1A0[];
extern char D_0017A1B8[];
extern char D_0017A1D0[];
extern int D_0017A05C;
extern int D_0017A060;
extern int D_0017A064;
extern int D_0017A068;
extern int D_0017A06C;
extern int D_0017A07C;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void scriptIntrEntryChildThread(int, void *, void *, void *);
extern void fadeTickProc(void);
extern void setPlayerStatusSwitch(int);
extern void seStop(int);
extern void scrRun(void);
extern void func_00018B08(void);
extern void func_00018B38(void);
extern void func_00018A58(void);

static void func_000167B8(void *arg)
{
    void *th = isysGetThisSubThread();

    scrInit(th);
    scriptIntrEntryChildThread(ScrIntrDef_SYSTEM_PAUSE, th, D_0017A098, arg);
    scriptIntrEntryChildThread(ScrIntrDef_SYSTEM_CONTINUE, th, D_0017A0B0, arg);
    scriptIntrEntryChildThread(ScrIntrDef_DEMO_PAUSE, th, D_0017A0C8, arg);
    scriptIntrEntryChildThread(ScrIntrDef_DEMO_CONTINUE, th, D_0017A0E0, arg);
    scriptIntrEntryChildThread(ScrIntrDef_MENU_PAUSE, th, D_0017A0F8, arg);
    scriptIntrEntryChildThread(ScrIntrDef_MENU_CONTINUE, th, D_0017A110, arg);
    scriptIntrEntryChildThread(ScrIntrDef_GAME_ENDING, th, D_0017A128, arg);
    scriptIntrEntryChildThread(ScrIntrDef_JUMP_HOKORA, th, D_0017A140, arg);
    scriptIntrEntryChildThread(ScrIntrDef_JUMP_SEKIBAN, th, D_0017A158, arg);
    scriptIntrEntryChildThread(ScrIntrDef_START_ACTIVE_DEMO, th, D_0017A170, arg);
    scriptIntrEntryChildThread(ScrIntrDef_DEBUG_CHECKPOINT_LOAD, th, D_0017A188, arg);
    scriptIntrEntryChildThread(ScrIntrDef_GAME_CANCEL, th, D_0017A1A0, arg);
    scriptIntrEntryChildThread(ScrIntrDef_TIMEATTACK_MENU_START, th, D_0017A1B8, arg);
    scriptIntrEntryChildThread(ScrIntrDef_TIMEATTACK_RETRY, th, D_0017A1D0, arg);
    for (;;) {
        fadeTickProc();
        setPlayerStatusSwitch(D_0017A07C == 0);
        if (D_0017A05C == 0) {
            if (D_0017A060 != 0)
                func_00018B08();
        } else if (D_0017A060 == 0) {
            seStop(D_0017A05C);
            D_0017A05C = 0;
        }
        if (D_0017A064 == 0) {
            if (D_0017A06C != 0)
                func_00018B38();
        } else if (D_0017A06C == 0) {
            seStop(D_0017A064);
            if (D_0017A068 != 0)
                seStop(D_0017A068);
            D_0017A064 = 0;
            D_0017A068 = 0;
        }
        func_00018A58();
        scrRun();
    }
}
