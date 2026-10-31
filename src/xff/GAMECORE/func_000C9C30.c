extern int ScrIntrDef_GAME_LOADSTART;
extern int D_0017B274;
extern int D_0017B278;
extern int D_0017B27C;
extern void scriptIntrSignal(int);

static void func_000C9C30(int ok)
{
    if (ok != 0) {
        D_0017B27C = 1;
        D_0017B274 = 0;
        scriptIntrSignal(ScrIntrDef_GAME_LOADSTART);
    } else {
        D_0017B278 = 0;
    }
}
