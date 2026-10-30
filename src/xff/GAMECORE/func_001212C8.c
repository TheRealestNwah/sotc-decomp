typedef struct {
    int obj;
    char pad4[0x14];
    int bgm;
    char pad1C[0x14];
    int flag;
    char pad34[0x10];
    int done;
    int attr;
    int eyeCamera;
    char pad50[8];
} DemoSlot;

extern DemoSlot B_001A5A78[2];
extern void gameflowBossEyeCameraDisable(int);
extern void gameflowSetPauseEnable(int);
extern void _gameFlagCls(int);
extern void bgmStop(int, int *, float);
extern int flushScriptObjImmediate();

static void func_001212C8(int obj)
{
    DemoSlot *slot = B_001A5A78;
    int i;

    for (i = 0; i < 2; i++, slot++) {
        if (obj == slot->obj) {
            slot->done = 1;
            if (slot->eyeCamera)
                gameflowBossEyeCameraDisable(0);
            if (slot->attr & 1)
                gameflowSetPauseEnable(1);
            if (slot->flag)
                _gameFlagCls(slot->flag);
            if (slot->bgm)
                bgmStop(slot->bgm, 0, 100.0f);
            slot->obj = 0;
            flushScriptObjImmediate(obj);
            return;
        }
    }
}
